#include<bits/stdc++.h>
using namespace std;

int main(){
    int R, C;
    if(!(cin >> R >> C)) return 0;
    vector<vector<int>> grid(R, vector<int>(C));

    queue<pair<int, int>> q;
    int freshCnt = 0;

    // 1. 初始化：收集所有烂橘子位置，统计新鲜橘子总数
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

    // 2. 特判：如果一开始就没有新鲜橘子，直接返回0
    if(freshCnt == 0){
        cout << 0 << '\n';
        return 0;
    }

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    int minutes = 0;
    // 3. 多源BFS：每一轮循环代表过去1分钟
    while(!q.empty()){
        // 获取这一分钟开始时，烂橘子队列的大小
        int levelSize = (int)q.size(); 
        for(int k = 0; k < levelSize; ++k){
            auto [r, c] = q.front(); q.pop();

            // 尝试感染四周
            for(int d = 0; d < 4; ++d){
                int nr = r + dr[d];
                int nc = c + dc[d];
                // 边界检测且只有是新鲜橘子才会被感染
                if(nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if(grid[nr][nc] == 1){
                    grid[nr][nc] = 2;  // 变成烂橘子
                    --freshCnt;        // 新鲜数量减一
                    q.emplace(nr, nc); // 将新烂掉的橘子入队，供下一分钟扩散用
                }
            }
        }
        ++minutes; // 处理完一轮扩散，时间加1
    }

    // 4. 最终检查：如果还有剩余新鲜橘子，输出-1；否则输出最后一分钟处理完后的时间
    // 注意：这里的 minutes-1 是因为最后一次循环中队列虽然为空，但 minutes 还是做了自增
    if(freshCnt > 0) cout << -1 << '\n';
    else cout << minutes - 1 << '\n';
    return 0;
}