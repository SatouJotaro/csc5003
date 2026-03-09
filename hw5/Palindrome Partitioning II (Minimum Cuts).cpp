#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int minCuts(string s){
    int n = s.length();
    if(n == 0) return 0;

    // 1. 预处理回文表
    vector<vector<bool>> isPal(n, vector<bool>(n, false));
    for(int len = 1; len <= n; len++){
        for(int i = 0; i <= n - len; i++){
            int j = i + len - 1;
            if(s[i] == s[j]){
                if(len <= 2) isPal[i][j] = true;
                else isPal[i][j] = isPal[i + 1][j - 1];
            }
        }
    }

    // 2. DP 计算最小切割
    // dp[i] 表示前 i 个字符组成的字符串最少需要切割多少次
    vector<int> dp(n + 1, n);
    dp[0] = -1;

    for(int i = 1; i <= n; i++){
        for(int j = 0; j < i; j++){
            if(isPal[j][i-1]){
                dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }
    return dp[n];
}
int main(){
    string s;
    if(cin >> s){
        cout << minCuts(s) << endl;
    }
    return 0;
}