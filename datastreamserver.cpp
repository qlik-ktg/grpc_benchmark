#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <thread>
#include <forward_list>
#include <string>

#include <grpc++/grpc++.h>
#include <grpc++/impl/codegen/async_stream.h>

#include "datastream.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::ServerAsyncResponseWriter;
using grpc::Status;
using datastream::DataChunkRequest;
using datastream::DataChunkSummary;
using datastream::DataStream;
using std::chrono::system_clock;
using namespace std::placeholders;

using namespace std;

//class DataStreamServerImpl final : public DataStream::Service {
//public:
//	explicit DataStreamServerImpl() : Service() {
//
//	}
//
//	Status SendDataStream(ServerContext* context, ServerReader<DataChunkRequest>* reader, DataChunkSummary* summary) override
//	{
//		DataChunkRequest request, previousRequest;
//		int numChunks = 0;
//
//		auto startTime = system_clock::now();
//		while(reader->Read(&request)) {
//			numChunks++;
//			previousRequest = request;
//		}
//		auto endTime = system_clock::now();
//		auto diff = endTime - startTime;
//		auto micros = chrono::duration_cast<chrono::microseconds>(diff);
//
//		cout << "numChunks = " << numChunks << endl;
//
//		summary->set_elapsed_time(micros.count());
//
//		return Status::OK;
//	}
//}; // DataStreamServer

//void RunServer() {
//	string server_address("localhost:50051");
//	DataStreamServerImpl service;
//
//	ServerBuilder builder;
//	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
//	builder.RegisterService(&service);
//	unique_ptr<Server> server(builder.BuildAndStart());
//	cout << "Server is listening on " << server_address << endl;
//	server->Wait();
//}

int responseCount;

static Status ProcessSimpleRPC(const DataChunkRequest* request, DataChunkSummary* response) {
	responseCount++;
	std::cout << "Received message" << std::endl;
	return Status::OK;
}

class ServerRpcContext {
public:
	ServerRpcContext() { }
	virtual ~ServerRpcContext() { }

	virtual bool RunNextState(bool) = 0;  // next state, return false if done
	virtual void Reset() = 0;             // start this back at a clean state
};

class ServerRpcContextDataStream GRPC_FINAL : public ServerRpcContext {
public:
	ServerRpcContextDataStream(
			std::function<void(ServerContext *ctx, DataChunkRequest *, grpc::ServerAsyncResponseWriter<DataChunkSummary> *, void *)> request_method,
			std::function<grpc::Status(const DataChunkRequest *, DataChunkSummary *)> invoke_method)
	: srv_ctx_(new ServerContext),
	next_state_(&ServerRpcContextDataStream::invoker),
	request_method_(request_method),
	invoke_method_(invoke_method),
	response_writer_(srv_ctx_.get())
	{
		request_method_(srv_ctx_.get(), &req_, &response_writer_, (void *)this);
	}

	~ServerRpcContextDataStream() GRPC_OVERRIDE {}

	bool RunNextState(bool ok) GRPC_OVERRIDE {
		return (this->*next_state_)(ok);
	}
	void Reset() GRPC_OVERRIDE {
		srv_ctx_.reset(new ServerContext);
		req_ = DataChunkRequest();
		response_writer_ = grpc::ServerAsyncResponseWriter<DataChunkSummary>(srv_ctx_.get());

		// Then request the method
		next_state_ = &ServerRpcContextDataStream::invoker;
		request_method_(srv_ctx_.get(), &req_, &response_writer_, (void *)this);
	}

private:
	bool finisher(bool) {return false;}
	bool invoker(bool ok) {
		if (!ok) {
			return false;
		}

		DataChunkSummary response;
		grpc::Status status = invoke_method_(&req_, &response);

		// Have the response writer work and invoke on_finish when done
		next_state_ = &ServerRpcContextDataStream::finisher;
		response_writer_.Finish(response, status, (void *)this);
		return true;
	}

	std::unique_ptr<ServerContext> srv_ctx_;
	DataChunkRequest req_;
	bool (ServerRpcContextDataStream::*next_state_)(bool);

