// 在 n×n 网格中，从 (0,0) 走到 (n-1,n-1) 再返回，每格樱桃只能摘一次，求能摘到的最多樱桃数

// 关键转化：来回两趟等价为两个人同时从 (0,0) 走向 (n-1,n-1) 。

// 两人走了 k 步时，若 person1 在第 r1 行，则它的列为 c1 = k - r1（因为每步走右或下，行+列=步数）。所以状态只需要 dp[k][r1][r2]，列自动推算
// DP状态：dp[k][r1][r2] = 两人各走了 k 步，person1 在行 r1、person2 在行 r2 时的最大樱桃数
// 每步转移：两人各自可以"向右"或"向下"，共 4 种组合，取最大值。若两人在同格，樱桃只算一次

#include<bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> grid;
vector<vector<vector<int>>> memo;

int solve(int k, int r1, int r2){
    int c1 = k - r1, c2 = k - r2;

    // 越界或荆棘
    if(r1 < 0 || r1 >= n || r2 < 0 || r2 >= n ||
        c1 < 0 || c1 >= n || c2 < 0 || c2 >= n ||
        grid[r1][c1] == -1 || grid[r2][c2] == -1)
        return -1e9;
    

    if(k == 2 * (n-1)) return grid[r1][c1];
    if(memo[k][r1][r2] != INT_MIN) return memo[k][r1][r2];

    // 当前格子樱桃（同格只算一次）
    int cherries = grid[r1][c1];
    if(r1 != r2) cherries += grid[r2][c2];

    // 两人各自向右或向下，共4种组合
    int best = max({solve(k+1, r1+1, r2+1),
                    solve(k+1, r1+1, r2),
                    solve(k+1, r1, r2+1),
                    solve(k+!, r1, r2)});
    
    return memo[k][r1][r2] = cherries + best;
}

int main(){
    cin >> n;
    grid.assign(n, vector<int>(n));
    // assign 是 vector 的重新赋值方法，用来一次性设定 vector 的大小和初始值
    // v.assign(大小, 初始值);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> grid[i][j];
        }
    }

    // memo[k][r1][r2]，k最大为2*(n-1)
    // 两人走了 k 步时，若 person1 在第 r1 行，则它的列为 c1 = k - r1（因为每步走右或下，行+列=步数）
    // 所以状态只需要 dp[k][r1][r2]，列自动推算
    memo.assign(2*n, vector<vector<int>>(n, vector<int>(n, INT_MIN)));

    cout << max(0, solve(0, 0, 0)) << endl;
    return 0;
}

// 题目本来是一个人走来回：

// 第一趟：(0,0) → (n-1,n-1)，只能向右/向下
// 第二趟：(n-1,n-1) → (0,0)，只能向左/向上

// 同一格的樱桃只能摘一次

// 难点：第一趟摘了哪些格子，会影响第二趟能摘什么，两趟之间有依赖，很难直接建模。

// 关键转化：第二趟从终点走回起点，反过来看就是从起点走向终点。所以一个人走来回 = 两个人同时从 (0,0) 走向 (n-1,n-1)，只要两人同步走，走过的格子自然不重复计算

// 一人来回：
//   去：(0,0) → (n-1,n-1)
//   回：(n-1,n-1) → (0,0)

// 等价转化为：
//   人A：(0,0) → (n-1,n-1)
//   人B：(0,0) → (n-1,n-1)  （同时出发，同时到达）




// memo 就是这道题的 dp 数组，只是用"记忆化搜索"的方式填写

// |     | 迭代DP          | 记忆化搜索           |
// | --- | ------------- | --------------- |
// | 数组名 | dp[k][r1][r2] | memo[k][r1][r2] |
// | 含义  | 完全一样          | 完全一样            |
// | 填法  | 三重for循环       | 递归时顺带存值         |

// memo[k][r1][r2] 的含义 ：

// 两人都走了 k 步

// 人A在第 r1 行（列自动算出：c1 = k - r1）
// 人B在第 r2 行（列自动算出：c2 = k - r2）

// 此状态下能摘到的最大樱桃数

// 为什么 memo 大小是 2n × n × n？
// 两人各走 2*(n-1) 步才能从(0,0)到(n-1,n-1)
// 所以 k 的范围是 0 ~ 2*(n-1)，共 2*n-1 个值
// → 开 2*n 保险

// r1, r2 各自范围是 0 ~ n-1
// → 各开 n

// 三维：memo[步数k][人A的行][人B的行]

// memo.assign(2*n, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
// //           ↑                        ↑                ↑
// //         k维度                    r1维度            r2维度，全填INT_MIN

// INT_MIN 表示"还没算过"，是记忆化的标志