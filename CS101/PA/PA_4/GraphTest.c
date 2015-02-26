#include "Graph.h"
#include <time.h>

int main() {

  srand(time(NULL));
  Graph g = newGraph(10000);

  // for(int i = 1; i <= 1000; i++) {
  //     for(int j = i+1; j <= 1000; j++) {
  //       if(i%32 == 0 || (j%56) == 1) 
  //         addEdge(g, i, j);
  //     }
  // }

  for(int i = 1; i <= 400; i++) {
    for(int j = i+1; j <= 300; j++) {
        int k = rand() % 9999+1;
        int l = rand() % 9999+1;
        addEdge(g, k, l);
    }
  }
  //printGraph(stdout, g);

  BFS(g, 10);
  BFS(g, 20);
  BFS(g, 30);
  BFS(g, 40);
  BFS(g, 50);

  int i = 0;
  for(i = 1; i <= 1000; i++) {
    printf("%d ", getParent(g, i)+1);
    if(i % 20 == 1)
      printf("\n");
  }
}
