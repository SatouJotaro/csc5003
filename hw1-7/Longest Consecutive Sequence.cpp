// 题意：给一个无序、可含重复数字的整数数组，求数组里最长连续整数序列的长度（数字不用在原数组相邻）。
// 输入：先给数组长度 n，再给 n 个整数；
// 输出：直接打印最长连续序列的长度。
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    unordered_set<int> s; // 哈希集合：去重+快速查找

    // 插入所有元素（自动去重）
    for(int i = 0; i < n; i++){
        int x; cin >> x;
        s.insert(x);
    }

    int max_len = 0;

    // 遍历每个数字，只处理【连续序列起点】
    for(int x : s){
        if(!s.count(x-1)){
            int cur = x, cur_len = 1;

            while(s.count(cur + 1)){
                cur++;
                cur_len++;
            }

            max_len = max(max_len, cur_len);
        }
    }

    cout << max_len << endl;
    return 0;
}


// count() = 统计某个元素在容器中出现的次数
// 对于集合 (set)：元素唯一，所以只会返回 0（不存在）或 1（存在）
// 能用 count () 的数据结构（C++ ACM 常用）
    // 哈希集合：unordered_set（本题用的）
    // 有序集合：set
    // 哈希映射：unordered_map
    // 有序映射：map