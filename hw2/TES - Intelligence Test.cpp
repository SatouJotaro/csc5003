#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if(!(cin >> n)) return 0;          // 防止空输入
    const int MAXV = 1'000'000;        // 题目给出的值域上限
    vector<vector<int>> pos(MAXV + 1); // pos[value] 保存所有下标（0-index）
    
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        pos[x].push_back(i);
    }
    
    int q; cin >> q;
    while (q--) {
        int m; cin >> m;
        vector<int> b(m);
        for (int i = 0; i < m; ++i) cin >> b[i];
        
        int cur = -1; // 当前匹配到的 A 中的最右位置
        bool ok = true;
        for (int i = 0; i < m && ok; ++i) {
            int x = b[i];
            const vector<int> &vec = pos[x];
            if (vec.empty()) {
                ok = false;            // 根本不存在
                break;
            }
            // 在 vec 中寻找 > cur 的最小下标
            auto it = lower_bound(vec.begin(), vec.end(), cur + 1);
            if (it == vec.end()) {
                ok = false;            // 没有合适的出现位置
                break;
            }
            cur = *it;                 // 成功匹配
        }
        cout << (ok ? "TAK" : "NIE") << '\n';
    }
    return 0;
}