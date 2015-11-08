#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sl.h"

unsigned char rndtable[256] = {
    0,   8, 109, 220, 222, 241, 149, 107,  75, 248, 254, 140,  16,  66 ,
    74,  21, 211,  47,  80, 242, 154,  27, 205, 128, 161,  89,  77,  36 ,
    95, 110,  85,  48, 212, 140, 211, 249,  22,  79, 200,  50,  28, 188 ,
    52, 140, 202, 120,  68, 145,  62,  70, 184, 190,  91, 197, 152, 224 ,
    149, 104,  25, 178, 252, 182, 202, 182, 141, 197,   4,  81, 181, 242 ,
    145,  42,  39, 227, 156, 198, 225, 193, 219,  93, 122, 175, 249,   0 ,
    175, 143,  70, 239,  46, 246, 163,  53, 163, 109, 168, 135,   2, 235 ,
    25,  92,  20, 145, 138,  77,  69, 166,  78, 176, 173, 212, 166, 113 ,
    94, 161,  41,  50, 239,  49, 111, 164,  70,  60,   2,  37, 171,  75 ,
    136, 156,  11,  56,  42, 146, 138, 229,  73, 146,  77,  61,  98, 196 ,
    135, 106,  63, 197, 195,  86,  96, 203, 113, 101, 170, 247, 181, 113 ,
    80, 250, 108,   7, 255, 237, 129, 226,  79, 107, 112, 166, 103, 241 ,
    24, 223, 239, 120, 198,  58,  60,  82, 128,   3, 184,  66, 143, 224 ,
    145, 224,  81, 206, 163,  45,  63,  90, 168, 114,  59,  33, 159,  95 ,
    28, 139, 123,  98, 125, 196,  15,  70, 194, 253,  54,  14, 109, 226 ,
    71,  17, 161,  93, 186,  87, 244, 138,  20,  52, 123, 251,  26,  36 ,
    17,  46,  52, 231, 232,  76,  31, 221,  84,  37, 216, 165, 212, 106 ,
    197, 242,  98,  43,  39, 175, 254, 145, 190,  84, 118, 222, 187, 136 ,
    120, 163, 236, 249
};

int rndindex = 0;

static double next_random (void)
{
    rndindex = (rndindex+1)&255;
    double result = rndtable[rndindex]/255.0;
  //  printf("%G\n", result);
    return result;
}

typedef struct Node{
  struct Node** nodes;
  char* value;
  char* key;
  int height;

} Node;

static Node* create_node(char *key, char *value, int height)
{
  Node *n = malloc(sizeof(Node));
  n->key=key;
  n->value=value;
  n->nodes = malloc(sizeof(Node*)*height);
  n->height=height;
  return n;
}

skiplist* create_skiplist(void){
  skiplist *sl = malloc(sizeof(skiplist));
  Node *head = malloc(sizeof(Node));
  sl->head = head;
  sl->head->value=NULL;
  sl->head->key=NULL;
  sl->head->nodes = malloc(sizeof(Node*)*20);
  return sl;
}


void add(skiplist *sl, char *key, char *value){

  int oldheight = sl->height;

  int height = 1;
  while(height<=oldheight && next_random()>=0.5){
    height+=1;
  }

  Node *node = create_node(key,value,height);

  Node *leadingNodes[oldheight];

  Node *current = sl->head;
  int i;
  for(i = oldheight-1;i>=0;i--){
    while(current->nodes[i]!=NULL &&strcmp(node->key, current->nodes[i]->key)>0){
      //printf("%s greater than %s\n",node->key,current->nodes[i]->key);
      current=current->nodes[i];
    }
    leadingNodes[i]=current;

  }
  int upheight = height;
  if (height>oldheight){
    sl->height=height;
    sl->head->nodes[height-1]=node;
    node->nodes[height-1]=NULL;
    upheight=oldheight;
  }

  for(i=0;i<upheight;i++){
    node->nodes[i]=leadingNodes[i]->nodes[i];
    leadingNodes[i]->nodes[i]=node;
  }
}

void delete(skiplist *sl, char *key)
{
  int i;
  Node *current = sl->head;

  for(i=sl->height-1;i>=0;i--){

    while(current->nodes[i]!=NULL){
      int k = strcmp(key, current->nodes[i]->key);

      if (k==0){
        current->nodes[i]=current->nodes[i]->nodes[i];
        break;
      }

      if (k<0){
        //printf("%s < %s\n", key, current->nodes[i]->key);
        break;
      }

      current=current->nodes[i];
    }
  }

}

char *get_value(skiplist *sl, char *key){
  int i;
  Node *current = sl->head;

  for(i=sl->height-1;i>=0;i--){

    while(current->nodes[i]!=NULL){
      int k = strcmp(key, current->nodes[i]->key);

      if (k==0){
        return current->nodes[i]->value;
      }

      if (k<0){
        //printf("%s < %s\n", key, current->nodes[i]->key);
        break;
      }

      current=current->nodes[i];
    }
  }

  return NULL;
}

/*

  for(i=sl->height-1;i>=0;i--){
    while(current->nodes[i]!=NULL && strcmp(key, current->nodes[i]->key)>=0){
      strcmp(key, current->nodes[i]->key)>=0
      printf("%s < %s\n", key, current->nodes[i]->key);
      current=current->nodes[i];
    }
    printf("droppin to %d\n",i);
  }

  return current->value;
*/

void print_skiplist(skiplist *sl){

  Node *node = sl->head;
  while(node->nodes[0]!=NULL){
    int k = 0;
    while(k<node->height){
      printf("%s ",node->value);
      k++;
    }
    printf("\n");
    node=node->nodes[0];
  }

}

void print_skiplist2(skiplist *sl){
  int i;
  int j;

  Node *current;
  printf("%s\n","----------");

  for (i = sl->height-1; i >=0; --i)
  {
    current = sl->head;
    while(current!=NULL){
      printf(" %s ",current->key);
      current=current->nodes[i];
    }
    printf("\n");
  }
}
