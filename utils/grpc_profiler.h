#ifndef UTILS_GRPC_PROFILER_H_
#define UTILS_GRPC_PROFILER_H_

#ifdef __cplusplus
extern "C" {
#endif /*  __cplusplus */

void grpc_profiler_start(const char *filename);
void grpc_profiler_stop();

#ifdef __cplusplus
}
#endif /*  __cplusplus */

#endif /* UTILS_GRPC_PROFILER_H_ */
