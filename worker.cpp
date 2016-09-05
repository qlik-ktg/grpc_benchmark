#include <sys/signal.h>

#include <chrono>
#include <thread>

#include <gflags/gflags.h>
#include <grpc/grpc.h>
#include <grpc/support/time.h>

#include "qps_worker.h"
#include "utils/test_config_cpp.h"

DEFINE_int32(driver_port, 0, "Port for communication with driver");
DEFINE_int32(server_port, 0, "Port for operation as a server");

static bool got_sigint = false;

static void sigint_handler(int x) {
    got_sigint = true;
}

namespace grpc {
namespace testing {

static void RunServer() {
    QpsWorker worker(FLAGS_driver_port, FLAGS_server_port);

    while (!got_sigint && !worker.Done()) {
        gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME), gpr_time_from_seconds(5, GPR_TIMESPAN)));
    }
}

}  // namespace testing
}  // namespace grpc

int main(int argc, char** argv) {
    grpc::testing::InitTest(&argc, &argv, true);

    signal(SIGINT, sigint_handler);

    grpc::testing::RunServer();

    return 0;
}
