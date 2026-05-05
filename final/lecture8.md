# 区间DP / 多维DP的核心思想
动态规划的本质是避免重复计算 。设计DP时需要：

定义 f[][] 表示某个子问题的最优解
推导状态转移方程
保证最优解可以由子状态组合而成（最优子结构）

实战建议：优先使用记忆化搜索（memoization）来实现，避免手动枚举顺序的错误 

## 例题 1：Borrowing Classroom（借教室）
问题：n天有不同数量的教室，m个请求按顺序满足，找第一个无法满足的请求编号

关键技巧：
单调性：check(k) = 前k个请求能否都满足。若前k个可以，前k-1个一定也可以 → 可以二分答案
快速可行性检查：每个请求 (d, s, t) 对区间 [s,t] 每天加需求量 d，用差分数组或线段树做区间加法 + 前缀和查询

## 例题 2：Edit Distance（编辑距离）

问题：三种操作（插入/删除/替换），word1变成word2的最少操作数 。

DP状态：F[i][j] = word1前i字符变成word2前j字符的最少操作数 。

转移方程：
若 word1[i] == word2[j]：F[i][j] = F[i-1][j-1]

否则取三种操作的最小值：
F[i][j]=1+min(F[i−1][j], F[i][j−1], F[i−1][j−1])

分别对应：删除word1末尾、插入word2末尾字符、替换

## 例题 3：Burst Balloons（戳气球）
问题：戳破气球i得 nums[left] * nums[i] * nums[right] 分，求最大得分 。

关键转化：不思考"先戳哪个"，而是思考**"区间内最后戳哪个"** 。

DP状态：F[l][r] = 戳完开区间 (l,r) 内所有气球的最大得分。

转移：假设气球 k 是区间 (l,r) 内最后被戳的：
F[l][r]= max(F[l][k]+F[k][r]+nums[l]×nums[k]×nums[r])
(l<k<r)

因为 k 最后被戳时，其邻居必然是 l 和 r，状态不再动态变化

## 例题 4：Strange Printer（奇怪的打印机）
问题：打印机每次打一段相同字符（可覆盖），求打印字符串 s 的最少轮数 。

DP状态：F[l][r] = 打印子串 s[l..r] 的最少轮数 。

转移：

1. 基础：dp[l][r] = dp[l+1][r] + 1（单独打 s[l]）

2. 优化：若存在 k（l < k ≤ r）使得 s[k] == s[l]，则打 s[l] 时顺带覆盖到 k 位置：dp[l][r] = min(dp[l][r], dp[l+1][k-1] + dp[k][r])

## 例题 5：Minimum Cost to Merge Stones（合并石子）
问题：每次合并恰好 K 堆相邻石子，代价是石子总数，求合并成1堆的最小代价 。

可行性判断：每次合并减少 K-1 堆，要使 n 堆变 1 堆，必须 (n-1) % (K-1) == 0，否则返回 -1 。

DP状态：F[i][j] = 将 stones[i..j] 合并成尽可能少的堆的最小代价 。

转移：

dp[i][j] = min(dp[i][mid] + dp[mid+1][j])，其中 mid = i, i+(K-1), i+2(K-1), ...

若 (j-i) % (K-1) == 0，说明可以合并成一堆，再加上 sum(i,j)

## 例题 6：Cherry Pickup（摘樱桃）
问题：n×n网格，从 (0,0) 走到 (n-1,n-1) 再返回，最多摘多少樱桃（同一格只算一次）

关键转化：来回两趟难以直接建模，将其等价转化为两人同时从 (0,0) 走到 (n-1,n-1) 

DP状态：F[k][r1][r2] = 两人均走了 k 步、walker1 在第 r1 行、walker2 在第 r2 行时的最大樱桃数。列由 c = k - r 推算，所以不需要存列 

转移：枚举两人上一步各自往右或往下，取4种组合的最大值，再加当前两格的樱桃（若在同一格则只加一次）

## 例题 7：Remove Boxes（移除盒子）⭐最难
问题：移除一段连续同色 k 个盒子得 k² 分，求移除所有盒子的最大分数 。

难点：普通 F[l][r] 不够，因为区间外的同色盒子可以与区间端点合并，影响最优决策 。

DP状态：F[l][r][k] = 解决区间 [l,r]，且 boxes[r] 右侧已附加 k 个同色盒子时的最大得分 。

转移（两种选择）：

Option 1 - 直接移除 boxes[r]：
dp[l][r][k] = dp[l][r-1][0] + (k+1)²

