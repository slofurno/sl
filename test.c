#include "sl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(){


  skiplist *sl = create_skiplist();

  char *key1="aaa";
  char *value1="value1";

  char *key2="bbb";
  char *value2="value2";

  char *key3="ccc";
  char *value3="value3";

  char *key4="ddd";
  char *value4="value4";

  char *key5="eee";
  char *value5="value5";

  char *key6="fff";
  char *value6="value6";

  add(sl, key1, value1);
  add(sl, key2, value2);
  add(sl, key3, value3);
  add(sl, key4, value4);
  add(sl, key5, value5);
  add(sl, key6, value6);

  print_skiplist(sl);

  return 0;
}
