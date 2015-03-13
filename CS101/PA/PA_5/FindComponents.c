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

void findSCC(Graph, List l, FILE *);

int main(int argc, char ** argv) {

  if(argc != 3 || argv == NULL) {
    fprintf(stderr, "Must pass in filename as command-line argument");
    exit(1);
  }

  char * fn = argv[1];
  char * out_fn = argv[2];
  FILE * fp_out = fopen(out_fn, "w");

  Graph G = processFile(fn, out_fn);
  
  List l = newList();

  for(int i = 1; i <= getOrder(G); i++) {
    append(l, i);
  }

  fprintf(fp_out, "Adjacency List Representation : \n");
  printGraph(fp_out, G);
  fprintf(fp_out, "\n\n");

  DFS(G, l);


  Graph T = transpose(G);


  DFS(T, l);

  findSCC(T, l, fp_out);

  freeList(&l);
  freeGraph(&G);
  freeGraph(&T);
  fclose(fp_out);
}

void findSCC(Graph G, List l, FILE * fp_out) {

  if(G == NULL || l == NULL || fp_out == NULL) {
    fprintf(stderr, "Error : Null Input to findSCC\n");
    exit(1); 
  }

  List temp = newList();
  int comp_num = 1;

  for(moveTo(l, length(l)-1); getIndex(l) >= 0; movePrev(l)) {
    int element = getElement(l);

    if(getParent(G, element) == -1) {
      prepend(temp, element);
      fprintf(fp_out, "Component # %d : ", comp_num++);
      printList(fp_out, temp);
      fprintf(fp_out, "\n");
      clear(temp);
    }
    else {
      prepend(temp, element);
    }
  }

  freeList(&temp);
}


Graph processFile(char * fn, char * fn_out) {
  
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
      addArc(new_graph, origin, terminus);
    }
    else {
      break;
    }
  }

  fclose(fp);

  return new_graph;
}
