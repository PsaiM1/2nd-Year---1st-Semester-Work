#include "graph.h"
#include <stdio.h>
/*
Author: PrasannaSai Meruga
Section: Majeed 10 AM

This program is an implementation of a directed graph using dynamic 
memory allocation as a method of storing the verticies and edges of the graph.
It also uses linked lists as they way to store the memory that was allocated.
 */

int has_vertex(Graph graph, const char name[]); /*so it can be used legally*/

/*
Initializes the graph by setting its only field to NULL so it can be used
properly with the other functions. 
Since graph has a memory address passed in via the pointer
theres no need to use malloc on it.
 */
void init_graph(Graph *graph) {
  /*graph already has a memory address*/
  if (graph != NULL) {
    graph->verthead = NULL; /*set the vert list to null*/
  } 
}

/*
Adds a vertex to the graph. It checks if its the vertex and initializes 
everything accordingly and if not it will simply iteratre through the list of
vertices and add the new vertex at the end

Returns 1 if successful 
Return 0 if failed or vertex already exists in the graph
 */
int add_vertex(Graph *graph, const char new_vertex[]) {
  Node *temp = malloc(sizeof(Node));
  Node *curr;
  if (new_vertex != NULL && graph != NULL) {
    temp->vert.data = malloc((sizeof(char) * strlen(new_vertex)) + 1);
    temp->vert.edgelist = NULL;
    strncpy(temp->vert.data, new_vertex, strlen(new_vertex));
  } else {
    return 0; /* the new_vertex was NULL */
  }
  if (graph->verthead == NULL) { /*theres no head to the linked list*/
    graph->verthead = temp;
    graph->verthead->vert.data = temp->vert.data;
    graph->verthead->vert.edgelist = temp->vert.edgelist;
    strncpy(graph->verthead->vert.data, new_vertex, strlen(new_vertex));
    return 1;
  } else if (has_vertex(*graph, new_vertex) == 0){ /*if doesn't contain*/
    curr = graph->verthead;
    while (curr->next != NULL) {
      curr = curr->next;
    }
    curr->next = temp;
    return 1;
  } else { /*failure*/
    return 0;
  }
}

/*
Checks if the vertex exists within the graph. It simply iterates
through the list of vertices until it reaches the requested vertex

Returns 1 if vertex name is in the graph
Returns 0 if vertex is not in the graph
 */
int has_vertex(Graph graph, const char name[]) {
  Node *curr;
  if (graph.verthead != NULL && name != NULL) {
    curr = graph.verthead;
    while (curr->next != NULL) {
      if (strcmp(curr->vert.data, name) == 0) { /*if names are same*/
	return 1;
      } else { /* else iterate*/
	curr = curr->next;
      }
    }

    if (strcmp(curr->vert.data, name) == 0) { /*check last node*/
      return 1;
    }
    return 0; 
  } else { /*empty link means no vertex*/
    return 0;
  }
  return 0;
}

/*
Counts how many vertices exist within the graph. Simply iterates and counts

Returns the number of verts in the graph
so anything 0 or higher
 */
int num_vertices(Graph graph) {
  Node *curr;
  int sum = 0;
  if (graph.verthead != NULL) { /*at least 1 exists*/
    curr = graph.verthead;
    do {
      sum++;
      curr = curr->next;
    } while(curr != NULL);
  } else { /*no verticies*/
    return sum;
  }
  return sum;
}

/*
Adds an edge to the function that starts from the source vertex and
points to the dest vertex and is assigned a cost. It checks whether a 
edge is being added for the first time and initializes the edge list
accordingly.

Returns 1 if an edge is successfully added
Returns 0 if the edge couldn't be added due to 
- negative cost
- source or dest dont exist in the graph
- an edge already exists going from source to dest
 */
int add_edge(Graph *graph, const char source[], const char dest[], int cost) {
  Node *curr;
  Node *curr2;
  Edge *curredge;
  Edge *temp = malloc(sizeof(Edge));
  
  
  if (graph != NULL && cost >= 0 && has_vertex(*graph, source) &&
      has_vertex(*graph, dest) && source != NULL && dest != NULL) {
    curr = graph->verthead;
    do {
      if (strcmp(curr->vert.data, source) == 0 && curr->vert.edgelist != NULL) {
	curredge = curr->vert.edgelist;
	do {
	  if (strcmp(curredge->dest_vertex->vert.data, dest) == 0) {
	    return 0; /* edge already exists */
	  } else {
	    curredge = curredge->next_edge;
	  }
	} while (curredge != NULL);
	curr2 = graph->verthead;
	do {
	  if (strcmp(curr2->vert.data, dest) == 0) { /*if at dest vertex*/
	    curredge = curr->vert.edgelist; /*is set at source vertex*/
	    temp->dest_vertex = curr2;
	    temp->next_edge = NULL;
	    temp->cost = cost;
	    /*iterate to end of source edgelist*/
	    while (curredge->next_edge != NULL) {
	      curredge = curredge->next_edge;
	    }
	    curredge->next_edge = temp;
	    /*curredge = temp; a new edge in the edge linked list*/
	    return 1;
	  } else { /*if not yet at dest vertex*/
	    curr2 = curr2->next;
	  }
	} while (curr2 != NULL);
      } else if (strcmp(curr->vert.data, source) == 0 &&
		 curr->vert.edgelist == NULL){ /*make the first edge*/
	curr2 = graph->verthead;
	curr->vert.edgelist = malloc(sizeof(Edge));
	do {
	  if (strcmp(curr2->vert.data, dest) == 0) { /*if at dest vertex*/
	    curr->vert.edgelist->dest_vertex = curr2;
	    curr->vert.edgelist->next_edge = NULL;
	    curr->vert.edgelist->cost = cost;
	    return 1;
	  } else { /*if not yet at dest vertex*/
	    curr2 = curr2->next;
	  }
	} while (curr2 != NULL);
      } else {
	curr = curr->next;
      }
    } while (curr != NULL);
  } else {
    return 0;
  }
  return 0;
}

