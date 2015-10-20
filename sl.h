

typedef struct sl{
  struct Node* head;
  int height;

} skiplist;


void add(skiplist *sl, char *key, char *value);

skiplist* create_skiplist(void);
