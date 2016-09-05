#include <grpc/support/port_platform.h>

#ifdef GPR_POSIX_ENV

#include "env.h"

#include <stdlib.h>

#include <grpc/support/log.h>

#include <grpc/support/string_util.h>
#include "src/core/lib/support/string.h"

char *gpr_getenv(const char *name) {
    char *result = getenv(name);
    return result == NULL ? result : gpr_strdup(result);
}

void gpr_setenv(const char *name, const char *value) {
    int res = setenv(name, value, 1);
    GPR_ASSERT(res == 0);
}

#endif /* GPR_POSIX_ENV */
