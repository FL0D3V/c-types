#ifndef _STRING_VIEW_H_
#define _STRING_VIEW_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct {
  size_t count;
  const char* string;
} string_view_t;

#endif // _STRING_VIEW_H_
