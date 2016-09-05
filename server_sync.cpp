#include <thread>

#include <grpc++/security/server_credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/host_port.h>
#include <grpc/support/log.h>

#include "services.grpc.pb.h"
#include "server.h"
#include "utils/usage_timer.h"

namespace grpc {
namespace testing {

class BenchmarkServiceImpl GRPC_FINAL : public BenchmarkService::Service {
public:
    Status UnaryCall(ServerContext* context, const SimpleRequest* request,
            SimpleResponse* response) GRPC_OVERRIDE {
        if (request->response_size() > 0) {
            if (!Server::SetPayload(request->response_type(),
                            request->response_size(),
                            response->mutable_payload())) {
                return Status(grpc::StatusCode::INTERNAL, "Error creating payload.");
            }
        }
        return Status::OK;
    }
    Status StreamingCall(
            ServerContext* context,
            ServerReaderWriter<SimpleResponse, SimpleRequest>* stream) GRPC_OVERRIDE {
        SimpleRequest request;
        while (stream->Read(&request)) {
            SimpleResponse response;
            if (request.response_size() > 0) {
                if (!Server::SetPayload(request.response_type(),
                                request.response_size(),
                                response.mutable_payload())) {
                    return Status(grpc::StatusCode::INTERNAL, "Error creating payload.");
                }
            }
            stream->Write(response);
        }
        return Status::OK;
    }
};

class SynchronousServer GRPC_FINAL : public grpc::testing::Server {
public:
    explicit SynchronousServer(const ServerConfig& config) : Server(config) {
        ServerBuilder builder;

        char* server_address = NULL;

        gpr_join_host_port(&server_address, "::", port());
        builder.AddListeningPort(server_address,
                Server::CreateServerCredentials(config));
        gpr_free(server_address);

        builder.RegisterService(&service_);

        impl_ = builder.BuildAndStart();
    }

private:
    BenchmarkServiceImpl service_;
    std::unique_ptr<grpc::Server> impl_;
};

std::unique_ptr<grpc::testing::Server> CreateSynchronousServer(
        const ServerConfig& config) {
    return std::unique_ptr<Server>(new SynchronousServer(config));
}

}  // namespace testing
}  // namespace grpc
