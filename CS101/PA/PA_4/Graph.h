
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

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// typedef our private struct as a user accessable Graph class
typedef struct GraphObj * Graph;

Graph newGraph(int num);

void freeGraph(Graph *);

int getOrder(Graph g);

int getSize(Graph g);

int getSource(Graph g);

int getParent(Graph g, int vertex);

int getDist(Graph g, int vertex);

int getPath(List L, Graph g, int vertex);

void makeNull(Graph g);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void printGraph(FILE * out, Graph g);

#endif
