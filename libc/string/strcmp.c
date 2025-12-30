#include <string.h>

int strcmp(const char* lhs, const char* rhs) {
  int count = strlen(lhs);
  if (strlen(rhs) != count)
    return -1;
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