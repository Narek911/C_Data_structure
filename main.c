#include <stdio.h>
#include <stdlib.h>
 
/* A structure to represent an linked list node */
typedef struct _node
{
  int dest;
  struct _node* next;
} node;
 
/* A structure to represent an linked list */
typedef struct _list
{
  node *head;
} list;
 
/**
 * A structure to represent a graph. A graph
 * is an array of linked lists.
 * Size of array will be V (number of vertices
 * in graph)
 * */ 
typedef struct _graph
{
    int V;
    list* array;
} graph;
 
/* A utility function to create a new linked list node */
node* newLinkedListNode(int dest)
{
  node* newNode = (node*) malloc(sizeof(node));
  newNode->dest = dest;
  newNode->next = NULL;
  return newNode;
}
 
/* A utility function that creates a graph of V vertices */
graph* createGraph(int V)
{
  graph* Graph = (graph*) malloc(sizeof(graph));
  Graph->V = V;

  /**
   * Create an array of linked lists.  Size of
   * array will be V
  */
  Graph->array = (list *) malloc(V * sizeof(list));
 
  /**
   * Initialize each linked list as empty by
   * making head as NULL
  */
  for (int i = 0; i < V; ++i)
      Graph->array[i].head = NULL;

  return Graph;
}
 
/* Adds an edge to an undirected graph */
void addEdge(graph* Graph, int src, int dest)
{
  /**
   * Add an edge from src to dest.  A new node is
   * added to the linked list of src.  The node
   * is added at the beginning
  */
  node* newNode = newLinkedListNode(dest);
  newNode->next = Graph->array[src].head;
  Graph->array[src].head = newNode;

  /**
   * Since graph is undirected, add an edge from
   * dest to src also
  */
  newNode = newLinkedListNode(src);
  newNode->next = Graph->array[dest].head;
  Graph->array[dest].head = newNode;
}
 
/**
 * A utility function to print the linked list
 * representation of graph
*/
void printGraph(graph *Graph)
{
  for (int v = 0; v < Graph->V; ++v)
  {
    node* pCrawl = Graph->array[v].head;
    printf("\n linked list of vertex %d\n head ", v);
    while (pCrawl)
    {
      printf("-> %d", pCrawl->dest);
      pCrawl = pCrawl->next;
    }
    printf("\n");
  }
}
 
int main()
{
  /* create the graph given in above fugure */
  int V = 5;
  graph *  Graph= createGraph(V);
  addEdge(Graph, 0, 1);
  addEdge(Graph, 0, 4);
  addEdge(Graph, 1, 2);
  addEdge(Graph, 1, 3);
  addEdge(Graph, 1, 4);
  addEdge(Graph, 2, 3);
  addEdge(Graph, 3, 4);
  addEdge(Graph, 3, 5);
  addEdge(Graph, 3, 6);

  /* print the linked list representation of the above graph */
  printGraph(Graph);

  return 0; 
}