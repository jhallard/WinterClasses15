// |===================================================================|
// ||  Author  - John Allard                                          ||     
// ||  ID      - 1437547                                              || 
// ||  CruzID  - jhallard                                             || 
// ||  Project - Programming Assignment #5                            ||                 
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

  int * parent;
  int * color;
  int * discovered;
  int * finished;
  List * adj_list;

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
int getDiscover(Graph G, int u) {
  if(G == NULL) {
    fprintf(stderr, "Error : Graph null in getDiscover");
    exit(1);
  }
  if(u < 1 || u > G->order) {
    fprintf(stderr, "Error : vertex value out of range in getDiscover");
    exit(1);
  }

  return G->discovered[--u];
}

// @func - finish
// @args - #1 Graph to be queried, #2 vertex in the graph to get the finish time of
// @ret  - the time of finish for the given vertex
// @info : Pre: 1<=u<=n=getOrder(G) 
int getFinish(Graph G, int u) {
  if(G == NULL) {
    fprintf(stderr, "Error : Graph null in getFinish");
    exit(1);
  }
  if(u < 1 || u > G->order) {
    fprintf(stderr, "Error : vertex value out of range in getFinish");
    exit(1);
  }

  return G->finished[--u];

}

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

// @func - copyGraph
// @args - Graph Object to have a copy made of
// @ret  - new graph object
Graph copyGraph(Graph G) {
  Graph new_graph = newGraph(G->order);

  for(int i = 0; i < G->order; i++) {
    List * temp = &G->adj_list[i];

    for(moveTo(*temp, 0); getIndex(*temp) >= 0; moveNext(*temp)) {
      addArc(new_graph, i+1, getElement(*temp)+1);
    }
  }

  return new_graph;
}

// @func - transpose
// @args - Graph to be transposed
// @ret  - tranposed graph
// @info - This function takes all edges and switch their origin and terminus
Graph transpose(Graph G) {
  Graph new_graph = newGraph(G->order);

  for(int i = 0; i < G->order; i++) {
    List * temp = &G->adj_list[i];

    for(moveTo(*temp, 0); getIndex(*temp) >= 0; moveNext(*temp)) {
      addArc(new_graph, getElement(*temp)+1, i+1);
    }
  }

  return new_graph;
}


// @func - visit
// @args - #1 Graph object in question, #2 vertex to visit, #3 time value at the beginning of this call
void visit(Graph G, List s, int vert, int * t) {
  G->color[vert] = GRAY;
  G->discovered[vert] = ++(*t);
  // printf("outer :  %d \n", vert);
  for(moveTo(G->adj_list[vert], 0); getIndex(G->adj_list[vert]) >= 0; moveNext(G->adj_list[vert])) {
    
    int curr = getElement(G->adj_list[vert]);
    if(G->color[curr] == WHITE) {
      G->parent[curr] = vert+1;
      visit(G, s, curr, t);
    }
  }

  G->color[vert] = BLACK;
  G->finished[vert] = ++(*t);
  prepend(s, vert);
}

// @func - DFS
// @args - #1 Graph object to be searched, #2 list containing the order of vertices to be processed
// @info - This function performs DFS on the graph object, searching the vertices in the order they are given in the input list.
//         This same list is then used as an output parameter to store the vertices by decreasing finish time.
void DFS(Graph G, List s) {

  if(G == NULL) {
    fprintf(stderr, "Error : Null input in DFS");
    exit(1); 
  }

  if(length(s) != G->order) {
    fprintf(stderr, "Precondition Failure : List length != G->order in DFS");
    exit(1); 
  }

  List ret = newList();

  // initialization of DFS
  for(int i = 0; i < G->order; i++) {
    G->color[i] = WHITE;
    G->parent[i] = NIL;
  }

  int t = 0;

  // main DFS loop, recursively visit all of the vertices in order
  for(moveTo(s, 0); getIndex(s) >= 0; moveNext(s)) {
    int curr = getElement(s)-1;
    if(G->color[curr] == WHITE) {
      visit(G, ret, curr, &t);
    }  
  }

  clear(s);
  
  // fill the original list with our values of decreasing finish time.
  for(moveTo(ret, 0); getIndex(ret) >= 0; moveNext(ret)) {
      append(s, getElement(ret)+1);
  }

  freeList(&ret);

}






  
  
  


