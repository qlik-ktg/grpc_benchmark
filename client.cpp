#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <thread>

#include <boost/program_options.hpp>

#include <grpc++/grpc++.h>
#include <thread>

#include "indexlet_service.grpc.pb.h"
#include "execution_parameter.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using indexlet_service::SelectionRequest;
using indexlet_service::SelectionReply;
using indexlet_service::IndexletService;

using namespace std;
using namespace boost::program_options;

class IndexletServiceClient {
    struct AsyncClientCall {
        SelectionReply reply;
        ClientContext context;
        Status status;

        std::unique_ptr<ClientAsyncResponseReader<SelectionReply> > response_reader;
    };

    std::unique_ptr<IndexletService::Stub> stub_;

    CompletionQueue cq_;

public:
    explicit IndexletServiceClient(std::shared_ptr<Channel> channel)
        : stub_(IndexletService::NewStub(channel))
    { }

    void GetSelection(const std::vector<uint64_t>& sels) {
        SelectionRequest request;
        for(const auto& v : sels)
        	request.add_selections(v);

        AsyncClientCall* call = new AsyncClientCall;

        auto start = chrono::high_resolution_clock::now();
        call->response_reader = stub_->AsyncGetSelection(&call->context, request, &cq_);
        call->response_reader->Finish(&call->reply, &call->status, (void*)call);
        auto stop = chrono::high_resolution_clock::now();
        auto diff = (stop - start);
        cout << "GetSelection in " << chrono::duration<double,milli>(diff).count() << endl;
    }

    // loop while waiting for the completed responses
    void AsyncCompleteRpc() {
        void* got_tag;
        bool ok = false;

        while(cq_.Next(&got_tag, &ok)) {
            AsyncClientCall* call = reinterpret_cast<AsyncClientCall*>(got_tag);
            GPR_ASSERT(ok);
            if (call->status.ok()) {
            	auto start = chrono::high_resolution_clock::now();
            	auto resultSize = call->reply.selected_size();
            	vector<uint64_t> result(resultSize);
            	copy(call->reply.mutable_selected()->begin(), call->reply.mutable_selected()->end(), result.begin());
            	auto stop = chrono::high_resolution_clock::now();
            	auto diff = stop - start;
            	cout<< "Serialization: " << resultSize << " takes:\t\t " << chrono::duration<double, milli>(diff).count() << " ms" << endl;
            }
            else
                std::cout << "RPC failed" << std::endl;

            delete call;
        }
    }
}; // IndexletServiceClient

int main(int argc, char** argv) {
	try {
		string configFile;
		size_t numIterations = 100;

		options_description desc("Allowed options");
		desc.add_options()
		("help,h", "print usage message")
		("config,c", value<string>(&configFile)->required(), "path to execution configuration file")
		("numIteration,i", value<size_t>(&numIterations)->required(), "number of iterations");

		variables_map vm;
		try {
			store(parse_command_line(argc, argv, desc), vm);

			if (vm.count("help")) {
				cout << desc << endl;
				return 0;
			}
			notify(vm);
		} catch(const error& e) {
			cerr << "ERROR: " << e.what() << endl << endl;
			cerr << desc << endl;
			return 0;
		}

		ExecutionParameterParser paramParser(vm["config"].as<string>());
		auto& executionParam = paramParser.GetExecutionParameter();

		IndexletServiceClient indexletServiceClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
		std::thread thread_ = std::thread(&IndexletServiceClient::AsyncCompleteRpc, &indexletServiceClient);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, executionParam.nFirstSym);

		auto filterSize = executionParam.defaultSelectionStateSize;
		std::vector<uint64_t> filter(filterSize);
		for(auto i = 0; i < numIterations; ++i) {
			// generate filter
			std::generate_n(filter.begin(), filterSize, [&]() { return dist(gen); });

			indexletServiceClient.GetSelection(filter);
		}

		std::cout << "Press ctrl-c to quit" << std::endl << std::endl;
		thread_.join();
		cout << "Done" << endl;

		return 0;
	} catch(const exception& e) {
		cerr << e.what() << endl;
	}
}