Option 2 - 找到同色 boxes[m] 合并（l ≤ m < r 且 boxes[m] == boxes[r]）：先清空 (m, r) 中间部分，让 boxes[m] 与 boxes[r] 相邻：
dp[l][r][k] = max(dp[l][m][k+1] + dp[m+1][r-1][0])

---

| 题目    | DP维度 | 核心技巧         |
| ----- | ---- | ------------ |
| 借教室   | 差分数组 | 二分答案 + 差分区间加 |
| 编辑距离  | 2D   | 经典字符串DP      |
| 戳气球   | 2D区间 | 思考"最后戳哪个"    |
| 奇怪打印机 | 2D区间 | 相同字符合并打印     |
| 合并石子  | 2D区间 | 可行性 + 区间分割   |
| 摘樱桃   | 3D   | 两人同步走        |
| 移除盒子  | 3D区间 | 附加外部状态 k     |

最核心的设计原则：状态要能完整表达子问题，当普通区间DP不满足最优子结构时，需要增加维度来记录外部信息（如 Remove Boxes 的 k）

---

# 区间DP 
## 什么是区间DP？
区间DP是一种以区间 [l, r] 为状态的动态规划，核心思想是**"小区间支撑大区间"**：先算出所有短区间的最优解，再合并得到更长区间的最优解 。

它适用于这类问题：将一段连续区间的元素合并/分割/操作，求最优值（如你课上的戳气球、合并石子等）

## DP三要素
① 状态定义
dp[i][j] // 表示区间 [i, j] 的最优解（最小代价/最大得分等）

② 状态转移

枚举区间内的分割点 k，将大区间拆成两个小区间：

dp[i][j]= min(dp[i][k]+dp[k+1][j]+cost(i,j))
i≤k<j

③ 初始化
长度为 1 的区间（dp[i][i]）是边界，单独初始化
求最小值时，其余初始化为 INF；求最大值时初始化为 0 或 -INF

# 代码写法
## 标准写法
区间DP必须按区间长度从小到大枚举，保证转移时小区间已经算好

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 305;
int dp[MAXN][MAXN];
int n;

int main() {
    // 1. 读入数据
    // ...

    // 2. 初始化
    memset(dp, 0x3f, sizeof(dp));   
    // 求最小值：全部初始化为 INF
    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;               
        // 长度为1的区间，base case

    // 3. 按区间长度枚举（核心！）
    for (int len = 2; len <= n; len++) {        
        // 枚举区间长度
        for (int i = 1; i + len - 1 <= n; i++) { 
            // 枚举起点 i
            int j = i + len - 1;               
            // 终点 j
            for (int k = i; k < j; k++) {      
                // 枚举分割点 k
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + cost(i, j));
            }
        }
    }

    // 4. 答案
    cout << dp[1][n] << endl;
    return 0;
}
```

## 记忆化搜索写法
这种写法更不容易出错，不用手动想枚举顺序

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
int dp[MAXN][MAXN];
bool vis[MAXN][MAXN];
int n;

int solve(int l, int r) {
    if (l == r) return 0;       
    // base case
    if (vis[l][r]) return dp[l][r];  
    // 已算过，直接返回
    
    vis[l][r] = true;
    dp[l][r] = INT_MAX;         
    // 求最小值初始化为极大值
    
    for (int k = l; k < r; k++) {
        dp[l][r] = min(dp[l][r], solve(l, k) + solve(k+1, r) + cost(l, r));
    }
    return dp[l][r];
}

int main() {
    memset(vis, false, sizeof(vis));
    cout << solve(1, n) << endl;
    return 0;
}
```
---
|      | 迭代写法（循环）    | 记忆化搜索（递归）             |
| ---- | ----------- | --------------------- |
| 枚举顺序 | 必须手动按长度从小到大 | 自动处理，无需考虑             |
| 出错风险 | 枚举顺序写错就全错   | 较低，更直观                |
| 性能   | 略快（无递归开销）   | 略慢（函数调用栈）             |
| 推荐场景 | 状态简单的2D区间DP | 状态复杂（3D如Remove Boxes） |
---

## 初始化常见陷阱
```cpp
// ❌ 错误：直接初始化dp[i][j] = 0，然后求最小值
// 会导致非法状态被当成合法答案

// ✅ 正确：求最小值时用 INF 初始化
memset(dp, 0x3f, sizeof(dp));   // 0x3f3f3f3f ≈ 1e9，常用技巧
for (int i = 1; i <= n; i++) dp[i][i] = base_case_value;

// ✅ 正确：求最大值时用 0 或 -INF 初始化
memset(dp, 0, sizeof(dp));
for (int i = 1; i <= n; i++) dp[i][i] = base_case_value;
```
