#include<bits/stdc++.h>
using namespace std;

int main(){
    int R, C;
    if(!(cin >> R >> C)) return 0;
    vector<vector<int>> grid(R, vector<int>(C));

    queue<pair<int, int>> q;
    int freshCnt = 0;

    for(int i = 0; i < R; ++i){
        for(int j = 0; j < C; ++j){
            cin >> grid[i][j];
            if(grid[i][j] == 2){
                q.emplace(i, j);
            } else if(grid[i][j] == 1){
                ++freshCnt;
            }
        }
    }

    if(freshCnt == 0){
        cout << 0 << '\n';
        return 0;
    }

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    int minutes = 0;
    while(!q.empty()){
        int levelSize = (int)q.size();
        for(int k = 0; k < levelSize; ++k){
            auto [r, c] = q.front(); q.pop();
            for(int d = 0; d < 4; ++d){
                int nr = r + dr[d];
                int nc = c + dc[d];
                if(nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if(grid[nr][nc] == 1){
                    grid[nr][nc] = 2;
                    --freshCnt;
                    q.emplace(nr, nc);
                }
            }
        }
        ++minutes;
    }

    if(freshCnt > 0) cout << -1 << '\n';
    else cout << minutes - 1 << '\n';
    return 0;
}