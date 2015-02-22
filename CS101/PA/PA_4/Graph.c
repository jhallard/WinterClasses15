// |===================================================================|
// ||  Author  - John Allard                                          ||     
// ||  ID      - 1437547                                              || 
// ||  CruzID  - jhallard                                             || 
// ||  Project - Programming Assignment #4                            ||                 
// ||  File    - Graph.c                                              || 
// ||  Info    - Implementation of the GraphObj Data Structure        ||                                             
// |===================================================================|

#include "Graph.h"

// @type - GraphObj
// @info - This struct represents a simple, undirected, unwieghted graph data structure.
//         It performs operations over integer vertex data, and is used by the FindPath function
//         which will allow a user to find the shortest path between different vertices in this graph.
typedef struct GraphObj {
  int order;
  int size;
  List * asjList;

} GraphObj;

/*** Constructors-Destructors ***/

  // @func - Constructor
  // @args - #1 number of vertices in this graph
  Graph newGraph(int n);
  
  // @func - freeGraph
  // @args - pointer to a graph, which is a double pointer to a GraphObj struct
  void freeGraph(Graph* pG);

  /*** Access functions ***/  

  // @func - getOrder
  // @args - Graph to be queried
  // @ret  - The number of vertices in this graph
  int getOrder(Graph G);

  // @func - getSize
  // @args - Graph to be queried
  // @ret  - the number of edges in this graph
  int getSize(Graph G);

  // @func - getSource
  // @args - Graph to be queried
  // @ret  - returns the index that was most recently used at a source
  //         vertex for BFS
  int getSource(Graph G);

  // @func - getParent
  // @args - #1 graph to be queried, #2 the index of the vertex that we are querying the parent of
  int getParent(Graph G, int u);

  // @func - getDist
  // @args - #1 Graph to be queried, #2 the vertex to find the distance to
  // @ret  - The distance (each edge = 1) between the source and target vertices
  int getDist(Graph G, int u);

  // @func - getPath
  // @args - #1 List to be worked on, #2 graph to be queried, #3 destination vertex to find the path
  // @ret  - nothing
  void getPath(List L, Graph G, int u);

  /*** Manipulation procedures ***/

  // @func - makeNull
  // @args - Graph object to nullify
  // @ret  - nothing
  void makeNull(Graph G);

  // @func - addEdge
  // @args - #1 Graph in question, #2 first vertex, #3 second vertex
  // @ret  - nothing
  void addEdge(Graph G, int u, int v);

  // @func - addArc
  // @args - #1 Graph object in question, #2 first vertex, #3 second vertex
  // @ret  - nothing
  void addArc(Graph G, int u, int v);

  // @func - BFS
  // @args - #1 Graph in question, #2 source vertex for the algorithm
  // @ret  - nothing, results of BFS are stored internally
  void BFS(Graph G, int s);

  /*** Other operations ***/

  // @func - printGraph
  // @args - #1 output stream, #2 Graph object to print
  // @ret  - nothing
  void printGraph(FILE* out, Graph G);

