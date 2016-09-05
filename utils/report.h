#ifndef REPORT_H_
#define REPORT_H_


#include <memory>
#include <set>
#include <vector>

#include <grpc++/support/config.h>

#include "../driver.h"

namespace grpc {
namespace testing {

/** Interface for all reporters. */
class Reporter {
public:
    /** Construct a reporter with the given \a name. */
    Reporter(const string& name)
            : name_(name) {
    }

    virtual ~Reporter() {
    }

    /** Returns this reporter's name.
     *
     * Names are constants, set at construction time. */
    string name() const {
        return name_;
    }

    /** Reports QPS for the given \a result. */
    virtual void ReportQPS(const ScenarioResult& result) = 0;

    /** Reports QPS per core as (YYY/server core). */
    virtual void ReportQPSPerCore(const ScenarioResult& result) = 0;

    /** Reports latencies for the 50, 90, 95, 99 and 99.9 percentiles, in ms. */
    virtual void ReportLatency(const ScenarioResult& result) = 0;

    /** Reports system and user time for client and server systems. */
    virtual void ReportTimes(const ScenarioResult& result) = 0;

private:
    const string name_;
};

/** A composite for all reporters to be considered. */
class CompositeReporter: public Reporter {
public:
    CompositeReporter()
            : Reporter("CompositeReporter") {
    }

    /** Adds a \a reporter to the composite. */
    void add(std::unique_ptr<Reporter> reporter);

    void ReportQPS(const ScenarioResult& result) GRPC_OVERRIDE;
    void ReportQPSPerCore(const ScenarioResult& result) GRPC_OVERRIDE;
    void ReportLatency(const ScenarioResult& result) GRPC_OVERRIDE;
    void ReportTimes(const ScenarioResult& result) GRPC_OVERRIDE;

private:
    std::vector<std::unique_ptr<Reporter> > reporters_;
};

/** Reporter to gpr_log(GPR_INFO). */
class GprLogReporter: public Reporter {
public:
    GprLogReporter(const string& name)
            : Reporter(name) {
    }

private:
    void ReportQPS(const ScenarioResult& result) GRPC_OVERRIDE;
    void ReportQPSPerCore(const ScenarioResult& result) GRPC_OVERRIDE;
    void ReportLatency(const ScenarioResult& result) GRPC_OVERRIDE;
    void ReportTimes(const ScenarioResult& result) GRPC_OVERRIDE;
};

/** Dumps the report to a JSON file. */
class JsonReporter: public Reporter {
public:
    JsonReporter(const string& name, const string& report_file)
            : Reporter(name), report_file_(report_file) {
    }

private:
    void ReportQPS(const ScenarioResult& result) GRPC_OVERRIDE;
    void ReportQPSPerCore(const ScenarioResult& result) GRPC_OVERRIDE;
    void ReportLatency(const ScenarioResult& result) GRPC_OVERRIDE;
    void ReportTimes(const ScenarioResult& result) GRPC_OVERRIDE;

    const string report_file_;
};

}  // namespace testing
}  // namespace grpc



#endif /* REPORT_H_ */
