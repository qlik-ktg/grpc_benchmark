#include "report.h"

#include <fstream>

#include <grpc/support/log.h>
#include "../driver.h"
#include "parse_json.h"
#include "stats.h"

namespace grpc {
namespace testing {

void CompositeReporter::add(std::unique_ptr<Reporter> reporter) {
    reporters_.emplace_back(std::move(reporter));
}

void CompositeReporter::ReportQPS(const ScenarioResult& result) {
    for (size_t i = 0; i < reporters_.size(); ++i) {
        reporters_[i]->ReportQPS(result);
    }
}

void CompositeReporter::ReportQPSPerCore(const ScenarioResult& result) {
    for (size_t i = 0; i < reporters_.size(); ++i) {
        reporters_[i]->ReportQPSPerCore(result);
    }
}

void CompositeReporter::ReportLatency(const ScenarioResult& result) {
    for (size_t i = 0; i < reporters_.size(); ++i) {
        reporters_[i]->ReportLatency(result);
    }
}

void CompositeReporter::ReportTimes(const ScenarioResult& result) {
    for (size_t i = 0; i < reporters_.size(); ++i) {
        reporters_[i]->ReportTimes(result);
    }
}

void GprLogReporter::ReportQPS(const ScenarioResult& result) {
    gpr_log(GPR_INFO, "QPS: %.1f", result.summary().qps());
}

void GprLogReporter::ReportQPSPerCore(const ScenarioResult& result) {
    gpr_log(GPR_INFO, "QPS: %.1f (%.1f/server core)", result.summary().qps(),
            result.summary().qps_per_server_core());
}

void GprLogReporter::ReportLatency(const ScenarioResult& result) {
    gpr_log(GPR_INFO,
            "Latencies (50/90/95/99/99.9%%-ile): %.1f/%.1f/%.1f/%.1f/%.1f us",
            result.summary().latency_50() / 1000,
            result.summary().latency_90() / 1000,
            result.summary().latency_95() / 1000,
            result.summary().latency_99() / 1000,
            result.summary().latency_999() / 1000);
}

void GprLogReporter::ReportTimes(const ScenarioResult& result) {
    gpr_log(GPR_INFO, "Server system time: %.2f%%",
            result.summary().server_system_time());
    gpr_log(GPR_INFO, "Server user time:   %.2f%%",
            result.summary().server_user_time());
    gpr_log(GPR_INFO, "Client system time: %.2f%%",
            result.summary().client_system_time());
    gpr_log(GPR_INFO, "Client user time:   %.2f%%",
            result.summary().client_user_time());
}

void JsonReporter::ReportQPS(const ScenarioResult& result) {
    grpc::string json_string = SerializeJson(result,
            "type.googleapis.com/grpc.testing.ScenarioResult");
    std::ofstream output_file(report_file_);
    output_file << json_string;
    output_file.close();
}

void JsonReporter::ReportQPSPerCore(const ScenarioResult& result) {
    // NOP - all reporting is handled by ReportQPS.
}

void JsonReporter::ReportLatency(const ScenarioResult& result) {
    // NOP - all reporting is handled by ReportQPS.
}

void JsonReporter::ReportTimes(const ScenarioResult& result) {
    // NOP - all reporting is handled by ReportQPS.
}

}  // namespace testing
}  // namespace grpc
