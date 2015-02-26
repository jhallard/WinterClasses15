// |===================================================================|
// ||  Author  - John Allard                                          ||     
// ||  ID      - 1437547                                              || 
// ||  CruzID  - jhallard                                             || 
// ||  Project - Programming Assignment #4                            ||                
// ||  File    - FindPath.c                                           || 
// ||  Info    - Command-line program for finding the shortest path   ||
// ||            between two vertices in a given graph.               ||                              
// |===================================================================|

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

Graph readFile(char *);
void computeOutput(Graph, char *, char *);

int main(int argc, char ** argv) {

  if(argc != 3 || argv == NULL) {
    fprintf(stderr, "Must pass in filename as command-line argument");
    exit(1);
  }

  char * fn = argv[1];
  char * out_fn = argv[2];
  Graph graph = readFile(fn);
  // computeOutput(graph, fn, out_fn);
  printGraph(stdout, graph);
  BFS(graph, 2);
}



Graph readFile(char * fn) {
  
  FILE * fp = fopen(fn, "r");
  char line[81];

  if(fp == NULL) {
    fprintf(stderr, "Error : Invalid Filename Argument");
    exit(1);
  }

  fgets(line, 10, fp);
  int order = 0;
  sscanf(line, "%d", &order);
  if(order <= 0) {
    fprintf(stderr, "Error parsing input file, order < 0");
    exit(1);
  }
  Graph new_graph = newGraph(order);
  int origin = -1;
  int terminus = -1; 
  while(fgets(line, 10, fp) != NULL)
  {
    sscanf(line, "%d %d", &origin, &terminus);
    if(origin > 0 && terminus > 0 && origin <= order && terminus <= order) {
      addEdge(new_graph, origin, terminus);
    }
    else {
      break;
    }
  }


  while(fgets(line, 10, fp) != NULL)
  {
    sscanf(line, "%d %d", &origin, &terminus);
    if(origin > 0 && terminus > 0 && origin <= order && terminus <= order) {
      BFS(new_graph, origin);
      List l = newList();
      getPath(l, new_graph, terminus);
      printList(stdout, l);
      fprintf(stdout, "\n");
    }
    else {
      break;
    }
  }


  fclose(fp);
  return new_graph;
}





void computeOutput(Graph graph, char * fn, char * out_fn) {
  FILE * fp = fopen(fn, "r");
  char line[81];

  if(fp == NULL) {
    fprintf(stderr, "Error : Invalid Filename Argument");
    exit(1);
  }

  fclose(fp);
}