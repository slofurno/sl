#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../skiplist.c"
#include "input.c"

int main(){

    skiplist *sl = create_skiplist();

    char *keys[] = {"one","two","three","four","five","six","seven","eight","nine","ten","eleven"};

    int testkey_sz = sizeof(testkeys)/sizeof(char*);
    printf("you have %d keys\n", testkey_sz);
    int test_sz = sizeof(keys)/sizeof(char*);
    printf("? %d\n", test_sz);

    char *steve = "steve";

    skiplist_add(sl, steve, steve);

    for (int i = 0; i < test_sz; i++){
        skiplist_add(sl, keys[i], keys[i]);
    }

    for (int i = 0; i < testkey_sz; i++){
        skiplist_add(sl, testkeys[i], testkeys[i]);
    }

    skiplist_print(sl);
    char *six = skiplist_search(sl, "six");

    printf("getting %s : %s\n", "six", six);

    char *am_i_steve = skiplist_remove(sl, steve);
    printf("steve?  %s\n", am_i_steve);

    char *am_i_null = skiplist_remove(sl, "Zzz");

    if (!am_i_null){
        printf("null as expected\n");
    }

    return 0;

}
