#include "Graph.h"
#include <time.h>

int main() {

  srand(time(NULL));
  testOne();
  testTwo();
  testThree();

}


void testOne() {
  Graph g = newGraph(1000);

  for(int i = 1; i <= 300; i++) {
      for(int j = i+1; j <= 200; j++) {
          addEdge(g, i, j);
      }
  }

  for(int i = 0; i < 500; i++) {
    DFS(g, i);
  }
}


void testTwo() {
  Graph g = newGraph(1000);

  for(int i = 1; i <= 100; i++) {
      for(int j = i+1; j <= 9000; j++) {
          addEdge(g, i, j);
      }
  }

  for(int i = 0; i < 800; i++) {
    List l = newList();
    DFS(g, l);  
    freeList(l);
  }

  freeGraph(&G);
}


void testThree() {
  Graph g = newGraph(900);

  for(int i = 1; i <= 500; i++) {
      for(int j = i+1; j <= 800; j++) {
          addEdge(g, i, j);
      }
  }

  freeGraph(&G);

}