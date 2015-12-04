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

  char **inputs;

  char *line = NULL;
  size_t len = 0;
  int read;
  int bytes_read;

  //txt not text thanks for wasting an hour on this LETTER E
  FILE *fp = fopen("./strings.txt","rt");


  while ((read = getline(&line, &len, fp)) != -1) {
      //   printf("Retrieved line of length %zu %d :\n", read, len);
        //  printf("%s", line);
          char *keyval = malloc(sizeof(char)*len);
          strncpy(keyval, line, read-1);
          skiplist_add (sl, keyval, keyval);
  }

  fclose(fp);

  char *del1 = "0ziHrVsk";
  char *del2 = "32bSIsQF";
  char *del3 = "wGvvD2BV";

  skiplist_print (sl);

  skiplist_delete (sl, del1);
  skiplist_delete (sl, del2);
  skiplist_delete (sl, del3);



  skiplist_add (sl, del1, del1);
  skiplist_add (sl, del2, del2);
  skiplist_add (sl, del3, del3);

    char *mykey = "papa_steve";
    char *myval = ":D:D:D:D";

    skiplist_add(sl, mykey, myval);

    char *checkkey = skiplist_search(sl, mykey);

    //skiplist_print (sl);

    printf("is this your key: %s\n", checkkey);


/*
  while((bytes_read = getline (&my_string, nbytes, stdin))>=0){
    printf("read some byts %d\n",nbytes );
    add(sl, my_string, my_string);
    my_string=NULL;
    nbytes=0;
  }
  */



/*
  add(sl, key1, value1);
  add(sl, key2, value2);
  add(sl, key3, value3);
  add(sl, key4, value4);
  add(sl, key5, value5);
  add(sl, key6, value6);

  char *testkey = "ccc";

  char *answer1 = get_value(sl, testkey);
  printf("should be value3: %s\n", answer1);

  char *testkey2 = "a";

  char *answer2 = get_value(sl, testkey2);
  printf("should be NULL: %s\n", answer2);


  char *testkey3 = "z";

  char *answer3 = get_value(sl, testkey3);
  printf("should be NULL: %s\n", answer3);
*/
  skiplist_print (sl);

  return 0;
}
