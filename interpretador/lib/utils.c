#include "utils.h"
#include <string.h>

double convert_char(char *c) {
  double value;

  if (strlen(c) == 4) {
    switch (c[2]) {
    case 'a':
      value = '\a';
      break;
    case 'b':
      value = '\b';
      break;
    case 'f':
      value = '\f';
      break;
    case 'n':
      value = '\n';
      break;
    case 'r':
      value = '\r';
      break;
    case 't':
      value = '\t';
      break;
    case 'v':
      value = '\v';
      break;
    case '0':
      value = '\0';
      break;
    default:
      value = c[2];
      break;
    }
  } else {
    value = c[1];
  }

  return value;
}