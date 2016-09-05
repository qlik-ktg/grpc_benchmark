#ifndef UTILS_CREATE_TEST_CHANNEL_H_
#define UTILS_CREATE_TEST_CHANNEL_H_

#include <memory>

#include <grpc++/security/credentials.h>

namespace grpc {
class Channel;

std::shared_ptr<Channel> CreateTestChannel(const grpc::string& server,
        bool enable_ssl);

std::shared_ptr<Channel> CreateTestChannel(const grpc::string& server,
        const grpc::string& override_hostname, bool enable_ssl,
        bool use_prod_roots);

std::shared_ptr<Channel> CreateTestChannel(const grpc::string& server,
        const grpc::string& override_hostname, bool enable_ssl,
        bool use_prod_roots, const std::shared_ptr<CallCredentials>& creds);

std::shared_ptr<Channel> CreateTestChannel(const grpc::string& server,
        const grpc::string& override_hostname, bool enable_ssl,
        bool use_prod_roots, const std::shared_ptr<CallCredentials>& creds,
        const ChannelArguments& args);

}  // namespace grpc

#endif /* UTILS_CREATE_TEST_CHANNEL_H_ */
