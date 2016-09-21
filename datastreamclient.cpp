#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#include <gflags/gflags.h>
#include "utils/test_config_cpp.h"

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/security/credentials.h>

#include "datastream.grpc.pb.h"

DEFINE_int32(num_clients, 2, "number of clients");
DEFINE_int32(data_size, 10, "size of data in MB");
DEFINE_int32(num_iterations, 10, "number of iterations");
DEFINE_int32(chunk_size, 64, "chunk size");
DEFINE_string(address,"0.0.0.0", "server address");
DEFINE_int32(port, 10000, "port");

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using datastream::DataChunkRequest;
using datastream::DataChunkSummary;
using datastream::DataStream;
using std::chrono::system_clock;

using namespace std;

//class DataStreamClient {
//public:
//	DataStreamClient(std::shared_ptr<Channel> channel) :
//			stub_(DataStream::NewStub(channel)) {
//	}
//
//	template<typename T>
//	void SendDataStream(std::vector<T>& Data) {
//		DataChunkSummary stats;
//		ClientContext context;
//		const int dataSize = Data.size();
//		const int chunkSize = 64 * 1024; // 64KB
//		const int numSegments = dataSize / chunkSize;
//
//		boost::uuids::uuid uuid = boost::uuids::random_generator()();
//		const std::string uuidStr = boost::lexical_cast<std::string>(uuid);
//
//		std::unique_ptr<ClientWriter<DataChunkRequest>> writer(
//				stub_->SendDataStream(&context, &stats));
//		for (auto Ix = 0; Ix < numSegments; ++Ix) {
//			DataChunkRequest request;
//			const int offset = Ix * chunkSize;
//			const int requestSize = std::min(chunkSize, dataSize - offset);
//			request.set_name(uuidStr.c_str());
//			request.set_totallength(dataSize);
//			request.set_offset(offset);
//			request.set_datalength(requestSize);
//			request.set_body(&(Data[0]) + offset, requestSize);
//
//			if (!writer->Write(request)) {
//				break;
//			}
//		}
//
//		// finalize the write
//		writer->WritesDone();
//		Status status = writer->Finish();
//		if (status.ok()) {
//			std::cout << "Finished sending " << dataSize << " bytes in "
//					<< stats.elapsed_time() << " microseconds" << std::endl;
//		} else {
//			std::cout << "SendDataStream rpc failed" << std::endl;
//		}
//	}
//private:
//	std::unique_ptr<DataStream::Stub> stub_;
//};
//// DataStreamClient


template<typename T>
class AsyncDataStreamClient {
public:
	explicit AsyncDataStreamClient(std::shared_ptr<Channel> channel,
			const std::vector<T>& Data, size_t numRPCs, size_t chunkSize)
		: stub_(DataStream::NewStub(channel)), Data_(Data), numRPCs_(numRPCs), chunkSize_(chunkSize)
	{
		startTime_ = system_clock::now();

		requestCount_ = 0;
		replyCount_ = 0;

		// HACK: we have fix data size
		const auto dataSize = Data_.size();
		const auto numMessage = dataSize / chunkSize;

		senderStartTime_ = system_clock::now();
		sender_ = std::thread(&AsyncDataStreamClient<T>::SendDataStream,
				this, Data_, numRPCs, chunkSize);

		collectorStartTime_ = system_clock::now();
		collector_ = std::thread(&AsyncDataStreamClient<T>::ReceiveReply,
				this, numRPCs * numMessage);
	}

	~AsyncDataStreamClient() {
		sender_.join();
		senderEndTime_ = system_clock::now();
		auto diff = senderEndTime_ - senderStartTime_;
		auto requestMicros = chrono::duration_cast<chrono::microseconds>(diff);
		double tmp = (double)requestMicros.count();
		tmp /= 1000.0; tmp /= 1000.0;
		cout << "Sent " << requestCount_ << " RPC messages in " << requestMicros.count()
				<< " microseconds"
				<< " --> "
				<< ((double)numRPCs_/tmp)
				<< " request/second"
				<< endl;

		collector_.join();
		collectorEndTime_ = system_clock::now();
		diff = collectorEndTime_ - collectorStartTime_;
		auto responseMicros = chrono::duration_cast<chrono::microseconds>(diff);
		tmp = (double)responseMicros.count();
		tmp /= 1000.0; tmp /= 1000.0;
		cout << "Received " << replyCount_ << " RPC reply in " << responseMicros.count()
				<< " microseconds"
				<< " --> "
				<< ((double)numRPCs_/tmp)
				<< " response/second"
				<< endl;
	}

