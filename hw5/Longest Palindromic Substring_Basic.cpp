#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int expandAroundCenter(const string& s, int left, int right){
    while(left >= 0 && right < s.length() && s[left] == s[right]){
        left--;
        right++;
    }

    // 返回长度：扩展停止时，left 和 right 都多走了一步，
    // 因此总长度是 (right - 1) - (left + 1) + 1 = right - left - 1

    return right - left - 1;
}
int main(){
    string s;
    cin >> s;

    int n = s.length();
    if(n == 0){
        cout << 0 << endl;
        return 0;
    }

    int max_len = 0;
    for(int i = 0; i < n; i++){
        // 情况1：回文长度为奇数 (中心是一个字符)
        int len1 = expandAroundCenter(s, i, i);
        // 情况2：回文长度为偶数 (中心是两个字符之间)
        int len2 = expandAroundCenter(s, i, i+1);

        max_len = max({max_len, len1, len2});
    }

    cout << max_len << endl;
    return 0;
}