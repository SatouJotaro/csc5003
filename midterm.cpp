#include<bits/stdc++.h>

using namespace std;

int main(){
    string s; cin >> s;
    int n = s.length();
    if(n == 0) {cout << 0 << endl; return 0;}

    vector<vector<bool>> isPal(n, vector<bool>(n, false));
    for(int len = 1; len <= n; len++){
        for(int i = 0; i <= n - len; i++){
            int j = i + len - 1;
            if(s[i] == s[j]){
                if(len <= 2) isPal[i][j] = true;
                else isPal[i][j] = isPal[i+1][j-1]; // 对称过去
            }
        }
    }

    vector<int> dp(n+1 , n);
    dp[0] = -1;

    for(int j = 1; j <= n; j++){
        for(int i = 0; i < j; i++){
            if(isPal[i][j-1]){
                dp[j] = max(dp[j], dp[i] + 1);
            }
        }
    }

    cout << dp[n] << 0;
    return 0;
}