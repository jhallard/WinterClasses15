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
  int * distance;

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
    new_graph->distance = malloc(n*sizeof(int));
    new_graph->color = malloc(n*sizeof(int));
    return new_graph;
  }
  
  // @func - freeGraph
  // @args - pointer to a graph, which is a double pointer to a GraphObj struct
  void freeGraph(Graph* pG) {
  // --------------------------------------------------//
  // TODO - Free the graph pointer and set it to null
  //---------------------------------------------------//
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

  // @func - getDist
  // @args - #1 Graph to be queried, #2 the vertex to find the distance to
  // @ret  - The distance (each edge = 1) between the source and target vertices
  int getDist(Graph G, int u) {

    if(G == NULL) {
      fprintf(stderr, "Error : Graph null in getParent");
      exit(1);
    }
    else if(G->parent == NULL) {
      fprintf(stderr, "Invalid inquiry");
      exit(1);
    }
    return G->distance[--u];
  }

  // @func - getPath
  // @args - #1 List to be worked on, #2 graph to be queried, #3 destination vertex to find the path
  // @ret  - nothing
  void getPath(List L, Graph G, int u) {
    if(u == G->source)
      return;
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

  // @func - BFS
  // @args - #1 Graph in question, #2 source vertex for the algorithm
  // @ret  - nothing, results of BFS are stored internally
  void BFS(Graph G, int s) {

    const int INF = -2;
    const int NIL = -1;

    if(G == NULL || s <= 0 || s > G->order) {
      fprintf(stderr, "Invalid Arguments in BFS");
      exit(1);
    }
    G->source = s;
    --s; // normalize s to our working space
    for(int i = 0; i < G->order; i++) {
      if(i == s) continue;
      G->color[i] = WHITE;
      G->parent[i] = INF;
      G->distance[i] = NIL;
    }

    G->color[s] = GRAY;
    G->parent[s] = NIL;
    G->distance[s] = 0;
    List queue = newList();
    prepend(queue, s);


    while(length(queue) > 0) { 
      
     // printf("In main loop\n"); 
      int x = front(queue);
      List adj_temp = G->adj_list[x];
     // printList(stdout, adj_temp);
      deleteFront(queue);

     // printf("From Queue\n"); 
      for(moveTo(adj_temp, 0); getIndex(adj_temp) >= 0; moveNext(adj_temp)) {
          
       // printf("In inner loop\n"); 
        int vert = getElement(adj_temp);
        if(G->color[vert] == WHITE) {
          G->color[vert] = GRAY;
          G->distance[vert] = G->distance[x]+1;
          G->parent[vert] = x;
          append(queue, vert);
        }

      } // end inner for loop

      G->color[x] = BLACK;

    } // end main while loop

  } // end BFS function

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



  

  
  
  


