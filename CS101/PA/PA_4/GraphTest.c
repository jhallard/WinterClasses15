#include "Graph.h"
#include <time.h>

int main() {

  srand(time(NULL));
  Graph g = newGraph(200);

  for(int i = 1; i <= 200; i++) {
      for(int j = i+1; j <= 200; j++) {
          addEdge(g, i, j);
      }
  }

  BFS(g, 2);
  List l = newList();

  getPath(l, g, 30);
  printList(stdout, l);

}
