#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Skeleton for Queue */
typedef struct _queue
{
  int frontIndex;
  int rearIndex;
  int size;
  unsigned capacity;
  int *arr;
} queue;

/* to create queue */
queue * createQueue(unsigned capacity) 
{
  queue *que = (queue *)malloc(sizeof(queue));
  que->capacity = capacity;
  que->frontIndex = que->size = 0;
  que->rearIndex = capacity - 1;
  que->arr = (int *)malloc(que->capacity * sizeof(int));

  return que;
}

/* Queue is Full when size becomes equal to the capacity */
int isFull(queue *que) 
{
  /* Overflow condition */
  return (que->size == que->capacity);
}

/* To add an item to Queue */
void enqueue(queue *que, int item)
{
  if(isFull(que)) {
    return;
  }

  /* Finding the next rearIndex except the fisrt one */
  que->rearIndex = (que->rearIndex + 1) % que->capacity;

  /* Inserting element in the array */
  que->arr[que->rearIndex] = item;

  /* Incrementing the size */
  que->size = que->size + 1;
  printf("%d enqueued to queue\n", item);
}

/* Empty when size is 0 */
int isEmpty(queue *que)
{
  /* underflow condition */
  return (que->size == 0);
}

/* To remove an item from the Queue */
int dequeue(queue *que) 
{
  if (isEmpty(que)) {
    return INT_MIN;
  }

  /* Getting the last element */
  int item = que->arr[que->frontIndex];

  /* Finding the previouse frontIndex except the last one */
  que->frontIndex = (que->frontIndex + 1) % que->capacity;

  /* deincrimenting the size */
  que->size = que->size - 1;

  return item;
} 

/* To get the fisrt element */
int front(queue *que) 
{
  if (isEmpty(que)) {
    return INT_MIN;
  }

  return que->arr[que->frontIndex];
}

/* To get the last element */
int rear(queue * que)
{
  if (isEmpty(que)) {
    return INT_MIN;
  }

  return que->arr[que->rearIndex];
}


/**
 * Applications
 * *Scheduling
 * *Maintaning playlist
 * *Interrrupt handling 
*/
int main() 
{  
  queue *Queue = createQueue(1000);

  enqueue(Queue, 10);
  enqueue(Queue, 20);
  enqueue(Queue, 30);
  enqueue(Queue, 40);

  /**
   * evaluetes as
   * 10  <-- this is Front item
   * 20
   * 30
   * 40  <-- this is rear item
  */

  printf("%d dequeu from queue\n", dequeue(Queue));

  printf("Front item is %d\n", front(Queue));
  printf("Rear item is %d\n", rear(Queue));
  return 0;
}