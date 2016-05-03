#ifndef SL_SKIPLIST_INCLUDED
#define SL_SKIPLIST_INCLUDED

typedef struct skiplist skiplist;

struct skiplist {
  int height;
  char *value;
  char *key;
  skiplist **nodes;
};

void skiplist_add(skiplist *sl, char *key, char *value);

char *skiplist_search(skiplist *sl, char *key);

void skiplist_delete(skiplist *sl, char *key);

char *skiplist_remove(skiplist *sl, char *key);

void skiplist_print(skiplist *head);

skiplist *create_skiplist(void);

#endif
