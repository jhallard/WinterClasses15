#include "Graph.h"
#include <time.h>

int main() {

  srand(time(NULL));
  Graph g = newGraph(1000);

  for(int i = 1; i <= 300; i++) {
      for(int j = i+1; j <= 200; j++) {
          addEdge(g, i, j);
      }
  }

  for(int i = 0; i < 500; i++) {
    List l = newList();
    BFS(g, i);
    getPath(l, g, i+1);
    clear(l);
    getPath(l, g, i-1);
    clear(l);
    getPath(l, g, 1000-i);
    clear(l);
  }

}
