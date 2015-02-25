// |===================================================================|
// ||  Author  - John Allard                                          ||     
// ||  ID      - 1437547                                              || 
// ||  CruzID  - jhallard                                             || 
// ||  Project - Programming Assignment #4                            ||                
// ||  File    - FindPath.c                                           || 
// ||  Info    - Command-line program for finding the shortest path   ||
// ||            between two vertices in a given graph.               ||                              
// |===================================================================|


int main(int argc, char ** argv) {

  if(argc != 2 || argv == NULL) {
    fprintf(stderr, "Must pass in filename as command-line argument");
    exit(1);
  }

  char * fn = argv[1];
  Graph graph = readFile(fn);
  BFS(graph, 2);

}


Graph readFile(char * fn);
