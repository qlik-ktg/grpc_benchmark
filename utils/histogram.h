#ifndef SOURCE_DIRECTORY__HISTOGRAM_H_
#define SOURCE_DIRECTORY__HISTOGRAM_H_

#include <grpc/support/histogram.h>
#include "stats.grpc.pb.h"

namespace grpc {
namespace testing {

class Histogram {
public:
    // TODO: look into making histogram params not hardcoded for C++
    Histogram()
            : impl_(
                    gpr_histogram_create(default_resolution(),
                            default_max_possible())) {
    }
    ~Histogram() {
        if (impl_)
            gpr_histogram_destroy(impl_);
    }
    Histogram(Histogram&& other)
            : impl_(other.impl_) {
        other.impl_ = nullptr;
    }

    void Merge(const Histogram& h) {
        gpr_histogram_merge(impl_, h.impl_);
    }
    void Add(double value) {
        gpr_histogram_add(impl_, value);
    }
    double Percentile(double pctile) const {
        return gpr_histogram_percentile(impl_, pctile);
    }
    double Count() const {
        return gpr_histogram_count(impl_);
    }
    void Swap(Histogram* other) {
        std::swap(impl_, other->impl_);
    }
    void FillProto(HistogramData* p) {
        size_t n;
        const auto* data = gpr_histogram_get_contents(impl_, &n);
        for (size_t i = 0; i < n; i++) {
            p->add_bucket(data[i]);
        }
        p->set_min_seen(gpr_histogram_minimum(impl_));
        p->set_max_seen(gpr_histogram_maximum(impl_));
        p->set_sum(gpr_histogram_sum(impl_));
        p->set_sum_of_squares(gpr_histogram_sum_of_squares(impl_));
        p->set_count(gpr_histogram_count(impl_));
    }
    void MergeProto(const HistogramData& p) {
        gpr_histogram_merge_contents(impl_, &*p.bucket().begin(),
                p.bucket_size(), p.min_seen(), p.max_seen(), p.sum(),
                p.sum_of_squares(), p.count());
    }

    static double default_resolution() {
        return 0.01;
    }
    static double default_max_possible() {
        return 60e9;
    }

private:
    Histogram(const Histogram&);
    Histogram& operator=(const Histogram&);

    gpr_histogram* impl_;
};
}
}

#endif /* SOURCE_DIRECTORY__HISTOGRAM_H_ */
