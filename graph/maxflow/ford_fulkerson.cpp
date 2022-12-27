#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<int>> vii;
typedef vector<int> vi;

class GraphFlowNetWork {
private:
  int V;      // number of vertex
  vii adj;   // adjacent matrix
public:
  GraphFlowNetWork(int n): V(n) {
    adj.resize(n);
    for(int i = 0; i < n; i++)
      adj[i].resize(n, 0);
  }

  void addEdge(int u, int v, int capacity);
  int FordFulkerson(int src, int tml);
  bool BFSfindExistingPath(vii graphResidual, vi &predecessor, int s, int t);

};


void GraphFlowNetWork::addEdge(int u, int v, int capacity) {
  adj[u][v] = capacity;     // dericted graph
}

int GraphFlowNetWork::FordFulkerson(int src, int tml) {
  vii graphResidual(adj);
  vi predecessor(V, -1);
  int maxFlow = 0;

  // BFS finds augmenting path,
  while(BFSfindExistingPath(graphResidual, predecessor, src, tml)) {

    // Find minimum residual capacity of the edges along
    // 用predecessor[v] 和 v 表示一條edge
    int mincapacity = 1E9;
    for(int v = tml; v != src; v = predecessor[v]) {
      int u = predecessor[v];
      mincapacity = min(graphResidual[u][v], mincapacity);
    }

    // updating the maximun flow
    maxFlow += mincapacity;

    // updating residual graph
    for(int v = tml; v != src; v = predecessor[v]) {
      int u = predecessor[v];
      graphResidual[u][v] -= mincapacity;
      graphResidual[v][u] += mincapacity;
    }
  }

  return maxFlow;
}

bool GraphFlowNetWork::BFSfindExistingPath(vii graphResidual, vi &predecessor, int s, int t) {
  vi visited(V, 0);
  predecessor.resize(V, -1);

  queue<int> q;

  q.push(s);
  visited[s] = 1;
  while(!q.empty()) {
    int u = q.front();
    q.pop();

    for(int v = 0; v < V; v++)
      if(graphResidual[u][v] != 0 && visited[v] != 1) {
        q.push(v);
        visited[v] = 1;
        predecessor[v] = u;

        // If we find a connection to the sink node,
        // then there is no point in BFS anymore
        if(v == t)
          return true;
      }
  }

  return false;
}

int main() {
  GraphFlowNetWork g(6);

  g.addEdge(0, 1, 9);g.addEdge(0, 3, 9);
  g.addEdge(1, 2, 3);g.addEdge(1, 3, 8);
  g.addEdge(2, 4, 2);g.addEdge(2, 5, 9);
  g.addEdge(3, 2, 7);g.addEdge(3, 4, 7);
  g.addEdge(4, 2, 4);g.addEdge(4, 5, 8);

  cout << g.FordFulkerson(0, 5) << endl;    // 指定source為vertex(0), termination為vertex(5)

  return 0;
}

/*
reference:
  http://alrightchiu.github.io/SecondRound/flow-networksmaximum-flow-ford-fulkerson-algorithm.html
  https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/?ref=rp
  https://www.geeksforgeeks.org/max-flow-problem-introduction/
*/
