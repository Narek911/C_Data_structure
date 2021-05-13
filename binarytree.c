#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Skeleton for Binary Tree */
typedef struct _node
{
  int data;
  struct _node *left;
  struct _node *right;
} node;

/* To create tree */
node *createTree(int data) 
{
  /* Allocate memory for new node */
  node *nd = (node *)malloc(sizeof(node));

  /* Assign data ot this node */
  nd->data = data;

  /* Initalize left and right children as NULL */
  nd->left = NULL;
  nd->right = NULL;

  return nd;
}

/* print-left-right */
void preorder(node *nd)
{
  if (nd == NULL) {
    return;
  }

  printf("%d ", nd->data);

  preorder(nd->left);
  preorder(nd->right);
}

/* print-right-left */
void postorder(node *nd)
{
  if (nd == NULL) {
    return;
  }

  postorder(nd->left);
  postorder(nd->right);

  printf("%d ", nd->data);
}

/* left-print-rigth */
void inorder(node *nd)
{
  if (nd == NULL) {
    return;
  }

  inorder(nd->left);

  printf("%d ", nd->data);
  
  inorder(nd->right);
}

/**
 * Applications
 * *File system hierarchy
 * *Multiple variations of binary tree has wide variety of applications
*/
int main() 
{  
  node *root = createTree(1);
  root->left = createTree(2);
  root->right = createTree(3);
  root->left->left = createTree(4);
  printf("\nPreorder ");
  preorder(root);
  printf("\nPostorder ");
  postorder(root);
  printf("\ninorder ");
  inorder(root);
  return 0;
}