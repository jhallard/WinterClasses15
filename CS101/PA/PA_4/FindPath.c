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

int main(int argc, char ** argv) {

  if(argc != 2 || argv == NULL) {
    fprintf(stderr, "Must pass in filename as command-line argument");
    exit(1);
  }

  char * fn = argv[1];
  Graph graph = readFile(fn);
  BFS(graph, 2);

}


Graph readFile(char * fn) {
  
  FILE * fp = fopen(fn, "r");
  char line[80];

  if(fp == NULL) {
    fprintf(stderr, "Error : Invalid Filename Argument");
    exit(1);
  }

  fgets(line, 80, fp);
  int order = 0;
  int count = 0;
  sscanf(line, "%d", &order);
  if(order <= 0) {
    fprintf(stderr, "Error parsing input file, order < 0");
    exit(1);
  }
  Graph new_graph = newGraph(order);

  while(fgets(line, 80, fp) != NULL && line != "0 0\n")
  {
    int origin = -1;
    int terminus = -1; 
    sscanf(line, "%d %d", &origin, &terminus);
    if(origin > 0 && terminus > 0 && origin <= order && terminus <= order) {
      addEdge(new_graph, origin , terminus);
    }
  }
   fclose(fp);

   return new_graph;
}
