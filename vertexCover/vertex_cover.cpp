#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>
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
  int getVertexCover();
};

void Graph::addEdge(int u, int v) {
  // undirected graph
  adj[u].push_back(v);
  adj[v].push_back(u);
}

int Graph::getVertexCover() {
  bool visited[V] = {false};
  int apr_min = 0;      // record the covered vertex

  // Consider all edges one by one
  for(int u = 0; u < V; u++) {

    // An edge is only picked when both visited[u] and visited[v]
    // are false
    if(visited[u] == false) {

      // Go through all adjacents of u and pick the first not
      // yet visited vertex (We are basically picking an edge
      // (u, v) from remaining edges.
      for(auto it = adj[u].begin(); it != adj[u].end(); it++) {
        int v = *it;

        // Add the vertices (u, v) to the result set
        // all edges from/to them would be ignored
        if(visited[v] == false) {
          visited[v] = true;
          visited[u] = true;
          apr_min++;
          break;
        }
      }
    }
  }

  // Print the vertex cover
   for (int i=0; i<V; i++)
       if (visited[i])
         cout << i << " ";
  cout << endl;

  return apr_min;
}

int main() {
  // Create a graph given in the above diagram
  Graph g(7);
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 3);
  g.addEdge(3, 4);
  g.addEdge(4, 5);
  g.addEdge(5, 6);

  cout << g.getVertexCover() << endl;
  return 0;
}
