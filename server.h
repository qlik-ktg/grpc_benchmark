#pragma once

#ifndef SOURCE_SERVER_H
#define SOURCE_SERVER_H

#include <grpc++/security/server_credentials.h>
#include <grpc/support/cpu.h>
#include <vector>

#include "control.grpc.pb.h"
#include "messages.grpc.pb.h"
#include "data/ssl_test_data.h"
#include "utils/port.h"
#include "utils/limit_cores.h"
#include "utils/usage_timer.h"

namespace grpc {
namespace testing {

class Server {
public:
    explicit Server(const ServerConfig& config)
            : timer_(new UsageTimer) {
        cores_ = LimitCores(config.core_list().data(), config.core_list_size());
        if (config.port()) {
            port_ = config.port();

        } else {
            port_ = grpc_pick_unused_port_or_die();
        }
    }
    virtual ~Server() {
    }

    ServerStats Mark(bool reset) {
        UsageTimer::Result timer_result;
        if (reset) {
            std::unique_ptr<UsageTimer> timer(new UsageTimer);
            timer.swap(timer_);
            timer_result = timer->Mark();
        } else {
            timer_result = timer_->Mark();
        }

        ServerStats stats;
        stats.set_time_elapsed(timer_result.wall);
        stats.set_time_system(timer_result.system);
        stats.set_time_user(timer_result.user);
        return stats;
    }

    static bool SetPayload(PayloadType type, int size, Payload* payload) {
        // TODO(yangg): Support UNCOMPRESSABLE payload.
        if (type != PayloadType::COMPRESSABLE) {
            return false;
        }
        payload->set_type(type);
        std::unique_ptr<char[]> body(new char[size]());
        payload->set_body(body.get(), size);
        return true;
    }

    int port() const {
        return port_;
    }
    int cores() const {
        return cores_;
    }
    static std::shared_ptr<ServerCredentials> CreateServerCredentials(
            const ServerConfig& config) {
        if (config.has_security_params()) {
            SslServerCredentialsOptions::PemKeyCertPair pkcp = {
                    test_server1_key, test_server1_cert };
            SslServerCredentialsOptions ssl_opts;
            ssl_opts.pem_root_certs = "";
            ssl_opts.pem_key_cert_pairs.push_back(pkcp);
            return SslServerCredentials(ssl_opts);
        } else {
            return InsecureServerCredentials();
        }
    }

private:
    int port_;
    int cores_;
    std::unique_ptr<UsageTimer> timer_;
};

std::unique_ptr<Server> CreateSynchronousServer(const ServerConfig& config);
std::unique_ptr<Server> CreateAsyncServer(const ServerConfig& config);
std::unique_ptr<Server> CreateAsyncGenericServer(const ServerConfig& config);

}  // namespace testing
}  // namespace grpc

#endif // SOURCE_SERVER_H
