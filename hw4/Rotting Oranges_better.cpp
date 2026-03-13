#include<bits/stdc++.h>
using namespace std;

int main(){
    int R, C; cin >> R >> C;

    vector<vector<int>> grid(R, vector<int>(C));
    queue<pair<pair<int, int>, int>> q; // 存储 {{r, c}, time}
    int freshCnt = 0;

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            cin >> grid[i][j];
            if(grid[i][j] == 2) q.push({{i, j}, 0});
            if(grid[i][j] == 1) freshCnt++;
        }
    }

    int lastTime = 0;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while(!q.empty()){
        auto [pos, time] = q.front(); q.pop();

        int r = pos.first, c = pos.second;
        lastTime = time;  // 记录最后一次感染的时间

        for(int i = 0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] == 1){
                grid[nr][nc] = 2;
                freshCnt--;
                q.push({{nr, nc}, time + 1});  // 感染时间+1
            }
        }
    }

    if(freshCnt > 0) cout << -1 << endl;
    else cout << lastTime << endl;
    return 0;
}