/*
 * limit_cores.h
 *
 *  Created on: Sep 1, 2016
 *      Author: khoanguyen
 */

#pragma once

#ifndef UTILS_LIMIT_CORES_H_
#define UTILS_LIMIT_CORES_H_

namespace grpc {
namespace testing {
/// LimitCores: allow this worker to only run on the cores specified in the
/// array \a cores, which is of length \a cores_size.
///
/// LimitCores takes array and size arguments (instead of vector) for direct
/// conversion from repeated field of protobuf. Use a cores_size of 0 to remove
/// existing limits (from an empty repeated field)
int LimitCores(const int *cores, int cores_size);
}  // namespace testing
}  // namespace grpc

#endif /* UTILS_LIMIT_CORES_H_ */
