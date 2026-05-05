// 这是经典的多源 BFS（广度优先搜索）题，即 LeetCode 994「腐烂的橘子」

// 题目概括： 给定一个网格，腐烂橘子每分钟向上下左右扩散感染新鲜橘子，求全部新鲜橘子腐烂所需的最少分钟数；若存在无法被感染的新鲜橘子则输出 -1
// 输入：第一行 R C，接下来 R 行每行 C 个整数（0/1/2）
// 输出：一个整数（最小分钟数 / 0 / -1）

// 核心思路
// 把所有初始腐烂橘子同时入队，做一次多源 BFS，逐层扩散（每层 = 1 分钟），最终层数即为答案 。同时统计新鲜橘子数量，BFS 结束后若仍剩余新鲜橘子则返回 -1 

#include<bits/stdc++.h>
using namespace std;

int main(){
    int R, C; cin >> R >> C;
    vector<vector<int>> grid(R, vector<int>(C));
    queue<pair<int, int>> q;
    int fresh = 0;
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            cin >> grid[i][j];
            if(grid[i][j] == 2) q.push({i, j});
            if(grid[i][j] == 1) fresh++;
        }
    }
    if (fresh == 0) {cout << 0; return 0;}

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int minutes = 0;

    while(!q.empty()){
        int sz = q.size();
        bool spread = false;
        while(sz--){
            auto [x, y] = q.front(); q.pop();
            for(int d = 0; d < 4; d++){
                int nx = x + dx[d], ny = y + dy[d];
                if(nx >= 0 && nx < R && ny >= 0 && ny < C && grid[nx][ny] == 1){
                    grid[nx][ny] = 2;
                    fresh--;
                    q.push({nx, ny});
                    spread = true;
                }
            }
        }
        if (spread) minutes++;
    }
    
    cout << (fresh == 0 ? minutes : -1);
    return 0;
}

// 为什么用队列？
// BFS（广度优先搜索）的本质是**"一层一层向外扩散"**，而队列天然支持"先进先出"——先入队的腐烂橘子先扩散，这正好模拟了按时间顺序传播的过程 。你可以把队列想象成一个"待处理任务清单"，每分钟从清单里取出所有已腐烂的橘子去感染邻居，再把新腐烂的放进清单。

// 为什么用 pair<int, int>？
// 是的，就是因为二维数组。网格中每个位置需要行号 + 列号两个坐标才能定位，pair<int, int> 就是把这两个数打包在一起 ：
// pair.first → 行号 x
// pair.second → 列号 y

// sz 是 size（大小/数量）的缩写，代表当前这一分钟开始时，队列里腐烂橘子的数量 

// 为什么要嵌套两层 while？——最核心的问题
// 这是 BFS 按层计时的标准写法 。用一个类比理解：
// 想象腐烂是一圈一圈向外的涟漪，每一圈 = 1 分钟

// | 外层 while (!q.empty()) | 内层 while (sz--)       |
// | --------------------- | --------------------- |
// | 控制"一共传播几分钟"           | 控制"这一分钟内，处理完本层所有橘子"   |
// | 每循环一次 = 时间推进一层        | 每循环一次 = 处理队列里当前层的一个橘子 |

// 如果没有内层 while，只用一个 while，就无法区分"第1分钟的橘子"和"第2分钟的橘子"，时间计数会乱掉

// 第0分钟初始状态: 队列 = [A, B]   ← 初始腐烂橘子
// 外层循环第1次: sz = 2
//   内层取出A → 感染A的邻居C → C入队
//   内层取出B → 感染B的邻居D → D入队
//   spread=true → minutes++ = 1
// 第1分钟结束: 队列 = [C, D]

// 外层循环第2次: sz = 2
//   内层取出C → 感染邻居...
//   ...
//   minutes++ = 2

// spread 是 "是否发生了扩散" 的标志（布尔值）。
// 它解决一个边界问题：如果某一轮队列里全是腐烂橘子，但四周没有任何新鲜橘子可以感染，这一轮不应该计时 +1。

// spread = true：这一分钟内至少感染了一个新橘子 → 时间 +1
// spread = false：这一分钟什么都没扩散 → 不计时

// while (!q.empty()) {          // 只要还有橘子待处理
//     int sz = q.size();        // 记录"本分钟"有多少个腐烂橘子
//     bool spread = false;      // 本分钟是否发生了感染
//     while (sz--) {            // 逐一处理本分钟的橘子
//         auto [x, y] = q.front(); q.pop();  // 取出一个腐烂橘子的坐标
//         for (int d = 0; d < 4; d++) {      // 检查上下左右4个方向
//             // nx, ny = 邻居坐标
//             if (/* 邻居在边界内 */ && grid[nx][ny] == 1) { // 邻居是新鲜橘子
//                 grid[nx][ny] = 2;   // 感染它
//                 fresh--;            // 新鲜橘子数量-1
//                 q.push({nx, ny});   // 下一分钟它也要去感染别人
//                 spread = true;      // 标记：本分钟有扩散
//             }
//         }
//     }
//     if (spread) minutes++;    // 只有真正感染了人，时间才+1
// }
