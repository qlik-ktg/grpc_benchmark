#ifndef UTILS_TEST_CONFIG_H_
#define UTILS_TEST_CONFIG_H_

#include <grpc/support/time.h>

#ifdef __cplusplus
extern "C" {
#endif /*  __cplusplus */

#ifndef GRPC_TEST_SLOWDOWN_BUILD_FACTOR
#define GRPC_TEST_SLOWDOWN_BUILD_FACTOR 1.0
#endif

#ifndef GRPC_TEST_SLOWDOWN_MACHINE_FACTOR
#define GRPC_TEST_SLOWDOWN_MACHINE_FACTOR 1.0
#endif

extern double g_fixture_slowdown_factor;

#define GRPC_TEST_SLOWDOWN_FACTOR                                        \
  (GRPC_TEST_SLOWDOWN_BUILD_FACTOR * GRPC_TEST_SLOWDOWN_MACHINE_FACTOR * \
   g_fixture_slowdown_factor)

#define GRPC_TIMEOUT_SECONDS_TO_DEADLINE(x)                                  \
  gpr_time_add(                                                              \
      gpr_now(GPR_CLOCK_MONOTONIC),                                          \
      gpr_time_from_millis((int64_t)(GRPC_TEST_SLOWDOWN_FACTOR * 1e3 * (x)), \
                           GPR_TIMESPAN))

#define GRPC_TIMEOUT_MILLIS_TO_DEADLINE(x)                                   \
  gpr_time_add(                                                              \
      gpr_now(GPR_CLOCK_MONOTONIC),                                          \
      gpr_time_from_micros((int64_t)(GRPC_TEST_SLOWDOWN_FACTOR * 1e3 * (x)), \
                           GPR_TIMESPAN))

#ifndef GRPC_TEST_CUSTOM_PICK_PORT
#define GRPC_TEST_PICK_PORT
#endif

void grpc_test_init(int argc, char **argv);

#ifdef __cplusplus
}
#endif /*  __cplusplus */

#endif /* UTILS_TEST_CONFIG_H_ */
