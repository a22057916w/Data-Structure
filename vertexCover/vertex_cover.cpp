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
  void getVertexCover()
};

void Graph::addEdge(int u, int v) {
  // undirected graph
  adj[u].push_back(v);
  adj[v].push_back(u);
}

void Graph::getVertexCover() {
  bool visited[V] = {false};
  int apr_min = 0;

  for(int u = 0; u < v; u++) {

    if(visited[u] == false) {

      for(int it = adj[u].begin(), it != adj[u].end(); it++) {
        int v = *it;
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

  return 0;
}
