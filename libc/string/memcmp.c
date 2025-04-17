#include <string.h>

int memcmp(const void* restrict lhs, const void* restrict rhs, size_t count) {
    int diff;
    const unsigned char* c_lhs = (const unsigned char*) lhs;
    const unsigned char* c_rhs = (const unsigned char*) rhs;
    size_t i = 0;
    do {
        diff = c_lhs[i] - c_rhs[i];
        ++i;
    } while (i<count && diff == 0);
    return diff;
}