#include "create_test_channel.h"

#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include "../data/ssl_test_data.h"

namespace grpc {

// When ssl is enabled, if server is empty, override_hostname is used to
// create channel. Otherwise, connect to server and override hostname if
// override_hostname is provided.
// When ssl is not enabled, override_hostname is ignored.
// Set use_prod_root to true to use the SSL root for connecting to google.
// In this case, path to the roots pem file must be set via environment variable
// GRPC_DEFAULT_SSL_ROOTS_FILE_PATH.
// Otherwise, root for test SSL cert will be used.
// creds will be used to create a channel when enable_ssl is true.
// Use examples:
//   CreateTestChannel(
//       "1.1.1.1:12345", "override.hostname.com", true, false, creds);
//   CreateTestChannel("test.google.com:443", "", true, true, creds);
//   same as above
//   CreateTestChannel("", "test.google.com:443", true, true, creds);
std::shared_ptr<Channel> CreateTestChannel(const grpc::string& server,
        const grpc::string& override_hostname, bool enable_ssl,
        bool use_prod_roots, const std::shared_ptr<CallCredentials>& creds,
        const ChannelArguments& args) {
    ChannelArguments channel_args(args);
    if (enable_ssl) {
        const char* roots_certs = use_prod_roots ? "" : test_root_cert;
        SslCredentialsOptions ssl_opts = { roots_certs, "", "" };

        std::shared_ptr<ChannelCredentials> channel_creds = SslCredentials(
                ssl_opts);

        if (!server.empty() && !override_hostname.empty()) {
            channel_args.SetSslTargetNameOverride(override_hostname);
        }
        const grpc::string& connect_to =
                server.empty() ? override_hostname : server;
        if (creds.get()) {
            channel_creds = CompositeChannelCredentials(channel_creds, creds);
        }
        return CreateCustomChannel(connect_to, channel_creds, channel_args);
    } else {
        return CreateChannel(server, InsecureChannelCredentials());
    }
}

std::shared_ptr<Channel> CreateTestChannel(const grpc::string& server,
        const grpc::string& override_hostname, bool enable_ssl,
        bool use_prod_roots, const std::shared_ptr<CallCredentials>& creds) {
    return CreateTestChannel(server, override_hostname, enable_ssl,
            use_prod_roots, creds, ChannelArguments());
}

std::shared_ptr<Channel> CreateTestChannel(const grpc::string& server,
        const grpc::string& override_hostname, bool enable_ssl,
        bool use_prod_roots) {
    return CreateTestChannel(server, override_hostname, enable_ssl,
            use_prod_roots, std::shared_ptr<CallCredentials>());
}

// Shortcut for end2end and interop tests.
std::shared_ptr<Channel> CreateTestChannel(const grpc::string& server,
        bool enable_ssl) {
    return CreateTestChannel(server, "foo.test.google.fr", enable_ssl, false);
}

}  // namespace grpc
