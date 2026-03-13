// 原来的代码主要问题在于逻辑嵌套太深。其实，我们可以将“判断某个位置是否可消除”封装成一个函数，这样主循环看起来就像是“不断扫描直到没活可干”。
// 函数化：逻辑分离，一眼看出“检查”和“消灭”是分开的。
// 逻辑简化：使用 count 记录已被转化为 ? 的字符数，如果覆盖完所有字符数达到 n，则直接成功。


#include<bits/stdc++.h>
using namespace std;

// 检查在位置 i 是否可以把 stamp “反盖”上去
bool canStamp(int i, const string& stamp, string& t){
    bool hasChar = false; // 必须保证这一步盖章至少覆盖了一个有效字符
    int m = stamp.size();
    for(int j = 0; j < m; j++){
        if(t[i+j] != '?' && t[i+j] != stamp[j]) return false;
        hasChar = true;
    }
    return hasChar; // 只要不冲突就返回true
}
void solve(){
    string stamp, t;
    cin >> stamp >> t;
    int n = t.size(), m = stamp.size();

    // 标记每个位置是否已经变成 ?
    vector<bool> visited(n, false);
    int totalQ = 0;
    bool changed = true;

    while(changed){
        changed = false;
        for(int i = 0; i <= n - m; i++){
            if(!visited[i] && canStamp(i, stamp, t)){
                for(int j = 0; j < m; j++){
                    if(t[i+j] != '?'){
                        t[i+j] = '?';
                        totalQ++;
                    }
                }
                visited[i] = true;
                changed = true;
            }
        }
    }

    cout << (totalQ == n ? "YES" : "NO") << endl;
}
int main(){
    int T; cin >> T;
    while(T--) solve();
    return 0;
}