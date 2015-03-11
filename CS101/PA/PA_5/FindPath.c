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

void processFile(char *, char *);

int main(int argc, char ** argv) {

  if(argc != 3 || argv == NULL) {
    fprintf(stderr, "Must pass in filename as command-line argument");
    exit(1);
  }

  char * fn = argv[1];
  char * out_fn = argv[2];
  processFile(fn, out_fn);
}



void processFile(char * fn, char * fn_out) {
  
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
      addEdge(new_graph, origin, terminus);
    }
    else {
      break;
    }
  }

  printGraph(fp_out, new_graph);
  fprintf(fp_out, "\n\n");

  while(fgets(line, 10, fp) != NULL)
  {
    sscanf(line, "%d %d", &origin, &terminus);
    if(origin > 0 && terminus > 0 && origin <= order && terminus <= order) {
      BFS(new_graph, origin);
      List l = newList();
      getPath(l, new_graph, terminus);
      if(getDist(new_graph, terminus) == INF) {
        fprintf(fp_out, "The distance from %d to %d is infinity \n", origin, terminus);
        fprintf(fp_out, "No %d-%d path exists \n\n", origin, terminus);
      }
      else {
        fprintf(fp_out, "The distance from %d to %d is : %d \n", origin, terminus, getDist(new_graph, terminus));
        fprintf(fp_out, "A shortest %d-%d path is : ", origin, terminus);
        printList(fp_out, l);
        fprintf(fp_out, "\n\n");
      }
      freeList(&l);
    }
    else {
      break;
    }
  }
  freeGraph(&new_graph);
  fclose(fp);
  fclose(fp_out);
}
