#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int capacity, heapsize;

/* A utility function to swap two elements */
void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}
  
/* to get index of left child of node at index i */
int left(int i) 
{
  return (2*i + 1); 
}

/* to get index of right child of node at index i */
int right(int i) 
{ 
  return (2*i + 2); 
}

void max_heapify(int *arr, int index) 
{
  int leftChild;
  int rightChild;
  int largest;
  int temp;

  leftChild = left(index);
  rightChild = right(index);

  if (leftChild <= heapsize && arr[leftChild] > arr[index]) {
    largest = leftChild;
  } 
  else {
    largest = index;
  }

  if (rightChild < heapsize && arr[rightChild] > arr[largest]) {
    largest = rightChild;
  }
  if (largest != index) {
    swap(&arr[largest], &arr[index]);
    max_heapify(arr, largest);
  }
}

void build_max_heap(int *arr)
{
  int i;
  for (i = capacity/2; i >= 1; i--) {
    max_heapify(arr, i);
  }
}

int maximum(int *arr) 
{
  return arr[1];
}

int extract_max(int *arr) 
{
  int max, temp;
  max = arr[1];
  temp = arr[1];
  arr[1] = arr[heapsize];
  arr[heapsize] = temp;
  heapsize--;
  max_heapify(arr, 1);
  return max;
}
/**
 * Applications
 * *Suitable for applications dealing with priority
 * *Scheduling algorithm
 * *Caching
*/
int main() 
{  
  int i, val, num;
  int arr[11] = {0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
  heapsize = capacity = 7;
  build_max_heap(arr);
  val = maximum(arr);
  printf("\n\n maximum value=%d", val);
  printf("\n display element of max heap pririty queue: ");

  for (i = 1; i <= capacity; i++) {
    printf("%d ", arr[i]);
  }

  val = extract_max(arr);
  printf("\n extract maximum value=%d", val);
  return 0;
}