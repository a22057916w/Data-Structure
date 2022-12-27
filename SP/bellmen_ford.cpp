#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

struct Edge {
  int u;
  int v;
  int weight;
};

class Graph {
private:
  int V = 0;
  vector<Edge> edge;
public:
  Graph(int v): V(v) {}

  void addEdge(int u, int v, int w);
  void printArray(vector<int> vec);
  void BellmenFord(int src);
};


void Graph::addEdge(int u, int v, int w) {
  // directed graph
  edge.push_back({u, v, w});
}


void Graph::printArray(vector<int> dist) {

  printf("Vertex\t\tDistance from Source\n");
  for(int i = 0; i < dist.size(); i++)
    printf("%d\t\t%d\n", i, dist[i]);
}

// For each vertex, we consider all edges and update the dist[].
// We do the above procedure n - 1 times, n for vertex
void Graph::BellmenFord(int src) {
  vector<int> dist(V, 1E9);     // distance to source
  dist[src] = 0;

  int E = edge.size();

  // if there are n vertex , the simple path only contain n-1 edge
  for(int i = 0; i < V - 1; i++)
    for(int j = 0; j < E; j++) {
      int u = edge[j].u;
      int v = edge[j].v;
      int weight = edge[j].weight;

      if(dist[v] > dist[u] + weight)
        dist[v] = dist[u] + weight;
    }

  // if we do more than n - 1 times, and find out the distance can be reduced,
  // then there is at a negative cycle
  for(int j = 0; j < E; j++) {
    int u = edge[j].u;
    int v = edge[j].v;
    int weight = edge[j].weight;

    if(dist[v] > dist[u] + weight) {
      cout << "Graph contains negative weight cycle" << endl;
      return;
    }
  }

  printArray(dist);

  return;
}

int main() {
  Graph g(5);

  g.addEdge(0,1,-1);
  g.addEdge(0,2,4);
  g.addEdge(1,2,3);
  g.addEdge(1,3,2);
  g.addEdge(1,4,2);
  g.addEdge(3,2,5);
  g.addEdge(3,1,1);
  g.addEdge(4,3,-3);

  // negetive cycle example
  // g.addEdge(2,4,-1);
  // g.addEdge(4,2,-1);

  g.BellmenFord(0);

  return 0;
}
