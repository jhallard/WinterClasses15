
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

// @func - getDiscover
// @args - #1 Graph to be queried, #2 vertex in the graph to get the discover time of
// @ret  - the time of discovery for the given vertex
// @info : Pre: 1<=u<=n=getOrder(G) 
int getDiscover(Graph G, int u); 

// @func - finish
// @args - #1 Graph to be queried, #2 vertex in the graph to get the finish time of
// @ret  - the time of finish for the given vertex
// @info : Pre: 1<=u<=n=getOrder(G) 
int getFinish(Graph G, int u); 

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

  
// @func - printGraph
// @args - #1 output stream, #2 Graph object to print
// @ret  - nothing
void printGraph(FILE * out, Graph g);

// @func - copyGraph
// @args - Graph Object to have a copy made of
// @ret  - new graph object
Graph copyGraph(Graph G);

// @func - transpose
// @args - Graph to be transposed
// @ret  - tranposed graph
// @info - This function takes all edges and switch their origin and terminus
Graph transpose(Graph G);

// @func - DFS
// @args - #1 Graph object to be searched, List S to append vertices to
// @ret  - none
// @info - /* Pre: getLength(S)==getOrder(G) */
void DFS(Graph g, List s);

#endif
