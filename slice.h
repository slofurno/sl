#ifndef SL_SLICE_INCLUDED
#define SL_SLICE_INCLUDED

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct slice slice;
struct slice {
  int len;
  size_t cap;
  char *bytes;
};

void free_slice(slice *s);

void appendn(slice *self, char *str, size_t n);

void slice_appendn(slice *self, char *str, size_t n);

int slice_printf(slice *self, const char *format, ...);

void slice_append(slice *self, char *str);

void append(slice *self, char *str);

slice *make_slice();

#endif
