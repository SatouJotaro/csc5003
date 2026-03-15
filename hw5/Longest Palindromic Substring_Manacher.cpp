#include<bits/stdc++.h>
using namespace std;

int manacher(string s){
    // 预处理 每个字符中间插#
    string t = "#";
    for(char c : s){
        t += c;
        t += "#";
    }


    int n = t.length();
    vector<int> p(n, 0); // p[i] 记录以i为中心的回文直径
    int C = 0, R = 0;   // C是当前最大回文的中心，R是右边界，把他们当成指针
    int max_len = 0;

    for(int i = 0; i < n; i++){
        // 初始化p[i]
        if(i < R){
            p[i] = min(R - i, p[2 * C - i]);
        }

        // 扩大回文串
        while(i - p[i] - 1 >= 0 && i + p[i] + 1 < n && t[i - p[i] - 1] == t[i + p[i] + 1]) p[i]++;

        // 更新最大回文的中心， 更新右边界
        if(i + p[i] > R){
            C = i;
            R = i + p[i];
        }
        max_len = max(max_len, p[i]);
    }

    return max_len;
}

int main(){
    string s; cin >> s;
    cout << manacher(s) << endl;
    return 0;
}