#include <stdio.h>
#include <stdlib.h>

/* skeleton for stack */
typedef struct _stack {
  int topIndex;
  unsigned size;
  int* arr;
} stack;

/* to create stack */
stack* create(unsigned size) {
  stack* st = (stack *)malloc(sizeof(stack));
  st->size = size;
  st->topIndex = -1;
  st->arr = (int *)malloc(st->size * sizeof(int));

  return st;
}

/* Stack is full when top is equal to the last index (overflow condition)*/
int isFull(stack *st) {
  return st->topIndex == st->size - 1;
}

/* empty when top is -1 (end of flow condition)*/
int isEmpty(stack * st) {
  return st->topIndex == -1;
}

/* To add an item to stack */
void push(stack * st, int item) 
{
  /* Check if no overflow happen */
  if(isFull(st)) {
    return;
  }

  /* Pushing the element to the top */
  st->arr[++st->topIndex] = item;
}

/* To remove an item from stack */
int pop(stack *st) 
{
  /* Check if no end of flow happen */
  if(isEmpty(st)) {
    return -1;
  }

  return st->arr[st->topIndex--];
}

/* to get the top element */
int peek(stack *st) 
{
  /* Check if no end of flow happen */
  if(isEmpty(st)) {
    return -1;
  }

  return st->arr[st->topIndex];
}

void parseOperator(stack *st, char operator) 
{
    int arr[2];
    int result = 0;
    arr[0] = pop(st);
    arr[1] = pop(st);
    if (operator == '*') {
      result = arr[1] * arr[0];
    } else if (operator == '+') {
      result = arr[1] + arr[0];
    } else if (operator == '-') {
      result = arr[1] - arr[0];
    }
    
    push(st, result);
}

/**
 * Applications
 * *Recursion
 * *Parsing
 * *Browser
 * *Editors
*/
int main() 
{
  /**
   * Used in postfix evaluations
   * 2 3 1 * + 9 - 
   * /**
   * evaluetes as
   * - <-- this is top item
   * 9
   * +
   * *
   * 1
   * 3
   * 2
   * Algoritm is the folowing
   * ------------------------------result 5 - 9 == -4
   * - <-- the top element last evalutaion overator
   * 
   * -------------------------------
   * +  second evalutation operator 
   * --- result 3 + 2 == 5
   * * <-- first evalutaion operator
   * 1   result is 3 * 1 == 3
   * 3
   * ---
   * 2
   * -----------------------------
   * --------------------------------------------
  */
  stack *Stack = create(100);
  int arr[] = {2, 3, 1, '*', '+', 9, '-'};
  for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
    switch (arr[i]) {
      case '*': {
        parseOperator(Stack, '*'); 
        break;
      }
      case '+': {
        parseOperator(Stack, '+'); 
        break;
      }
      case '-': {
        parseOperator(Stack, '-'); 
        break;
      }
      default: {
        push(Stack, arr[i]);
      }
    }
  }
  
  printf("Result is %d\n", pop(Stack));
  return 0;
}