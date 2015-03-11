// |===================================================================|
// ||  Author  - John Allard                                          ||     
// ||  ID      - 1437547                                              || 
// ||  CruzID  - jhallard                                             || 
// ||  Project - Programming Assignment #4                            ||                 
// ||  File    - Graph.c                                              || 
// ||  Info    - Implementation of the GraphObj Data Structure        ||                                             
// |===================================================================|

#include "Graph.h"

// These defines are used to keep track of the vertex 'colors' during BFS
#define WHITE 0
#define GRAY  1
#define BLACK 2

// @type - GraphObj
// @info - This struct represents a simple, undirected, unwieghted graph data structure.
//         It performs operations over integer vertex data, and is used by the FindPath function
//         which will allow a user to find the shortest path between different vertices in this graph.
typedef struct GraphObj {
  int order;
  int size;
  int source;
  List * adj_list;
  int * parent;
  int * color;
  int * discover;
  int * finished;

} GraphObj;

/*** Constructors-Destructors ***/

  // @func - Constructor
  // @args - #1 number of vertices in this graph
  // @info - Pre : n > 0
  Graph newGraph(int n){

    if(n <= 0) {
      fprintf(stderr, "Error : Graph must be intialized with more than 0 vertices");
    }
    Graph new_graph = malloc(sizeof(GraphObj));
    new_graph->adj_list = malloc(n*sizeof(List));
    new_graph->order = n;
    new_graph->size = 0;
    new_graph->source = 0;

    for(int i = 0; i < n; i++) {
      new_graph->adj_list[i] = newList();
    }

    new_graph->parent = malloc(n*sizeof(int));

    for(int i = 0; i < n; i++) {
      new_graph->parent[i] = NIL;
    }

    new_graph->color = malloc(n*sizeof(int));

    new_graph->finished = malloc(n*sizeof(int));

    for(int i = 0; i < n; i++) {
      new_graph->finished[i] = -1;
    }

    new_graph->discovered = malloc(n*sizeof(int));


    for(int i = 0; i < n; i++) {
      new_graph->discovered[i] = -1;
    }


    return new_graph;
  }
  
  // @func - freeGraph
  // @args - pointer to a graph, which is a double pointer to a GraphObj struct
  // @info - cleans up all of the memory
  void freeGraph(Graph* pG) {

    if(pG == NULL || *pG == NULL) {
      fprintf(stderr, "Error : Trying to free null graph\n");
      exit(1);
    }

    for(int i = 0; i < (*pG)->order; i++) {
      freeList(&(*pG)->adj_list[i]);
    }
    free((*pG)->parent);
    (*pG)->parent = NULL;
    free((*pG)->color);
    (*pG)->color = NULL;
    free((*pG)->adj_list);
    (*pG)->adj_list = NULL;
    free((*pG)->discovered);
    (*pG)->discovered = NULL;
    free((*pG)->finished);
    (*pG)->finished = NULL;

    free(*pG);
    *pG = NULL;

  }

  /*** Access functions ***/  

  // @func - getOrder
  // @args - Graph to be queried
  // @ret  - The number of vertices in this graph
  int getOrder(Graph G){
    if(G == NULL) {
      fprintf(stderr, "Error : Graph null in getOrder");
    }
    return G->order;
  }

  // @func - getSize
  // @args - Graph to be queried
  // @ret  - the number of edges in this graph
  int getSize(Graph G) {
    if(G == NULL) {
      fprintf(stderr, "Error : Graph null in getSize");
    }
    return G->size;
  }

  // @func - getSource
  // @args - Graph to be queried
  // @ret  - returns the index that was most recently used at a source
  //         vertex for BFS
  int getSource(Graph G) {
    if(G == NULL) {
      fprintf(stderr, "Error :Graph null in getSource");
      exit(1);
    }
    return G->source;
  }

  // @func - getParent
  // @args - #1 graph to be queried, #2 the index of the vertex that we are querying the parent of
  int getParent(Graph G, int u) {
    if(G == NULL) {
      fprintf(stderr, "Error : Graph null in getParent");
      exit(1);
    }
    else if(G->parent == NULL) {
      fprintf(stderr, "Invalid inquiry");
      exit(1);
    }
    return G->parent[--u];
  }


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

/*** Manipulation procedures ***/

// @func - makeNull
// @args - Graph object to nullify
// @ret  - nothing
void makeNull(Graph G) {
 
if(G == NULL) {
  fprintf(stderr, "Graph null in make null");
  exit(1);
}
for(int i = 0; i < G->order; i++) {
  clear(G->adj_list[i]);
}

}

// @func - addEdge
// @args - #1 Graph in question, #2 first vertex, #3 second vertex
// @ret  - nothing
// @info - /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v) {

if(G == NULL) {
  fprintf(stderr, "Graph null in addEdge");
    exit(1);
  }
  else if(u > G->order || v > G->order || u <= 0 || v <= 0) {
    fprintf(stderr, "Error : Invalid index, out of range (addEdge function)");
    exit(1);
  }
  --u;--v;
  insertSorted(G->adj_list[u], v);
  insertSorted(G->adj_list[v], u);
  
}

// @func - addArc
// @args - #1 Graph object in question, #2 first vertex, #3 second vertex
// @ret  - nothing
// @info - /* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v) {

  if(G == NULL) {
    fprintf(stderr, "Graph null in addArc");
    exit(1);
  }
  else if(u > G->order || v > G->order || u <= 0 || v <= 0) {
    fprintf(stderr, "Error : Invalid index, out of range (addArc function)");
    exit(1);
  }
  --u;--v;
  insertSorted(G->adj_list[u], v);
      

}

/*** Other operations ***/

// @func - printGraph
// @args - #1 output stream, #2 Graph object to print
// @ret  - nothing
void printGraph(FILE* out, Graph G) {
  
  if(G == NULL || out == NULL) {
    fprintf(stderr, "Error : Null input in printGraph");
    exit(1); 
  }

  for(int i = 0; i < G->order; i++) {
    List L = G->adj_list[i];

    fprintf(out, "%d :", i+1);
    for(moveTo(L, 0); getIndex(L) >= 0; moveNext(L)) {
      fprintf(out, " %d ", getElement(L)+1);
    } 
    fprintf(out, "\n");
  }
}


void DFS(Graph g, List s) {



}





  
  
  


