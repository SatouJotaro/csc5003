// 题目含义：从 n 张图片中恰好挑选 x 张转发，要求任意连续的 k 张图片中都至少包含一张被转发的图片，求转发图片美观度之和的最大值
// 输入输出：输入 n,k,x 及美观度数组，输出最大和；若无法满足条件则输出 -1。

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

const long long INF = 1e16; // 必须足够大以防负数溢出

int main() {
    int n, k, x;
    cin >> n >> k >> x;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // dp[j][i] 表示选了 j 个，最后一个是 i
    // 用 vector<vector> 可能会占 190MB 空间，若内存限制极严可用两行滚动数组
    // 为了防止 MLE 或 RE，使用滚动数组 [2][n+1]
    // dp[0][...] 代表上一层 (j-1)，dp[1][...] 代表当前层 (j)
    vector<vector<long long>> dp(2, vector<long long>(n+1, -INF));

    dp[0][0] = 0;

    for(int j = 1; j <= x; j++){
        int cur = j % 2;
        int prev = (j - 1) % 2;
        // 每一层开始前，清空当前层的旧数据
        fill(dp[cur].begin(), dp[cur].end(), -INF);

        deque<int> dq;
        // 因为 dp[j][i] 依赖上一行 dp[j-1][p]，p 从 i-k 开始
        
        // 在计算 dp[j][i] 时，我们需要考查上一层 dp[j-1][p]
        // 其中 p 范围在 [i-k, i-1]

        for(int i = 1; i <= n; i++){
            // 1. 将新的合法候选 p = i-1 加入队列
            // 1. 入队：将上一个可能的状态 dp[j-1][i-1] 放入队列
            // 注意只有合法的状态 ( > -INF) 才能参与转移
            int p = i - 1;
            if(dp[prev][p] != -INF){
                while(!dq.empty() && dp[prev][dq.back()] <= dp[prev][p]) dq.pop_back();
                dq.push_back(p);
            }

            // 2. 移除超出窗口范围的索引 (距离 > k)
            // 2. 出队：排除距离当前位置 i 超过 k 的索引
            while(!dq.empty() && dq.front() < i - k){
                dq.pop_front();
            }
            
            // 3. 转移
            if(!dq.empty()){
                dp[cur][i] = dp[prev][dq.front()] + a[i];
            }
        }
    }

    long long ans = -1;
    int last_layer = x % 2;
    // 最后一张选中的图片必须能覆盖到终点，即索引在 [n-k+1, n] 之间
    for(int i = max(n - k + 1, 1); i <= n; i++){
        ans = max(ans, dp[last_layer][i]);
    }

    cout << ans << endl;
    return 0;
}