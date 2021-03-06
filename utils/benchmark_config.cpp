#include "benchmark_config.h"
#include <gflags/gflags.h>

DEFINE_bool(enable_log_reporter, true,
            "Enable reporting of benchmark results through GprLog");

DEFINE_string(scenario_result_file, "",
              "Write JSON benchmark report to the file specified.");

DEFINE_string(hashed_id, "", "Hash of the user id");

DEFINE_string(test_name, "", "Name of the test being executed");

DEFINE_string(sys_info, "", "System information");

DEFINE_string(server_address, "localhost:50052",
              "Address of the performance database server");

DEFINE_string(tag, "", "Optional tag for the test");

// In some distros, gflags is in the namespace google, and in some others,
// in gflags. This hack is enabling us to find both.
namespace google {}
namespace gflags {}
using namespace google;
using namespace gflags;

namespace grpc {
namespace testing {

void InitBenchmark(int* argc, char*** argv, bool remove_flags) {
  ParseCommandLineFlags(argc, argv, remove_flags);
}

static std::shared_ptr<Reporter> InitBenchmarkReporters() {
  auto* composite_reporter = new CompositeReporter;
  if (FLAGS_enable_log_reporter) {
    composite_reporter->add(
        std::unique_ptr<Reporter>(new GprLogReporter("LogReporter")));
  }
  if (FLAGS_scenario_result_file != "") {
    composite_reporter->add(std::unique_ptr<Reporter>(
        new JsonReporter("JsonReporter", FLAGS_scenario_result_file)));
  }

  return std::shared_ptr<Reporter>(composite_reporter);
}

std::shared_ptr<Reporter> GetReporter() {
  static std::shared_ptr<Reporter> reporter(InitBenchmarkReporters());
  return reporter;
}

}  // namespace testing
}  // namespace grpc
