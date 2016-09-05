#ifndef UTILS_STRING_H_
#define UTILS_STRING_H_

#include <stddef.h>

#include <grpc/support/port_platform.h>
#include <grpc/support/slice.h>
#include <grpc/support/slice_buffer.h>

#ifdef __cplusplus
extern "C" {
#endif

/* String utility functions */

/* Flags for gpr_dump function. */
#define GPR_DUMP_HEX 0x00000001
#define GPR_DUMP_ASCII 0x00000002

/* Converts array buf, of length len, into a C string  according to the flags.
 Result should be freed with gpr_free() */
char *gpr_dump(const char *buf, size_t len, uint32_t flags);

/* Calls gpr_dump on a slice. */
char *gpr_dump_slice(gpr_slice slice, uint32_t flags);

/* Parses an array of bytes into an integer (base 10). Returns 1 on success,
 0 on failure. */
int gpr_parse_bytes_to_uint32(const char *data, size_t length,
        uint32_t *result);

/* Minimum buffer size for calling ltoa */
#define GPR_LTOA_MIN_BUFSIZE (3 * sizeof(long))

/* Convert a long to a string in base 10; returns the length of the
 output string (or 0 on failure).
 output must be at least GPR_LTOA_MIN_BUFSIZE bytes long. */
int gpr_ltoa(long value, char *output);

/* Minimum buffer size for calling int64toa */
#define GPR_INT64TOA_MIN_BUFSIZE (3 * sizeof(int64_t))

/* Convert an int64 to a string in base 10; returns the length of the
 output string (or 0 on failure).
 output must be at least GPR_INT64TOA_MIN_BUFSIZE bytes long.
 NOTE: This function ensures sufficient bit width even on Win x64,
 where long is 32bit is size.*/
int int64_ttoa(int64_t value, char *output);

/* Reverse a run of bytes */
void gpr_reverse_bytes(char *str, int len);

/* Pad a string with flag characters. The given length specifies the minimum
 field width. The input string is never truncated. */
char *gpr_leftpad(const char *str, char flag, size_t length);

/* Join a set of strings, returning the resulting string.
 Total combined length (excluding null terminator) is returned in total_length
 if it is non-null. */
char *gpr_strjoin(const char **strs, size_t nstrs, size_t *total_length);

/* Join a set of strings using a separator, returning the resulting string.
 Total combined length (excluding null terminator) is returned in total_length
 if it is non-null. */
char *gpr_strjoin_sep(const char **strs, size_t nstrs, const char *sep,
        size_t *total_length);

/** Split \a str by the separator \a sep. Results are stored in \a dst, which
 * should be a properly initialized instance. */
void gpr_slice_split(gpr_slice str, const char *sep, gpr_slice_buffer *dst);

/* A vector of strings... for building up a final string one piece at a time */
typedef struct {
    char **strs;
    size_t count;
    size_t capacity;
} gpr_strvec;

/* Initialize/destroy */
void gpr_strvec_init(gpr_strvec *strs);
void gpr_strvec_destroy(gpr_strvec *strs);
/* Add a string to a strvec, takes ownership of the string */
void gpr_strvec_add(gpr_strvec *strs, char *add);
/* Return a joined string with all added substrings, optionally setting
 total_length as per gpr_strjoin */
char *gpr_strvec_flatten(gpr_strvec *strs, size_t *total_length);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_STRING_H_ */
