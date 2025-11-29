#include <stdio.h>
#include <string.h>

int puts(const char* restrict str) {
  const size_t len = strlen(str);
  for (size_t i = 0; i<len; ++i) {
      putchar(str[i]);
  }
  return len;
}