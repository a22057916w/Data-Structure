// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1541

// calculate only MST

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

int prim(int v, vector<vector<int>> &edges) {

  // for pair comparison: c++ compares the first elements and only if they are equivalent, compares the second elements.
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<pair<int, int>> adj[v];
  vector<bool> vis(v, false);

  // initiate the adjacency list
  for(int i = 0; i < edges.size(); i++) {
    int u = edges[i][0] - 1;
    int v = edges[i][1] - 1;
    int dist = edges[i][2];

    adj[u].push_back({v, dist});
    adj[v].push_back({u, dist});
  }

  int cost = 0;
  pq.push({0, 0});    // given a initial value (0-dist, node-start-point)
  while(!pq.empty()) {
    auto p = pq.top();  // the top of pq is the most lishtwage edge
    pq.pop();
    int weight = p.first;
    int vertex = p.second;

    if(!vis[vertex]) {

      cost += weight;
      vis[vertex] = true;

      // find the adjcent node for vertex then add the {dist, node} to pq
      for(auto e: adj[vertex])
        if(!vis[e.first])
          pq.push({e.second, e.first});
    }
  }
  return cost;
}

int main() {
  int testcase;

  cin >> testcase;
  while(testcase--) {
    int v, e;
    cin >> v >> e;

    // read the input
    vector<vector<int>> edges(e, vector<int>(3));
    for(int i = 0; i < e; i++)
      for(int j = 0; j < 3; j++)
        cin >> edges[i][j];

    int MSTcost = prim(v, edges);
    cout << MSTcost << endl;
  }

  return 0;
}
