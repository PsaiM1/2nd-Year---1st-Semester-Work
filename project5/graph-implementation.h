#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if !defined(GRAPH_IMPLEMENTATION_H)
#define GRAPH_IMPLEMENTATION_H
/*
Author: PrasannaSai Meruga
Section: Majeed 10 AM

This program is an implementation of a directed graph using dynamic 
memory allocation as a method of storing the verticies and edges of the graph.
It also uses linked lists as they way to store the memory that was allocated.
 */

struct vertex;
struct node;
struct graph;

typedef struct edge { /* linked listed for edges */
  struct node *dest_vertex;
  struct edge *next_edge;
  int cost;
} Edge;

typedef struct vertex { /* contains the head of edge linked list */
  Edge *edgelist;
  char *data;
} Vertex;

typedef struct node { /* foundation for vertex's linked list*/
  Vertex vert;
  struct node *next;
} Node;

typedef struct graph {
  Node *verthead; /*Linked list to store the vertices*/
} Graph;

#endif


