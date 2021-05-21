# C Data Structures
1. Arrays
Arrays are liner data Structures

2. Linked list
Linked lists are liner data Structures
  They are dinamic in size
  They always have a head node
  They contains only homogeneous elements
In this case every element allocate the fixed amount of memory and its introduces as
struct _Node {
  int data;
  struct _Node *next;
} Node;
Where next is a pointer to the next lement in the linked list.
Each Element in the node contains value and the address of the next element in the list
The main element is head and it has mandatory rool in this type

3. Stack
It is a Liner data structure
Stack is a LIFO
It is impossible to delete, modify random element
The main methods are:
  .push(elem) -> push the element to the top
  .pop() -> removes the element from the top and return it
  .isEmpty() -> True or False
  .peek() -> return top element

4. Queue
It is a liner data structure
Queue is FIFO
It is possible to insert from the end 
It is possible to monitor the first and last elements
It is possible to remove the Front element
It is possible to add element from the rear end

5. Binary tree
This is a hierarchical data structure
  The top element is a root of tree
  Each node can have at maximum tow elements in the tree
  It is possible to access randomly using the index
There are tree types of Bynary tree:
  Preorder
  Postorder
  Inorder

6. Binary Search tree
In the case we have the following rules:
  the left node should always be less the the root node
  The right node should always be more then the root node
  It is possible to insert, delete, and sort elements easier teh in Binary Tree
  min, max
  sort, 
  Then the output is sorder it represented the valid BSD
  In order to get sorted BSD we should perform inorder traveling on the tree

7. Heap
It is complete Binary tree
Its represented as an array with arr[0] as an root element
It has langth and size
Min Heap and Max Heap
There is a formula to calculate the binary heap index
Min Heap is for the smallest element in the array
Max Heap is for the biggest element inthe array

8. Hashing
This is a technology for obtaining a data structure. It is like a dictionary in python
The hashing funciton is used
It maps elements to the storage address
It let us 
  chaining
  open addressing
It let us to delete, search the elements
To prevent a colosions just assinge Null to the element
It provide as a mechanism to have a key value pair and have a access to add, modify values using key just like in dictionaries

9. Graph.
G(V,E)
It's represents the connections, communications formed between to objects
Its used to get connections, short routing, min values, spanning tree