#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;


typedef pair<int, int> iPair; // pair of <int, int>

class Graph {
private:
  int V;                      // number of vertex
  vector<iPair> *adj;   // store vertex and its weight

public:
  Graph(int v) {
    this->V = v;
    adj = new vector<iPair>[v];
  }

  void addEdge(int u, int v, int w);
  void shortestPath(int s);           // pass sourece

  void printArray(vector<int> vec);   // print the result

};

void Graph::addEdge(int u, int v, int w) {
  adj[u].push_back({v, w});
  /* if it is a undirected graph, uncomment the line below */
  // adj[v].push_back({u, w});
}

// implement Dijkstra's Algorithm
void Graph::shortestPath(int src) {

  // for pair comparison: c++ compares the first elements and only if they are equivalent, compares the second elements.
  priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
  vector<int> predecessor(V, -1); // record the path to each vertex
  vector<int> dist(V, 1E9);       // All distance from source are infinite  
  dist[src] = 0;                  // distance of source will be always 0

  pq.push({0, src});          // pq -> (weight, vertex)
  while(!pq.empty()) {

    // Extract the first minimum distance from the priority queue  
    int u = pq.top().second;
    pq.pop();

    // Get vertex label and weight of current adjacent of u
    for(auto p : adj[u]) {    // adj -> (vertex, weight)
      int v = p.first;
      int w = p.second;

      // If there is shorted path to v through u  
      if(dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;  // update distance of v
        predecessor[v] = u;
        pq.push({dist[v], v});  // pq - > (weight, vertex)
      }
    }
  }

  cout << "\nPrint Predecessor:\n";
  printArray(predecessor);
  cout << "\nPrint Distance:\n";
  printArray(dist);
}

void Graph::printArray(vector<int> vec) {
  for(int i = 0; i < vec.size(); i++)
    cout << i << " ";
  cout << endl;
  for(int i = 0; i < vec.size(); i++)
    cout << vec[i] << " ";
  cout << endl;
}

int main() {
  Graph g(6);
  g.addEdge(0, 1, 8);g.addEdge(0, 5, 1);
  g.addEdge(1, 0, 3);g.addEdge(1, 2, 1);
  g.addEdge(2, 0, 5);g.addEdge(2, 3, 2);
  g.addEdge(2, 4, 2);g.addEdge(3, 1, 4);
  g.addEdge(3, 2, 6);g.addEdge(3, 4, 7);
  g.addEdge(3, 5, 3);g.addEdge(5, 3, 2);
  g.addEdge(5, 4, 8);

  g.shortestPath(0);

  return 0;
}

/*
reference:
  http://alrightchiu.github.io/SecondRound/single-source-shortest-pathdijkstras-algorithm.html#code (implement reference)
  https://www.javatpoint.com/cpp-dijkstra-algorithm-using-priority-queue  (implement reference)
  https://ithelp.ithome.com.tw/m/articles/10209593 (explain in a simple way)
*/
