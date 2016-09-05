#include "limit_cores.h"

#include <grpc/support/cpu.h>
#include <grpc/support/log.h>
#include <grpc/support/port_platform.h>

#ifdef GPR_CPU_LINUX
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sched.h>

namespace grpc {
namespace testing {

int LimitCores(const int* cores, int cores_size) {
    const int num_cores = gpr_cpu_num_cores();
    int cores_set = 0;

    cpu_set_t* cpup = CPU_ALLOC(num_cores);
    GPR_ASSERT(cpup);
    const size_t size = CPU_ALLOC_SIZE(num_cores);
    CPU_ZERO_S(size, cpup);

    if (cores_size > 0) {
        for (int i = 0; i < cores_size; i++) {
            if (cores[i] < num_cores) {
                CPU_SET_S(cores[i], size, cpup);
                cores_set++;
            }
        }
    } else {
        for (int i = 0; i < num_cores; i++) {
            CPU_SET_S(i, size, cpup);
            cores_set++;
        }
    }
    bool affinity_set = (sched_setaffinity(0, size, cpup) == 0);
    CPU_FREE(cpup);
    return affinity_set ? cores_set : num_cores;
}

}  // namespace testing
}  // namespace grpc
#else
namespace grpc {
    namespace testing {

// LimitCores is not currently supported for non-Linux platforms
        int LimitCores(const int*, int) {return gpr_cpu_num_cores();}

    }  // namespace testing
}  // namespace grpc
#endif
