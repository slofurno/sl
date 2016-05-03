#include "skiplist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char rndtable[256] = {
    0,   8,   109, 220, 222, 241, 149, 107, 75,  248, 254, 140, 16,  66,  74,
    21,  211, 47,  80,  242, 154, 27,  205, 128, 161, 89,  77,  36,  95,  110,
    85,  48,  212, 140, 211, 249, 22,  79,  200, 50,  28,  188, 52,  140, 202,
    120, 68,  145, 62,  70,  184, 190, 91,  197, 152, 224, 149, 104, 25,  178,
    252, 182, 202, 182, 141, 197, 4,   81,  181, 242, 145, 42,  39,  227, 156,
    198, 225, 193, 219, 93,  122, 175, 249, 0,   175, 143, 70,  239, 46,  246,
    163, 53,  163, 109, 168, 135, 2,   235, 25,  92,  20,  145, 138, 77,  69,
    166, 78,  176, 173, 212, 166, 113, 94,  161, 41,  50,  239, 49,  111, 164,
    70,  60,  2,   37,  171, 75,  136, 156, 11,  56,  42,  146, 138, 229, 73,
    146, 77,  61,  98,  196, 135, 106, 63,  197, 195, 86,  96,  203, 113, 101,
    170, 247, 181, 113, 80,  250, 108, 7,   255, 237, 129, 226, 79,  107, 112,
    166, 103, 241, 24,  223, 239, 120, 198, 58,  60,  82,  128, 3,   184, 66,
    143, 224, 145, 224, 81,  206, 163, 45,  63,  90,  168, 114, 59,  33,  159,
    95,  28,  139, 123, 98,  125, 196, 15,  70,  194, 253, 54,  14,  109, 226,
    71,  17,  161, 93,  186, 87,  244, 138, 20,  52,  123, 251, 26,  36,  17,
    46,  52,  231, 232, 76,  31,  221, 84,  37,  216, 165, 212, 106, 197, 242,
    98,  43,  39,  175, 254, 145, 190, 84,  118, 222, 187, 136, 120, 163, 236,
    249};

int rndindex = 0;

static double next_random(void) {
  rndindex = (rndindex + 1) & 255;
  double result = rndtable[rndindex] / 255.0;
  return result;
}

static skiplist *create_node(char *key, char *value, int height) {
  skiplist *n = malloc(sizeof(skiplist));
  n->key = key;
  n->value = value;
  n->nodes = malloc(sizeof(skiplist *) * height);
  n->height = height;
  return n;
}

skiplist *create_skiplist(void) {
  srand((unsigned int)time(NULL));
  skiplist *sl = malloc(sizeof(skiplist));
  sl->value = NULL;
  sl->key = NULL;
  sl->nodes = malloc(sizeof(skiplist *) * 20);
  sl->height = 0;
  return sl;
}

static void skiplist_free(skiplist *sl) {
  // TODO: copy key/value on add + free here
  free(sl->nodes);
  free(sl);
}

void skiplist_add(skiplist *head, char *key, char *value) {
  int oldheight = head->height;
  int height = 1;
  /*
  while(height <= oldheight && next_random() >= 0.5) {
    height += 1;
  }
  */

  int x = rand();
  while (height <= oldheight && ((x >>= 1) & 1)) {
    height += 1;
  }

  if (height > oldheight) {
    head->height = height;
  }

  skiplist *node = create_node(key, value, height);
  skiplist *current = head;
  int i;
  for (i = height - 1; i >= 0; i--) {
    while (current->nodes[i] != NULL &&
           strcmp(node->key, current->nodes[i]->key) > 0) {
      current = current->nodes[i];
    }

    node->nodes[i] = current->nodes[i];
    current->nodes[i] = node;
  }
}

char *skiplist_remove(skiplist *head, char *key) {
  int i;
  skiplist *current = head;
  skiplist *match = NULL;
  int height = head->height;
  for (i = height - 1; i >= 0; i--) {
    while (current->nodes[i] != NULL) {
      int k = strcmp(key, current->nodes[i]->key);
      if (k == 0) {
        match = current->nodes[i];
        current->nodes[i] = current->nodes[i]->nodes[i];
        break;
      }

      if (k < 0) {
        break;
      }

      current = current->nodes[i];
    }
  }

  if (match) {
    char *value = match->value;
    skiplist_free(match);
    return value;
  }

  return NULL;
}

void skiplist_delete(skiplist *head, char *key) {
  int i;
  skiplist *current = head;

  for (i = head->height - 1; i >= 0; i--) {
    while (current->nodes[i] != NULL) {
      int k = strcmp(key, current->nodes[i]->key);
      if (k == 0) {
        current->nodes[i] = current->nodes[i]->nodes[i];
        break;
      }

      if (k < 0) {
        // printf("%s < %s\n", key, current->nodes[i]->key);
        break;
      }

      current = current->nodes[i];
    }
  }
}

char *skiplist_search(skiplist *head, char *key) {
  int i;
  skiplist *current = head;

  for (i = head->height - 1; i >= 0; i--) {
    while (current->nodes[i] != NULL) {
      int k = strcmp(key, current->nodes[i]->key);
      if (k == 0) {
        return current->nodes[i]->value;
      }

      if (k < 0) {
        // printf("%s < %s\n", key, current->nodes[i]->key);
        break;
      }

      current = current->nodes[i];
    }
  }
  return NULL;
}

void skiplist_print(skiplist *head) {
  skiplist *cur = head->nodes[0];
  int k;

  while (cur != NULL) {
    k = cur->height;
    for (; k > 0; k--) {
      printf("%s ", cur->value);
    }
    printf("\n");
    cur = cur->nodes[0];
  }

  printf("height: %d\n", head->height);
}
