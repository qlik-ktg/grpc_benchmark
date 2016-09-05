
#ifndef SOURCE_DIRECTORY__DRIVER_H_
#define SOURCE_DIRECTORY__DRIVER_H_


#include <memory>

#include "control.grpc.pb.h"
#include "utils/histogram.h"

namespace grpc {
namespace testing {

std::unique_ptr<ScenarioResult> RunScenario(
    const grpc::testing::ClientConfig& client_config, size_t num_clients,
    const grpc::testing::ServerConfig& server_config, size_t num_servers,
    int warmup_seconds, int benchmark_seconds, int spawn_local_worker_count);

bool RunQuit();
}  // namespace testing
}  // namespace grpc


#endif /* SOURCE_DIRECTORY__DRIVER_H_ */
