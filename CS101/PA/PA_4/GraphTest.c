#include "Graph.h"

int main() {

  Graph g = newGraph(10);

  for(int i = 1; i <= 10; i++) {
      for(int j = i; j <= 10; j++) {
        addEdge(g, i, j);
      }
  }
  printGraph(stdout, g);
}
