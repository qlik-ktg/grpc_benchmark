#ifndef UTILS_TEST_CONFIG_CPP_H_
#define UTILS_TEST_CONFIG_CPP_H_


namespace grpc {
namespace testing {

void InitTest(int* argc, char*** argv, bool remove_flags);

}  // namespace testing
}  // namespace grpc


#endif /* UTILS_TEST_CONFIG_CPP_H_ */
