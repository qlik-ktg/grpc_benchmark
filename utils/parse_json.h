#ifndef PARSE_JSON_H_
#define PARSE_JSON_H_

#include <grpc++/impl/codegen/config_protobuf.h>
#include <grpc++/support/config.h>

namespace grpc {
namespace testing {

void ParseJson(const grpc::string& json, const grpc::string& type,
GRPC_CUSTOM_MESSAGE* msg);

grpc::string SerializeJson(const GRPC_CUSTOM_MESSAGE&msg,
const grpc::string& type);

}
  // testing
        }// grpc

#endif /* PARSE_JSON_H_ */
