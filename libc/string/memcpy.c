#include <string.h>

void* memcpy(void* restrict dest, const void* restrict src, size_t size) {
    unsigned char* c_dest = (unsigned char*) dest;
    const unsigned char* c_src = (const unsigned char*) src;
    for (size_t i = 0; i<size; ++i) {
        c_dest[i] = c_src[i];
    }
    return dest;
}