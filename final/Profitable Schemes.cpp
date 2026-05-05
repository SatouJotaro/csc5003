// 有 n 个成员和 m 种犯罪，每种犯罪需要若干成员并产生若干利润，求所用成员数 ≤ n 且总利润 ≥ minProfit 的子集方案数（mod 10^9+7）

// 做法：二维计数背包 DP
// 核心思路：定义 dp[j][p] = 恰好用了 j 个成员、且利润至少为 p 的方案数
// 关键技巧是利润上限截断到 minProfit——超过 minProfit 的利润都等价，直接 clamp 避免状态爆炸。

// 转移（对每个犯罪，成员数 g，利润 pr，从后往前枚举防止重复选）：
// dp[j][min(p + pr, minProfit)] += dp[j - g][p]

// 为什么利润要截断（clamp）到 minProfit？
// 我们只关心利润"够不够"，不关心具体是多少。利润 6 和利润 10 对我们来说都是"达标了"，存在同一个格子 dp[j][minProfit] 里计数就够了
// 如果不截断，利润维度会膨胀到 ∑pri 最大 10000，而截断后只需 minProfit+1 = 101 个格子

#include <bits/stdc++.h>
using namespace std;

int main() {
    const int MOD = 1e9 + 7;
    int m, n, minProfit;
    cin >> m >> n >> minProfit;

    vector<int> g(m), pr(m);
    for(int i = 0; i < m; i++) cin >> g[i];
    for(int i = 0; i < m; i++) cin >> pr[i];

    // dp[j][p] = 用恰好j个成员且利润至少为p的方案数
    vector<vector<long long>> dp(n+1, vector<long long>(minProfit+1, 0));
    dp[0][0] = 1; // 什么都不做：0人、0利润，1种方案


    for(int i = 0; i < m; i++){
        // 0/1背包：从后往前遍历，防止同一犯罪用两次
        for(int j = n; j >= g[i]; j--){
            for(int p = minProfit; p >= 0; p--){
                int newP = min(p + pr[i], minProfit);
                dp[j][newP] = (dp[j][newP] + dp[j - g[i]][p]) % MOD;
            }
        }
    }

    // 答案：所有成员数 <= n 且利润 >= minProfit 的方案数之和
    long long ans = 0;
    for(int j = 0; j <= n; j++){
        ans = (ans + dp[j][minProfit]) % MOD;
    }

    cout << ans << "\n";
    return 0;
}

// g数组和pr数组是什么？
// 这是每个犯罪的属性，和成员个人无关：
// g[i]  = 第i种犯罪需要的成员数（代价/成本）
// pr[i] = 第i种犯罪能产生的利润（收益）
// 类比到背包问题：g[i] 是物品的重量，pr[i] 是物品的价值，背包容量是 n（成员总数）

// 为什么 j >= g[i]？
// 这是标准0/1背包的写法，含义是：只有当前剩余成员数 j 能"付得起"犯罪i的成员代价 g[i] 时，才考虑选它
// 犯罪i需要 g[i]=2 个成员
// 如果 j=1，根本凑不出2个人去犯罪，跳过
// 如果 j=3，可以选（剩余 j - g[i] = 1 个成员）
// 所以循环下限是 j >= g[i]，和背包问题的 j >= w[i] 完全一样

// 三层循环的转移逻辑逐行解释
// 用样例（n=5, minProfit=3）来追踪犯罪1（g=2, pr=3）:
// for (int i = 0; i < m; i++) {         // 枚举每种犯罪
//     for (int j = n; j >= g[i]; j--) { // j：当前用了j个成员（从大到小）
//         for (int p = minProfit; p >= 0; p--) { // p：当前利润为p

// 核心转移一句话：从"还没选犯罪i的状态 dp[j-g[i]][p]"，选了犯罪i之后变成"用了j个成员、利润变成 p+pr[i]"的状态：
// int newP = min(p + pr[i], minProfit); // 利润截断，超过minProfit就按minProfit算
// dp[j][newP] += dp[j - g[i]][p];
// //  ↑选了犯罪i后   ↑选之前的状态：用了j-g[i]个成员，利润为p

// 具体走一步（犯罪1：g=2, pr=3，从初始状态 dp=1 出发）：
// j=2, p=0:
//   newP = min(0+3, 3) = 3
//   dp[2][3] += dp[2-2][0] = dp[0][0] = 1
//   → dp[2][3] = 1  （选了犯罪1，用2人，利润3）

// 为什么从大到小遍历 j 和 p？ 和0/1背包完全相同的原因——防止同一种犯罪在同一轮中被选两次：
// 如果从小到大枚举j：
//   先更新了 dp[2]，后面遍历到 dp[4] 时又用到了已被更新的 dp[2]
//   → 犯罪i被选了两次，错误！

// 从大到小：每次用到的 dp[j-g[i]] 都是这轮更新前的旧值，正确。

// 为什么最终要加所有 dp[j][minProfit]？
// for (int j = 0; j <= n; j++)
//     ans += dp[j][minProfit];
// dp[j][minProfit] 的含义是："用了恰好 j 个成员，且利润至少为 minProfit的方案数"。

// 题目要求的是成员数 ≤ n，所以要把所有合法成员数（0, 1, 2, ..., n）的方案数全部加起来：
// ans = dp[0][3] + dp[1][3] + dp[2][3] + dp[3][3] + dp[4][3] + dp[5][3]
//     = 0 + 0 + 1 + 0 + 1 + 0
//     = 2  ✓

// dp[2][3]=1：只选犯罪1（2人，利润3）
// dp[4][3]=1：同时选犯罪0和犯罪1（4人，利润5≥3，截断后存在dp[4][3]）

