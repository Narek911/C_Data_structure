#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 20

typedef struct _item {
  int data;
  int key;
} item;


item *hashArray[SIZE];
item *d_Item;
item *Item;

int hashCode(int key)
{
  return key % SIZE;
}

item *search(int key) 
{
  int hashIndex  = hashCode(key);

  /* move in array until an empty  */
  while (hashArray[hashIndex] != NULL) {
    if (hashArray[hashIndex]->key == key) {
      return hashArray[hashIndex];
    }

    /* go to next cell */
    ++hashIndex;

    /* wrap around the table */
    hashIndex %= SIZE;
  }

  return NULL;
}

void insert(int key, int data) 
{
  item *Item = (item *)malloc(sizeof(item));
  Item->data = data;
  Item->key = key;

  /* get the hash */
  int hashIndex  = hashCode(key);

  /* move in array until an empty or deleted cell */
  while (hashArray[hashIndex ] != NULL && hashArray[hashIndex ]->key != -1) 
  {
    /* go to next cell */
    ++hashIndex ;

    /* wrap around the table */
    hashIndex  %= SIZE;
  }
  hashArray[hashIndex ] = Item;
}

item *delete(item * Item) 
{
  int key = Item->key;

  /* get the hash */
  int hashIndex  = hashCode(key);
  
  while (hashArray[hashIndex] != NULL) {
    if (hashArray[hashIndex]->key == key) {
      item  *temp = hashArray[hashIndex];
      /* assign a dummy item at deleted position */
      hashArray[hashIndex] = d_Item;
      return temp;
    }

    /* go to next cell */
    ++hashIndex;

    /* wrap around the table */
    hashIndex %= SIZE;
  }
  
  return NULL;
}

/**
 * Applications
 * *Suitable for application need constant time fetching
 * *To resovlong the assocative elemetns
*/
int main() 
{  
  d_Item = (item *)malloc(sizeof(item));
  d_Item->data = -1;
  d_Item->key = -1;
  insert(1, 20); insert(2, 70);
  insert(42, 80); insert(4, 25);
  insert(12, 44); insert(14, 32);
  insert(17, 11); insert(13, 78);
  insert(37, 97);
  Item = search(37);
  if(Item != NULL) {
    printf("Element found %d\n", Item->data);
  }
  else {
    printf("Element not found\n");
  }

  delete(Item);

  Item = search(37);
  if(Item != NULL) {
    printf("Element found %d\n", Item->data);
  }
  else {
    printf("Element not found\n");
  }
  return 0;
}