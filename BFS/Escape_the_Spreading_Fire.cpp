class Solution {
public:
    int r[4] = {1, 0, 0, -1}, c[4] = {0, 1, -1, 0};

    // return fireTime table by BFS
    vector<vector<int>> fireSpreadTime(vector<vector<int>> grid) {

      // declare the frieTime table as the same size as grid
      vector<vector<int>> fireTime(grid.size(), vector<int>(grid[0].size(), 0));

      // set fireTime table by BFS queue
      queue<pair<int, int>> fire;

      // initiate fire position to queue and fireTime
      for(int i = 0; i < grid.size(); i++)
          for(int j = 0; j < grid[0].size(); j++)
              if(grid[i][j] == 1) {
                  fire.push({i, j});
                  fireTime[i][j] = 0;
                }

      // set fireTime table
      while(!fire.empty()) {
        pair<int, int> pf = fire.front();
        fire.pop();
        int fx = pf.first, fy = pf.second;

        int newTime = fireTime[fx][fy] + 1;
        for(int i = 0; i < 4; i++) {
          fx = fx + r[i];
          fy = fy + c[i];

            if((fx >= 0 && fx < grid.size()) && (fy >= 0 && fy < grid[0].size()) && (grid[fx][fy] == 0)) {
                grid[fx][fy] = 1;
                fireTime[fx][fy] = newTime;
                fire.push({fx, fy});
            }
        }
      }
      return fireTime;
    }

    int maximumMinutes(vector<vector<int>>& grid) {

      // get fireTime table/grid
      vector<vector<int>> fireTime = fireSpreadTime(grid);

      for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++)
          cout << fireTime[i][j] << " ";
        cout << endl;
      }

      int maxPossibleTime = grid.size() * grid[0].size();
      if(canEscape(maxPossibleTime, fireTime, grid))
        return 1E9;

      if(!canEscape(0, fireTime, grid))
        return -1;

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

      return maxWaitTime;
    }

    bool canEscape(int waitTime, vector<vector<int>>& fireTime, vector<vector<int>> grid) {

      // declare the playerTime table as the same size as grid
      vector<vector<int>> playerTime(grid.size(), vector<int>(grid[0].size(), waitTime));

      queue<pair<int, int>> q;
      q.push({0, 0});

      while(!q.empty()) {
        pair<int, int> pp = q.front();
        q.pop();
        int px = pp.first, py = pp.second;

        int newTime = playerTime[px][py] + 1;
        for(int i = 0; i < 4; i++) {
          px = px + r[i];
          py = py + c[i];

          if((px == grid.size() - 1 && py = grid[0].size() - 1) && newTime <= fireTime[px][py])
            return true;

          if((px >= 0 && px < grid.size()) && (py >= 0 && py < grid[0].size()) && (grid[px][py] == 0) && newTime < fireTime[px][py]) {
              grid[px][py] = 1;
              playerTime[px][py] = newTime;
              q.push({px, py});
          }
        }
      }
      return false;
    }
};
