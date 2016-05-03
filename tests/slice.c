#include "../slice.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  slice *tevs = make_slice();
  char *msg = "AAAAAAAAAABB";

  slice_append(tevs, msg);
  printf("slice len: %d\n", tevs->len);

  slice_append(tevs, msg);
  printf("slice len: %d\n", tevs->len);

  slice_append(tevs, msg);
  printf("slice len: %d\n", tevs->len);

  slice_printf(tevs, " oOOooOoo %s :D:D:D:D", msg, 53);
  printf("slice len: %d\n", tevs->len);
  printf("%s\n", tevs->bytes);
}
