// https://leetcode.com/problems/min-cost-to-connect-all-points/

#include <alogrithm>
#include <utility>

class Edge {
public:
  int a, b;
  int dist;

  Edge(int a, int b, int dist): a(a), b(b), dist(dist) {};

  bool operator< (const Edge &e) {
    return this->dist < e.dist;
  }
};

class Solution {
public:
  vector<int> p;    // disjoint-set, track each point's parent

  int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();

    vector<Edge> edge;

    // calculating edge and sort
    for(int i = 0; i < n; i++)
      for(int j = i + 1; j < n; j++) {
        int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
        edge.push_back(Edge(i, j, dist));

      }
    sort(edge.begin(), edge.end());

    int cost = kruskal(edge);
    return cost;
  }

  int kruskal(vector<Edge>& edge) {
    int n = edge.size();

    p.resize(n + 1);
    for(int i = 0; i < n + 1; i++)
      p[i] = i;

    int cost = 0;
    for(int i = 0; i < n; i++) {
      int a = edge[i].a;
      int b = edge[i].b;

      // if the vertex has the same root(form a circle), ignore it
      if(find(a) == find(b))
        continue;

      // mrege two tree by assign them to the same root
      p[find(a)] = find(b);

      cost += edge[i].dist;
    }

    return cost;
  }

  int find(int x) {
    // p[x] = find(p[x]): assign new parent while searching to imporve efficiency
    return x == p[x] ? x : p[x] = find(p[x]);
  }
};
