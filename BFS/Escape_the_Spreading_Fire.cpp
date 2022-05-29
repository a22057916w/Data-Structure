class Solution {
public:
    int r[4] = {1, 0, 0, -1}, c[4] = {0, 1, -1, 0};

    // return fireTime table by BFS
    vector<vector<int>> fireSpreadTime(vector<vector<int>> grid) {

      // declare the frieTime table as the same size as grid
      vector<vector<int>> fireTime(grid.size(), vector<int>(grid[0].size(), -1));

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
      int fire_mins = 0;
      while(!fire.empty()) {

          int size = fire.size();
          while(size--) {

              pair<int, int> pf = fire.front();
              fire.pop();
              int fx = pf.first, fy = pf.second;

              fire_mins +=1;

              for(int k = 0; k < 4; k++) {
                  if((fx+r[k] >= 0 && fx+r[k] < grid.size()) && (fy+c[k] >= 0 && fy+c[k] < grid[0].size()) && (grid[fx+r[k]][fy+c[k]] == 0)) {
                      grid[fx+r[k]][fy+c[k]] = 1;
                      fireTime[fx+r[k]][fy+c[k]] = fire_mins;
                      fire.push({fx+r[k], fy+c[k]});
                  }
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

      int maxWaitTime = 0;
      int L = 0, R = fireTime[0][0];
      while(L < R) {
        int M = (L + R) >> 1;
        if(canEscape(M, fireTime, grid))
          L = M + 1;
        else
          R = M - 1;
      }

      return 0;

    bool canEscape(int waitTime, vector<vector<int>>& fireTime, vector<vector<int>> grid) {

      // declare the playerTime table as the same size as grid
      vector<vector<int>> playerTime(grid.size(), vector<int>(grid[0].size(), -1));
    }

        // queue<pair<int, int>> mov;
        // mov.push({0, 0});
        //
        // while(!man_reach && !mov.empty()) {
        //
        //     int size = mov.size();
        //     while(size--) {
        //
        //         pair<int, int> pm = mov.front();
        //         mov.pop();
        //         int mx = pm.first, my = pm.second;
        //
        //         for(int k = 0; k < 4; k++) {
        //             if(mx+r[k] >= 0 && mx+r[k] < grid.size() && my+c[k] >= 0 && my+c[k] < grid[0].size() && grid[mx+r[k]][my+c[k]] != 2) {
        //                 if((mx+r[k] == grid.size() - 1 && my+c[k] == grid[0].size() - 1)) {
        //                     man_reach = true;
        //                     break;
        //                 }
        //
        //                 grid[mx+r[k]][my+c[k]] = 3;
        //                 mov.push({mx+r[k], my+c[k]});
        //             }
        //         }
        //     }
        //     mov_mins += 1;
        // }
        //
        // cout << mov_mins << " " << man_reach << endl;
        // cout << fire_mins << " " << fire_reach << endl;
        // if(fire_reach) {
        //     if(mov_mins <= fire_mins)
        //         return fire_mins - mov_mins;
        //     else
        //         return -1;
        // }
        // else
        //     return 1E9;
    }
};
