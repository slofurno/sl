

typedef struct sl{
  struct Node* head;
  int height;

} skiplist;


void add(skiplist *sl, char *key, char *value);

char *get_value(skiplist *sl, char *key);

void delete(skiplist *sl, char *key);

skiplist* create_skiplist(void);