	void SendDataStream(const std::vector<T>& Data, size_t numRPCs,
			size_t chunkSize) {
		Status status;

		for (auto Ix = 0; Ix < numRPCs; ++Ix) {
			const auto dataSize = Data.size();
			const auto numMessage = dataSize / chunkSize;

			boost::uuids::uuid uuid = boost::uuids::random_generator()();
			const std::string uuidStr = boost::lexical_cast<std::string>(uuid);
			for (auto Jx = 0; Jx < numMessage; ++Jx) {
				DataChunkRequest request;

				const int offset = Jx * chunkSize;
				const int bytesToSend = std::min(chunkSize, dataSize - offset);
				request.set_name(uuidStr);
				request.set_totallength(dataSize*8);
				request.set_offset(offset);
				request.set_datalength(bytesToSend);
				request.set_body(&Data[0] + offset, bytesToSend);

				ClientContext* context(new grpc::ClientContext);
				RPCs_.push_back(
						stub_->AsyncSendDataStream(context, request, &cq_));

				requestCount_++;
			}
		}
	}

	void ReceiveReply(size_t rpcCount) {
		Status status;
		size_t count = 0;
		while ((volatile int) requestCount_ != rpcCount) {
			sleep(1);
		}

		while (count < rpcCount) {
			DataChunkSummary reply;
			void* got_tag;
			bool ok = false;

			if (RPCs_.size() && RPCs_.back()) {
				RPCs_.back()->Finish(&reply, &status, (void*) count);

				cq_.Next(&got_tag, &ok);
				GPR_ASSERT(got_tag == (void* )count);
				GPR_ASSERT(ok);

				if (status.ok()) {
					replyCount_++;
				}
				count++;

				RPCs_.pop_back();
			}
		}
	}

private:
	CompletionQueue cq_;
	std::unique_ptr<DataStream::Stub> stub_;
	std::vector<std::unique_ptr<ClientAsyncResponseReader<DataChunkSummary>>>RPCs_;

	const std::vector<T>& Data_;
	size_t numRPCs_;
	size_t chunkSize_;
	size_t requestCount_;
	size_t replyCount_;
	system_clock::time_point startTime_, endTime_, senderStartTime_, senderEndTime_, collectorStartTime_, collectorEndTime_;

	mutable std::mutex m;
	std::thread sender_;
	std::thread collector_;
};

void startClient(const std::string& host, int port,
		const std::vector<double>& Data, int num_iterations, int chunk_size)
{
	std::stringstream ss;
	ss << host << ":" << port;
	std::cout << "communicates to: " << host << ":" << port << std::endl;
	AsyncDataStreamClient<double> asyncClient(grpc::CreateChannel(ss.str().c_str(),
							grpc::InsecureChannelCredentials()), Data, num_iterations, chunk_size);
}

int main(int argc, char** argv) {
	grpc::testing::InitTest(&argc, &argv, true);

	const size_t dataSize = FLAGS_data_size *1024*1024;
	std::vector<double> Data(dataSize);
	if (FLAGS_num_clients <= 1) {
		startClient(FLAGS_address, FLAGS_port, Data, FLAGS_num_iterations, FLAGS_chunk_size*1024);
	} else {
		std::vector<std::thread> clients(FLAGS_num_clients);
		for(auto Ix = 0; Ix < FLAGS_num_clients; ++Ix) {
			cout << "DataStreamClient " << Ix << endl;
			clients[Ix] = std::thread(&startClient, FLAGS_address, FLAGS_port, Data, FLAGS_num_iterations, FLAGS_chunk_size*1024);
		}

		for(auto Ix = 0; Ix < FLAGS_num_clients; ++Ix) {
			clients[Ix].join();
		}
	}

	return 0;
}
