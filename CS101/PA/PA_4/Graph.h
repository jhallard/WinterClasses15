
// |===================================================================|
// ||  Author  - John Allard                                          ||     
// ||  ID      - 1437547                                              || 
// ||  CruzID  - jhallard                                             || 
// ||  Project - Programming Assignment #4                            ||                 
// ||  File    - Graph.c                                              || 
// ||  Info    - Implementation of the GraphObj data structure        ||                                             
// |===================================================================|

#ifndef GRAPH_H_JOHN_A_CS101
#define GRAPH_H_JOHN_A_CS101

#define INF  -2
#define NIL  -1

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// typedef our private struct as a user accessable Graph class
typedef struct GraphObj * Graph;

// @func - Constructor
// @args - #1 number of vertices in this graph
// @info - Pre : n > 0
Graph newGraph(int num);

// @func - freeGraph
// @args - pointer to a graph, which is a double pointer to a GraphObj struct
void freeGraph(Graph *);

// @func - getOrder
// @args - Graph to be queried
// @ret  - The number of vertices in this graph
int getOrder(Graph g);

// @func - getSize
// @args - Graph to be queried
// @ret  - the number of edges in this graph
int getSize(Graph g);

// @func - getSource
// @args - Graph to be queried
// @ret  - returns the index that was most recently used at a source
//         vertex for BFS
int getSource(Graph g);

// @func - getParent
// @args - #1 graph to be queried, #2 the index of the vertex that we are querying the parent of
int getParent(Graph g, int vertex);

// @func - getDist
// @args - #1 Graph to be queried, #2 the vertex to find the distance to
// @ret  - The distance (each edge = 1) between the source and target vertices
int getDist(Graph g, int vertex);

// @func - getPath
// @args - #1 List to be worked on, #2 graph to be queried, #3 destination vertex to find the path
// @ret  - nothing
void getPath(List L, Graph g, int vertex);

// @func - makeNull
// @args - Graph object to nullify
// @ret  - nothing
void makeNull(Graph g);

// @func - addEdge
// @args - #1 Graph in question, #2 first vertex, #3 second vertex
// @ret  - nothing
void addEdge(Graph G, int u, int v);

// @func - addArc
// @args - #1 Graph object in question, #2 first vertex, #3 second vertex
// @ret  - nothing
void addArc(Graph G, int u, int v);

// @func - BFS
// @args - #1 Graph in question, #2 source vertex for the algorithm
// @ret  - nothing, results of BFS are stored internally
void BFS(Graph G, int s);
  
// @func - printGraph
// @args - #1 output stream, #2 Graph object to print
// @ret  - nothing
void printGraph(FILE * out, Graph g);

#endif
