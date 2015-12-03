#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

typedef struct slice slice;
struct slice {
    int len;
    size_t cap;
    char *bytes;
};

void free_slice(slice *s)
{
    free(s->bytes);
}

static void slice_grow(slice *self)
{
    self->cap = 1.6*self->cap;
    self->bytes = realloc(self->bytes, self->cap); 
}

void appendn(slice *self, char *str, size_t n)
{
    while ((self->len + n + 1) > self->cap){
        slice_grow(self);
    } 
    
    char *dst = self->bytes + self->len;
    memcpy(dst, str, n); 
    self->len = self->len+n;
    self->bytes[self->len] = '\0';
}

void slice_appendn(slice *self, char *str, size_t n){
    appendn(self, str, n);
}

int slice_printf(slice *self, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int len;

    while(1){
        va_list args;
        va_copy(args,ap);
        len = vsnprintf(self->bytes + self->len, self->cap - self->len, format, args); 

        if (len<0){
            printf("failed\n");
            return -1;
        }
        
        if ((size_t)len + 1 <= self->cap - self->len){
            self->len += len;
            break;
        } 

        slice_grow(self);
    }

    return 0;
}

void slice_append(slice *self, char *str)
{
    size_t n = strlen(str);
    appendn(self, str, n);
}

void append(slice *self, char *str)
{
    size_t n = strlen(str);
    appendn(self, str, n);
}

slice* make_slice()
{
    slice *self = malloc(sizeof(slice));
    self->len = 0;
    self->cap = 16;
    self->bytes = malloc(sizeof(char)*16); 
    self->bytes[0] = '\0';
    return self;
}
