#include "usage_timer.h"

#include <grpc/support/time.h>
#include <sys/resource.h>
#include <sys/time.h>

UsageTimer::UsageTimer() : start_(Sample()) {}

double UsageTimer::Now() {
    auto ts = gpr_now(GPR_CLOCK_REALTIME);

    return ts.tv_sec + 1e-9 * ts.tv_nsec;
}

static double time_double(struct timeval* tv) {
    return tv->tv_sec + 1e-6 * tv->tv_usec;
}

UsageTimer::Result UsageTimer::Sample() {
    struct rusage usage;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    getrusage(RUSAGE_SELF, &usage);

    Result r;
    r.wall = time_double(&tv);
    r.user = time_double(&usage.ru_utime);
    r.system = time_double(&usage.ru_stime);

    return r;
}

UsageTimer::Result UsageTimer::Mark() const {
    Result s = Sample();
    Result r;
    r.wall = s.wall - start_.wall;
    r.user = s.user - start_.user;
    r.system = s.system - start_.system;

    return r;
}
