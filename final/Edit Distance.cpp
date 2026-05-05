// 最简做法：经典2D DP
// 这是教科书级别的DP，思路清晰、代码量小 ：

// 状态：dp[i][j] = word1 前 i 个字符变成 word2 前 j 个字符的最少操作数

// 初始化：

// dp[i][0] = i（删除 i 次）
// dp[0][j] = j（插入 j 次）

// 转移：

// 若 word1[i-1] == word2[j-1]：dp[i][j] = dp[i-1][j-1]
// 否则：dp[i][j] = 1 + min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]})
    // dp[i-1][j-1] + 1：替换
    // dp[i-1][j] + 1：删除 word1[i]
    // dp[i][j-1] + 1：插入 word2[j]

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, m; cin >> n >> m;

    // n=0就不读，直接保持空字符串
    string word1 = "", word2 = "";
    if (n > 0) cin >> word1;
    if (m > 0) cin >> word2;

    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    // 初始化边界
    for(int i = 0; i <= n; i++) dp[i][0] = i;
    for(int j = 0; j <= m; j++) dp[0][j] = j;

    // 状态转移
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(word1[i-1] == word2[j-1]){
                dp[i][j] = dp[i-1][j-1];
            } else{
                dp[i][j] = 1 + min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}

// 验证样例
// horse → ros，步骤：

// horse → rorse（替换 h→r）
// rorse → rose（删除 r）
// rose → ros（删除 e）

// 输出 3

//                    n+1行           m+1列  全为0
// vector<vector<int>> dp(n+1, vector<int>(m+1,  0));
// 1. vector<vector<int>>
// 这是一个 "装着vector的vector"，本质就是二维数组。可以这样理解：
// 外层 vector<...> = 若干行
// 内层 vector<int> = 每一行是一个整数数组
// 2. vector<...> dp(n+1, ...)
// 外层大小, n+1 表示有 n+1 行（0~n），后面那个参数是每行长什么样
// 3. vector<int>(m+1, 0)
// 每行是一个有 m+1 个元素、全部初始化为 0 的整数数组

// 假设 n=2, m=3，代码创建出这样一个表格：
//         j=0  j=1  j=2  j=3
// i=0  [  0    0    0    0  ]
// i=1  [  0    0    0    0  ]
// i=2  [  0    0    0    0  ]
// 总共 (n+1) 行 × (m+1) 列，为什么要 +1？因为 dp[0][j] 和 dp[i][0] 是边界（空字符串），需要留出第0行和第0列


// 初始化边界
// for(int i = 0; i <= n; i++) dp[i][0] = i;
// for(int j = 0; j <= m; j++) dp[0][j] = j;

// 这个初始化是在处理边界情况：当某个字符串为空时，唯一的办法就是全靠插入或删除。用DP表格来理解最清晰。
// 以 word1 = "horse", word2 = "ros" 为例，表格是这样的：
//       ""  r   o   s
//   ""  0   1   2   3
//   h   1   ?   ?   ?
//   o   2   ?   ?   ?
//   r   3   ?   ?   ?
//   s   4   ?   ?   ?
//   e   5   ?   ?   ?

// 第0列：dp[i][0] = i
// 含义：word1 前 i 个字符 → 空字符串，需要几步？
// 答案就是删除 i 次
// word1前1个字符 "h"   → ""   需要1次删除 → dp[1][0] = 1
// word1前2个字符 "ho"  → ""   需要2次删除 → dp[2][0] = 2
// word1前3个字符 "hor" → ""   需要3次删除 → dp[3][0] = 3
// ...
// 所以：for (int i = 0; i <= n; i++) dp[i][0] = i;

// 第0行：dp[0][j] = j
// 含义：空字符串 → word2 前 j 个字符，需要几步？
// 答案就是插入 j 次
// "" → word2前1个字符 "r"   需要1次插入 → dp[0][1] = 1
// "" → word2前2个字符 "ro"  需要2次插入 → dp[0][2] = 2
// "" → word2前3个字符 "ros" 需要3次插入 → dp[0][3] = 3
// ...
// 所以：for (int j = 0; j <= m; j++) dp[0][j] = j;

// 填完边界后的表格
//       ""  r   o   s
//   ""   0   1   2   3    ← dp[0][j] = j（插入j次）
//   h    1   ?   ?   ?
//   o    2   ?   ?   ?    ← dp[i][0] = i（删除i次）
//   r    3   ?   ?   ?
//   s    4   ?   ?   ?
//   e    5   ?   ?   ?
// 之后的 ? 就靠转移方程从左上角往右下角填满，最终答案在 dp[n][m] 右下角。

// 第0列 = 从 word1 删光，第0行 = 往空串里插满 word2，都是最直观的边界操作数

