// 题目含义：在包含负数的数组中，寻找和至少为 k 的最短连续子数组的长度。 
// 输入输出：输入数组长度 n、目标值 k 及数组元素，输出满足条件的最短子数组长度，若不存在则输出 -1。

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    int n; long long k;
    if(!(cin >> n >> k)) return 0;

    // 前缀和数组，大小为 n+1，P[0]=0
    vector<long long> P(n+1, 0);
    for(int i = 1; i <= n; i++){
        long long val; cin >> val;
        P[i] = P[i-1] + val;
    }

    deque<int> dq;
    int min_len = n + 1;

    for(int i = 0; i <= n; i++){
        // 1. 尝试更新结果：如果当前前缀和 - 队首前缀和 >= k
        while(!dq.empty() && P[i] - P[dq.front()] >= k){
            min_len = min(min_len, i - dq.front());
            dq.pop_front(); // 这个队首以后不需要再考虑了
        }

        // 2. 维持队列单调递增：如果当前前缀和更小，弹出队尾
        while(!dq.empty() && P[i] <= P[dq.back()]){
            dq.pop_back();
        }

        dq.push_back(i);
    }
    cout << (min_len == n + 1 ? -1 : min_len) << endl;
    return 0;
}


// deque（double-ended queue，双端队列）是一种具有队列和栈的性质的数据结构，支持在两端插入和移除元素。 
// 大多数Deque实现对于它们能够包含的元素数没有固定限制，但此接口既支持有容量限制的双端队列，也支持没有固定大小限制的双端队列。