#ifndef UTILS_ENV_H_
#define UTILS_ENV_H_

#include <stdio.h>

#include <grpc/support/slice.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Env utility functions */

/* Gets the environment variable value with the specified name.
 Returns a newly allocated string. It is the responsability of the caller to
 gpr_free the return value if not NULL (which means that the environment
 variable exists). */
char *gpr_getenv(const char *name);

/* Sets the the environment with the specified name to the specified value. */
void gpr_setenv(const char *name, const char *value);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_ENV_H_ */
