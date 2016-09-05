#include "test_config_cpp.h"
#include <gflags/gflags.h>

// In some distros, gflags is in the namespace google, and in some others,
// in gflags. This hack is enabling us to find both.
namespace google {}
namespace gflags {}
using namespace google;
using namespace gflags;

namespace grpc {
namespace testing {

void InitTest(int* argc, char*** argv, bool remove_flags) {
  ParseCommandLineFlags(argc, argv, remove_flags);
}

}  // namespace testing
}  // namespace grpc
