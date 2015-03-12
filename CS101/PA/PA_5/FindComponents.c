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

Graph processFile(char *, char *);

int main(int argc, char ** argv) {

  if(argc != 3 || argv == NULL) {
    fprintf(stderr, "Must pass in filename as command-line argument");
    exit(1);
  }

  char * fn = argv[1];
  char * out_fn = argv[2];

  Graph G = processFile(fn, out_fn);

  printGraph(stdout,  G);
  
  List l = newList();

  for(int i = 1; i <= getOrder(G); i++) {
    append(l, i);
  }

  DFS(G, l);
  printf("\n\n");
  printList(stdout, l);
  printf("\n\n");
  DFS(G, l);
  printf("\n\n");
  printList(stdout, l);
  printf("\n\n");

  freeList(&l);
  freeGraph(&G);
}



Graph processFile(char * fn, char * fn_out) {
  
  FILE * fp = fopen(fn, "r");
  FILE * fp_out = fopen(fn_out, "w");
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
      addArc(new_graph, origin, terminus);
    }
    else {
      break;
    }
  }

  // printGraph(fp_out, new_graph);

  fprintf(fp_out, "\n\n");
  fclose(fp);
  fclose(fp_out);

  return new_graph;
}
