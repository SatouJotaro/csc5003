// 打印机每次打印一段连续相同字符，可以覆盖已有内容，求打印出字符串 s 所需的最少打印次数

// DP状态：dp[l][r] = 打印出子串 s[l..r] 的最少次数

// 转移（两种情况）：
// 若 s[l] == s[r]：打 s[l] 时顺带延伸覆盖到 r 位置，dp[l][r] = dp[l][r-1]（不需要额外一次）
// 否则：枚举分割点 k，将区间拆成两段：dp[l][r] = min(dp[l][k] + dp[k+1][r])

// 初始化：dp[i][i] = 1（单个字符打一次）


#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    string s;
    cin >> n >> s;

    vector<vector<int>> dp(n, vector<int>(n, 0));

    // 按区间长度从小到大枚举
    for(int len = 1; len <= n; len++){
        for(int l = 0; l + len - 1 < n; l++){
            int r = l + len - 1;
            if(l == r) {dp[l][r] = 1; continue;}

            // s[l] 和 s[r] 相同时，打 l 顺带覆盖 r，不多花一次
            if(s[l] == s[r]){
                dp[l][r] = dp[l][r-1];
            } else{
                // 否则枚举分割点
                dp[l][r] = INT_MAX;
                for(int k = l; k < r; k++){
                    // 正确的分割应该是 dp[l][k] + dp[k+1][r]，左闭右闭，不重叠
                    dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r]);
                }
            }
        }
    }

    cout << dp[0][n-1] << endl;
    return 0;
}