/*
Gets the cost of the specified edge between source and dest. It 
iterates through source's edge list to find the edge to dest and then
returns its cost.

Returns the cost of the requested edge so zero or greater
Returns -1 if
- source or dest don't exist in the graph
- either source or dest are NULL
 */
int get_edge_cost(Graph graph, const char source[], const char dest[]) {
  Node *curr;
  Edge *curredge;

  if (source != NULL && dest != NULL && has_vertex(graph, source)
      && has_vertex(graph, dest) && source != NULL && dest != NULL) {
    curr = graph.verthead;
    do {
      if (strcmp(curr->vert.data, source) == 0 && curr->vert.edgelist != NULL) {
	curredge = curr->vert.edgelist;
	do {
	  if (strcmp(curredge->dest_vertex->vert.data, dest) == 0) {
	    return curredge->cost; /* edge already exists */
	  } else {
	    curredge = curredge->next_edge;
	  }
	} while (curredge != NULL);
	return -1; /*means no edge to dest exists for source*/
      } else if (strcmp(curr->vert.data, source) == 0
		 && curr->vert.edgelist == NULL) {
	return -1; /*means no edge to dest exists for source*/
      } else {
	curr = curr->next;
      }
    } while (curr != NULL);
  }
    
  return -1;
}

/*
Changes the edge cost of the requested edge between source and dest
It will iterate through sources's edge list to find the relevant edge
and then it will take the cost and alter it.

Returns 1 if the change was successful
Returns 0 if:
- new_cost is negative
- source or dest are not in the graph
- source and dest don't have an edge between them
 */
int change_edge_cost(Graph *graph, const char source[], const char dest[],
		     int new_cost) {
  Node *curr;
  Edge *curredge;

  if (graph != NULL && source != NULL && dest != NULL &&
      has_vertex(*graph, source) && has_vertex(*graph, dest) && new_cost >= 0
      && source != NULL && dest != NULL) {
    curr = graph->verthead;
    do {
      if (strcmp(curr->vert.data, source) == 0 && curr->vert.edgelist != NULL) {
	curredge = curr->vert.edgelist;
	do {
	  if (strcmp(curredge->dest_vertex->vert.data, dest) == 0) {
	    curredge->cost = new_cost; /* edge already exists */
	    return 1;
	  } else {
	    curredge = curredge->next_edge;
	  }
	} while (curredge != NULL);
	return 0; /* no edge exists */
      } else if (strcmp(curr->vert.data, source) == 0
		 && curr->vert.edgelist == NULL) {
	return 0; /*no edge exists */
      } else {
	curr = curr->next;
      }
    } while (curr != NULL);
  }
    
  return 0;
}

/*
Counts the number of neighbors a particular vertex has. It finds the 
requested vertex and then counts how many edges it has in its edge list.

Returns the number of neighbors counted so zero or greater
Returns -1 if 
- vertex doesnt exist in the graph
- vertex is NULL
 */
int num_neighbors(Graph graph, const char vertex[]) {
  Node *curr;
  Edge *curredge;
  int sum = 0;
  curr = graph.verthead;
  if (vertex != NULL && has_vertex(graph, vertex)) {
    do {
      if (strcmp(curr->vert.data, vertex) == 0 && curr->vert.edgelist != NULL) {
	curredge = curr->vert.edgelist; /*found the vertex so set edges*/
	if (curredge != NULL) {
	  do {
	    sum++;
	    curredge = curredge->next_edge;
	  } while (curredge != NULL);
	}
	return sum; /*all edges have been iterated through*/
      } else if (strcmp(curr->vert.data, vertex) == 0
		 && curr->vert.edgelist == NULL) {
	return sum; /*has no neighbors so sum is zero*/
      } else {
	curr = curr->next;
      }
    } while (curr != NULL);
  }
  return -1;
}
