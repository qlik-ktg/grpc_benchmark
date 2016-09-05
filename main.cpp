#include <set>

#include <grpc/support/log.h>

#include "driver.h"
#include "utils/report.h"
#include "utils/benchmark_config.h"

namespace grpc {
namespace testing {

static const int WARMUP = 20;
static const int BENCHMARK = 20;

static void RunQPS() {
    gpr_log(GPR_INFO, "Running QPS test");

    ClientConfig client_config;
    client_config.set_client_type(ASYNC_CLIENT);
    client_config.set_outstanding_rpcs_per_channel(100);
    client_config.set_client_channels(64);
    client_config.set_async_client_threads(8);
    client_config.set_rpc_type(STREAMING);
    client_config.mutable_load_params()->mutable_closed_loop();

    ServerConfig server_config;
    server_config.set_server_type(ASYNC_SERVER);
    server_config.set_async_server_threads(8);

    const auto result = RunScenario(client_config, 1, server_config, 1, WARMUP, BENCHMARK, -2);

    GetReporter()->ReportQPSPerCore(*result);
    GetReporter()->ReportLatency(*result);
}

}  // namespace testing
}  // namespace grpc

int main(int argc, char** argv) {
    grpc::testing::InitBenchmark(&argc, &argv, true);

    grpc::testing::RunQPS();

    return 0;
}