	std::function<void(ServerContext *ctx, DataChunkRequest *, grpc::ServerAsyncResponseWriter<DataChunkSummary> *, void *)> request_method_;
	std::function<grpc::Status(const DataChunkRequest *, DataChunkSummary *)> invoke_method_;
	grpc::ServerAsyncResponseWriter<DataChunkSummary> response_writer_;

};

class ServerImpl {

private:
	ServerBuilder builder;
	std::vector<std::unique_ptr<grpc::ServerCompletionQueue>> srv_cqs_;
	std::forward_list<ServerRpcContext *> contexts_;
	std::vector<std::thread> threads_;

	DataStream::AsyncService service_;
	std::unique_ptr<Server> server_;
	int num_threads_;

public:
	ServerImpl() {
		num_threads_ = 5;
		std::cout << "Listening at 10.88.5.100:50051" << std::endl;
		std::string server_address("10.88.5.100:50051");
		builder.AddListeningPort(server_address,
				grpc::InsecureServerCredentials());
		builder.RegisterService(&service_);
		builder.SetMaxMessageSize(1000*1024*1024);

		auto process_rpc_bound = std::bind(ProcessSimpleRPC, _1, _2);

		// Add one completion queue per thread
		for (int i = 0; i < num_threads_; i++) {
			srv_cqs_.emplace_back(builder.AddCompletionQueue());
		}

		server_ = builder.BuildAndStart();

		// Add a bunch of contexts
		for (int i = 0; i < 10000 / num_threads_; i++) {
			for (int j = 0; j < num_threads_; j++) {
				auto request_unary = std::bind(
						&DataStream::AsyncService::RequestSendDataStream, &service_,
						_1, _2, _3, srv_cqs_[j].get(), srv_cqs_[j].get(), _4);
				contexts_.push_front(
						new ServerRpcContextDataStream(request_unary,
								process_rpc_bound));
			}
		}

		for (int i = 0; i < num_threads_; i++) {
			shutdown_state_.emplace_back(new PerThreadShutdownState());
		}

		for (int i = 0; i < num_threads_; i++) {
			threads_.emplace_back(&ServerImpl::ThreadFunc, this, i);
		}

	}

	~ServerImpl() {
		for (auto thr = threads_.begin(); thr != threads_.end(); thr++) {
			thr->join();
		}
		server_->Shutdown();
		for (auto ss = shutdown_state_.begin(); ss != shutdown_state_.end();
				++ss) {
			(*ss)->set_shutdown();
		}
		for (auto cq = srv_cqs_.begin(); cq != srv_cqs_.end(); ++cq) {
			(*cq)->Shutdown();
			bool ok;
			void *got_tag;
			while ((*cq)->Next(&got_tag, &ok))
				;
		}
		while (!contexts_.empty()) {
			delete contexts_.front();
			contexts_.pop_front();
		}
	}

	void ThreadFunc(int rank) {
		// Wait until work is available or we are shutting down
		bool ok;
		void *got_tag;

		while (srv_cqs_[rank]->Next(&got_tag, &ok)) {
			ServerRpcContextDataStream *ctx =
					reinterpret_cast<ServerRpcContextDataStream *>(got_tag);

			// The tag is a pointer to an RPC context to invoke
			const bool still_going = ctx->RunNextState(ok);
			if (!shutdown_state_[rank]->shutdown()) {
				// this RPC context is done, so refresh it
				if (!still_going) {
					ctx->Reset();
				}
			} else {
				return;
			}
		}
		return;
	}

	class PerThreadShutdownState {
	public:
		PerThreadShutdownState() :
				shutdown_(false) {
		}

		bool shutdown() const {
			std::lock_guard<std::mutex> lock(mutex_);
			return shutdown_;
		}

		void set_shutdown() {
			std::lock_guard<std::mutex> lock(mutex_);
			shutdown_ = true;
		}

	private:
		mutable std::mutex mutex_;
		bool shutdown_;
	};

	std::vector<std::unique_ptr<PerThreadShutdownState>> shutdown_state_;
};

int main(int argc, char** argv) {
	cout << "DataStreamServer" << endl;
//	RunServer();
	ServerImpl server;

	return 0;
}
