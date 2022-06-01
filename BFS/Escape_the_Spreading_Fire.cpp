// https://leetcode.com/problems/escape-the-spreading-fire/

/*
The idea is:
  step 1: spread the fire with BFS
  step 2: check edge cases
  step 3: find the optimal time using Binary Search
*/

class Solution {
public:
    int r[4] = {1, 0, 0, -1}, c[4] = {0, 1, -1, 0};

    // return fireTime table by BFS
    vector<vector<int>> fireSpreadTime(vector<vector<int>> grid) {

      // set the value to infinitly large
      vector<vector<int>> fireTime(grid.size(), vector<int>(grid[0].size(), INT_MAX / 2));

      // set fireTime table by BFS queue
      queue<pair<int, int>> fire;

      // initiate fire position to queue and fireTime
      for(int i = 0; i < grid.size(); i++)
          for(int j = 0; j < grid[0].size(); j++)
              if(grid[i][j] == 1) {
                  fire.push({i, j});
                  fireTime[i][j] = 0;   // set starting fire position to zero timing
              }

      // set fireTime table
      while(!fire.empty()) {
        pair<int, int> pf = fire.front();
        fire.pop();
        int fx = pf.first, fy = pf.second;

        int newTime = fireTime[fx][fy] + 1;
        for(int i = 0; i < 4; i++) {
          int x = fx + r[i];
          int y = fy + c[i];

            if((x >= 0 && x < grid.size()) && (y >= 0 && y < grid[0].size()) && grid[x][y] == 0) {
                grid[x][y] = 1;
                fireTime[x][y] = newTime;
                fire.push({x, y});
            }
        }
      }
      return fireTime;
    }

    int maximumMinutes(vector<vector<int>>& grid) {

      // get fireTime table/grid
      vector<vector<int>> fireTime = fireSpreadTime(grid);

      // check if the fire can't reach safehouse and player
      int maxPossibleTime = grid.size() * grid[0].size();
      if(canEscape(maxPossibleTime, fireTime, grid))
        return 1E9;

      // check if it is impossible to reach safehouse
      if(!canEscape(0, fireTime, grid))
        return -1;

      // check the rest possibe time by binary-search
      int maxWaitTime = 0;
      int L = 0, R = maxPossibleTime;
      while(L < R) {
        int M = (L + R) >> 1;
        if(canEscape(M, fireTime, grid)) {
          maxWaitTime = M;
          L = M + 1;
        }
        else
          R = M - 1;
      }
      // check edge condition
      if(canEscape(L, fireTime, grid))
        maxWaitTime = L;

      return maxWaitTime;
    }

    // determine if the player can escape to safehouse
    bool canEscape(int waitTime, vector<vector<int>>& fireTime, vector<vector<int>> grid) {

      // declare the playerTime table as the same size as grid
      vector<vector<int>> playerTime(grid.size(), vector<int>(grid[0].size(), waitTime));

      queue<pair<int, int>> q;
      q.push({0, 0});

      // do BFS
      while(!q.empty()) {
        pair<int, int> pp = q.front();
        q.pop();
        int px = pp.first, py = pp.second;

        int newTime = playerTime[px][py] + 1;
        for(int i = 0; i < 4; i++) {
          int x = px + r[i];
          int y = py + c[i];

          // special case: the fire and player can reach the safehouse at the saem time
          if((x == grid.size() - 1 && y == grid[0].size() - 1) && newTime <= fireTime[x][y])
            return true;

          if((x >= 0 && x < grid.size()) && (y >= 0 && y < grid[0].size()) && (grid[x][y] == 0) && newTime < fireTime[x][y]) {
              grid[x][y] = 1;
              playerTime[x][y] = newTime;
              q.push({x, y});
          }
        }
      }
      return false;
    }
};
