#include <stdio.h>
#include <stdlib.h>


/* skeleton for linked list */
typedef struct _Node 
{
  int data;
  struct _Node *next;
} Node;

void findMiddle(Node *head) 
{
  Node *slow = head;
  Node *fast = head;
  if (head != NULL) {
    while (fast != NULL && fast->next != NULL) {
      fast = fast->next->next; //!< Step is 2 nodes
      slow = slow->next;       //!< Step is 1 node
    }
    printf(" Middle element is %d\n", slow->data);
  }
}

int main() 
{
  Node *head = NULL;
  Node *second = NULL;
  Node *third = NULL;
  Node *fourth = NULL;
  Node *fifth = NULL;
  Node *sixth = NULL;
  Node *seventh = NULL;
  Node *eighth = NULL;
  Node *ninth = NULL;
  Node *tenth = NULL;
  Node *eleventh = NULL;
  Node *twelfth = NULL;
  Node *thirteenth = NULL;

  head = (Node *)malloc(sizeof(Node));
  second = (Node *)malloc(sizeof(Node));
  third = (Node *)malloc(sizeof(Node));
  fourth = (Node *)malloc(sizeof(Node));
  fifth = (Node *)malloc(sizeof(Node));
  sixth = (Node *)malloc(sizeof(Node));
  seventh = (Node *)malloc(sizeof(Node));
  eighth = (Node *)malloc(sizeof(Node));
  ninth = (Node *)malloc(sizeof(Node));
  tenth = (Node *)malloc(sizeof(Node));
  eleventh = (Node *)malloc(sizeof(Node));
  twelfth = (Node *)malloc(sizeof(Node));
  thirteenth = (Node *)malloc(sizeof(Node));

  head->data       = 10;
  second->data     = 20;
  third->data      = 30;
  fourth->data     = 40;
  fifth->data      = 50;
  sixth->data      = 60;

  seventh->data    = 70;

  eighth->data     = 80;
  ninth->data      = 90;
  tenth->data      = 100;
  eleventh->data   = 110;
  twelfth->data    = 120;
  thirteenth->data = 130;

  /* Linking nodes */
  head->next       = second;
  second->next     = third;
  third->next      = fourth;
  fourth->next     = fifth;
  fifth->next      = sixth;
  sixth->next      = seventh;
  seventh->next    = eighth;
  eighth->next     = ninth;
  ninth->next      = tenth;
  tenth->next      = eleventh;
  eleventh->next   = twelfth;
  twelfth->next    = thirteenth;
  thirteenth->next = NULL;

  findMiddle(head);

  free(head);
  free(second);
  free(third);
  free(fourth);
  free(fifth);
  free(sixth);
  free(seventh);
  free(eighth);
  free(ninth);
  free(tenth);
  free(eleventh);
  free(twelfth);
  free(thirteenth);
  return 0;
}