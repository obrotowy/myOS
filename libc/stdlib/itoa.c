#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void _swap(void* a, void* b) {
  unsigned char* c_a = (unsigned char*) a;
  unsigned char* c_b = (unsigned char*) b;
  unsigned char tmp = *c_a;
  *c_a = *c_b;
  *c_b = tmp;
}

void _reverse(void* arr, size_t size) {
  void* left_ptr = arr;
  void* right_ptr = arr+size-1;
  while (left_ptr < right_ptr) {
      _swap(left_ptr, right_ptr);
      ++left_ptr;
      --right_ptr;
  }
}

char* itoa(int value, char* str, const int base) {
  if (value == 0) {
    str[0] = '0';
    str[1] = '\0';
  }
  else {
    int digit = 0;
    bool is_negative = (value < 0);
    while (value != 0) {
      int current_digit = value % base;
      char current_char;
      if (current_digit < 10) {
          current_char = '0' + current_digit;
      }
      else {
          current_char = 'A' + current_digit % 10;
      }
      str[digit] = current_char;
      value /= base;
      ++digit;
    }
    if (is_negative) {
      str[digit] = '-';
      ++digit;
    }
    str[digit] = '\0';
    _reverse(str, digit);
  }
  return str;
}

char* uitoa(uint32_t value, char* str, const int base) {
  if (value == 0) {
    str[0] = '0';
    str[1] = '\0';
  }
  else {
    int digit = 0;
    while (value != 0) {
      int current_digit = value % base;
      char current_char;
      if (current_digit < 10) {
        current_char = '0' + current_digit;
      }
      else {
        current_char = 'A' + current_digit % 10;
      }
      str[digit] = current_char;
      value /= base;
      ++digit;
    }
    str[digit] = '\0';
    _reverse(str, digit);
  }
  return str;
}