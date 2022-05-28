// https://leetcode.com/problems/number-of-islands/

#include <queue>
#include <utility>

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {

        int count = 0;
        int v[4] = {-1, 0, 0, 1}, h[4] = {0, 1, -1, 0};

        for(int i = 0; i < grid.size(); i++)
            for(int j = 0; j < grid[0].size(); j++) {
                if(grid[i][j] == '1') {
                    count++;      // there must be an island when encounter '1'


                    // check the island size, do BFS, and vistied check
                    queue<pair<int, int>> q;
                    q.push({i, j});

                    grid[i][j] = '2';    // 2 represent visited

                    // start BFS checking
                    while(!q.empty()) {
                        pair<int, int> p = q.front();
                        q.pop();
                        int x = p.first, y = p.second;

                        for(int k = 0; k < 4; k++){
                            if((x+v[k] >= 0 && x+v[k] < grid.size()) && (y+h[k] >= 0 && y+h[k] < grid[0].size()) && grid[x+v[k]][y+h[k]] == '1') {
                                q.push({x+v[k], y+h[k]});
                                grid[x+v[k]][y+h[k]] = '2';
                            }
                        }
                    }
                }
            }
        return count;
    }
};
