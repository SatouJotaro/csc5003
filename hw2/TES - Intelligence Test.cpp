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
        
        int cur = -1;
        bool ok = true;
        for (int i = 0; i < m && ok; ++i) {
            int x = b[i]; // 拿到 10。
            const vector<int> &vec = pos[x]; // & 是引用，意思是你不必把整个数组拷贝过来，而是直接拿着这个存储桶的“地址”。vec 现在就等于 pos[10]，也就是 {0, 2}。
            
            if (vec.empty()) {
                ok = false;            // 根本不存在
                break;
            }


            // 在 vec 中寻找 > cur 的最小下标
            auto it = lower_bound(vec.begin(), vec.end(), cur + 1);
            // cur + 1 等于 -1 + 1 = 0。
            // lower_bound 翻译成人话就是：“在 {0, 2} 里找一个大于等于 0 的最小值”。
            // 因为 0 本身就在 {0, 2} 里，所以它找到了 0。
            // it 现在是一个“迭代器”（你可以把它看作是指向 0 这个位置的指针）。
            
            if (it == vec.end()) {
                ok = false;            // 没有合适的出现位置
                break;
            }
            
            cur = *it;                 // 成功匹配
            // 什么是 *？ it 是个指针，*it 表示“取出指针指向的那个值”。
            // *it 取出了 0。所以现在 cur = 0。
            // 意义： 我们确认了第一个 10 出现在母串的索引 0 处。
        }
        
        cout << (ok ? "TAK" : "NIE") << '\n';
    }
    return 0;
}