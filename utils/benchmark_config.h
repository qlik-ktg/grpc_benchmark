#ifndef UTILS_BENCHMARK_CONFIG_H_
#define UTILS_BENCHMARK_CONFIG_H_

#include <memory>
#include <vector>

#include "report.h"

namespace grpc {
namespace testing {

void InitBenchmark(int* argc, char*** argv, bool remove_flags);

/** Returns the benchmark Reporter instance.
 *
 * The returned instance will take care of generating reports for all the actual
 * reporters configured via the "enable_*_reporter" command line flags (see
 * benchmark_config.cc). */
std::shared_ptr<Reporter> GetReporter();

}  // namespace testing
}  // namespace grpc

#endif /* UTILS_BENCHMARK_CONFIG_H_ */
