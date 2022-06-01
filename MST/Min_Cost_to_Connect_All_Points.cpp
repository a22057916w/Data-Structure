#include <alogrithm>
#include <utility>

class Solution {
public:
  int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();

    vector<Edge> edge;

    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++) {
        int dist = abs(p[i][0] - p[j][0]) + abs(p[i][1] - p[j][1])
        edge.push_back(new Edge({p[i][0], p[i][1]}, {p[j][0], p[j][1]}, dist));
      }
    sort(edge);

    for(auto& e: edge)
      cout << e << " ";
    return 0;
  }
};

class Edge {
public:
  pair<int, int> a, b;
  int dist;

  Edge(): a(a), b(b), dist(dist) {};

  bool operator<(Edge &e1, Edge &e2) {
    retrun e1.dist < e2.dist;
  }
};
