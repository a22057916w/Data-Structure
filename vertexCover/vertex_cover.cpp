#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

class Graph {
private:
  int V;              // number of vertex
  list<int> *adj;     // edges is much less than V*V
public:
  Graph(int n): V(n) {
    adj = new list<int>[V];
  }

  void addEdge(int u, int v);
  void getVertexCover()
};

void Graph::addEdge(int u, int v) {
  // undirected graph
  adj[u].push_back(v);
  adj[v].push_back(u);
}

void Graph::getVertexCover() {
  bool visited[V] = {false};

  for(int u = 0; u < v; u++) {

  }
}

int main() {

  return 0;
}
