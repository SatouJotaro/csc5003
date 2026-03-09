#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int manacher(string s){
    // 1. 预处理：将 s 转为 t，例如 aba -> #a#b#a#
    string t = "#";
    for(char c : s){
        t += c;
        t += "#";
    }

    int n = t.length();
    vector<int> p(n, 0); // p[i] 记录以 i 为中心的回文半径
    int C = 0, R = 0; // C 是当前最大回文的中心，R 是最右边界
    int max_len = 0;

    for(int i = 0; i < n; i++){
        // 利用对称性初始化 p[i]
        if( i < R ){
            p[i] = min(R - i, p[2 * C - i]);
        }

        // 向外扩展
        while(i - p[i] - 1 >= 0 && i + p[i] + 1 < n && t[i - p[i] - 1] == t[i + p[i] + 1]){
            p[i]++;
        }

        // 更新中心和右边界
        if( i + p[i] > R){
            C = i;
            R = i + p[i];
        }
        // 记录最大值
        max_len = max(max_len, p[i]);
    }
    return max_len;
}

int main(){
    string s;
    cin >> s;
    cout << manacher(s) << endl;
}