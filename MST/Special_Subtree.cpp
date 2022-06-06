// https://www.hackerrank.com/challenges/primsmstsub/problem?isFullScreen=true

#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'prims' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER start
 */

 int MinKeyExtract(vector<int> &key, vector<bool> &visited, int n) {
   int min_edge = INT_MAX / 2;
   int min_idx = -1;

   for(int i = 0; i < n; i++)
     if(!visited[i] && key[i] < min_edge) {
       min_edge = key[i];
       min_idx = i;
     }
   return min_idx;
 }

int prims(int n, vector<vector<int>> edges, int start) {
  vector<int> key(n, INT_MAX / 2);  // record the weigh between targe vertex and its adjacent vertex for each round
  vector<bool> visited(n, false);   // check if a vertex is visited
  vector<int> predecessor(n, -1);   // record the parent for each vertex in MST
  vector<vector<int>> e(n, vector<int>(n, INT_MAX));    // make an adjacency matrix

  // set the adjcent matrix from the given input
  for(int i = 0; i < edges.size(); i++) {
      int a = edges[i][0] - 1, b = edges[i][1] - 1;
      int dist = edges[i][2];

      e[a][b] = min(e[a][b], dist);   // there might be multiple path between two specfic nodes
      e[b][a] = e[a][b];
  }

  key[start - 1] = 0;
  for(int i = 0; i < n; i++) {      // iterate throught all vertice
    int u = MinKeyExtract(key, visited, n);   // get the vertex which has the mininum weight(to its predecessor)
    visited[u] = true;
    for(int j = 0; j < n; j++)    // set key for each vertex connected to u
      if(!visited[j] && u != j && e[u][j] < key[j]) {
        predecessor[j] = u;
        key[j] = e[u][j];
      }
  }

  // the final value of the sum of key is the minimun cost of MST
  int cost = 0;
  for(auto &weight : key)
    cost += weight;

  return cost;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<vector<int>> edges(m);

    for (int i = 0; i < m; i++) {
        edges[i].resize(3);

        string edges_row_temp_temp;
        getline(cin, edges_row_temp_temp);

        vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int edges_row_item = stoi(edges_row_temp[j]);

            edges[i][j] = edges_row_item;
        }
    }

    string start_temp;
    getline(cin, start_temp);

    int start = stoi(ltrim(rtrim(start_temp)));

    int result = prims(n, edges, start);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
