#ifndef STATS_H_
#define STATS_H_

#include <string>

#include "histogram.h"

namespace grpc {
namespace testing {

template<class T, class F>
double sum(const T& container, F functor) {
    double r = 0;
    for (auto v = container.begin(); v != container.end(); v++) {
        r += functor(*v);
    }
    return r;
}

template<class T, class F>
double average(const T& container, F functor) {
    return sum(container, functor) / container.size();
}

}  // namespace testing
}  // namespace grpc

#endif /* STATS_H_ */
