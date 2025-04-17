#include <string.h>

void* memmove(void* dest, const void* src, size_t size) {
    unsigned char* c_dest = (unsigned char*) dest;
    const unsigned char* c_src = (const unsigned char*) src;

    // Prevent memory corruption in case of memory regions overlap
    if (src < dest) {
        for (size_t i = 0; i<size; ++i) {
            c_dest[i] = c_src[i];
        }
    }
    else {
        for (size_t i = size; i!=0; --i) {
            c_dest[i] = c_src[i];
        }
    }
    return dest;
}