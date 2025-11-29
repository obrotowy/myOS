#include <string.h>

void* memset(void* restrict dest, int ch, size_t size) {
  unsigned char* c_dest = (unsigned char*) dest;
  for (size_t i = 0; i<size; ++i) {
    c_dest[i] = (unsigned char) ch;
  }
  return dest;
}