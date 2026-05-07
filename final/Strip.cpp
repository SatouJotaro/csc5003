// 题目含义：将长度为 n 的数组切分成若干段，要求每段长度至少为 l，且每段内的最大值与最小值之差不超过 s，求最少能切成多少段
// 输入输出：输入 n,s,l 及数组元素，输出最小分段数；若无法完成切分，则输出 -1

#include <iostream>
#include <vector>
#include <deque>
#include <set>

using namespace std;

const int INF = 1e9;

int main() {
    int n, s, l; cin >> n >> s >> l;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];

    vector<int> dp(n+1, INF);
    dp[0] = 0;

    deque<int> q_max, q_min; // 用于维护当前 [L, i-1] 的极大极小值
    multiset<int> ms;

    int L = 0, p2 = 0; // L 是极差窗口左界，p2 是放入 multiset 的指针
    for(int i = 1; i <= n; ++i){
        // 1. 更新极差窗口：维护 a[L...i-1] 的 max - min <= s
        while(!q_max.empty() && a[q_max.back()] <= a[i-1]) q_max.pop_back();
        while(!q_min.empty() && a[q_min.back()] >= a[i-1]) q_min.pop_back();
        q_max.push_back(i-1);
        q_min.push_back(i-1);

        while(a[q_max.front()] - a[q_min.front()] > s){
            // 当 L 右移时，如果 dp[L] 之前被加入过 ms，则将其移除
            // 只有当 p2 > L 时，说明 dp[L] 曾被插入过 ms
            if(p2 > L && dp[L] != INF){
                auto it = ms.find(dp[L]);
                if(it != ms.end()) ms.erase(it);
            }
            L++;
            if(!q_max.front() < L && q_max.front() < L) q_max.pop_front();
            if(!q_min.front() < L && q_min.front() < L) q_min.pop_front();
        }

        // 2. 将新进入 [L, i-l] 范围的 dp[j] 加入 multiset
        while(p2 <= i - l){
            if(p2 >= L && dp[p2] != INF) ms.insert(dp[p2]);
            p2++;
        }
        
        // 3. 计算当前的 dp[i]
        if(!ms.empty()) dp[i] = *ms.begin() + 1;
    }
    cout << (dp[n] >= INF ? -1 : dp[n]) << endl;
    return 0;
}

// MULTISET 数据类型是存储无序集的集合类型，它能包含重复的元素值。
// MULTISET 中的元素没有顺序位置。 也就是说，在MULTISET 中不存在第一元素、第二元素或第三元素的概念。