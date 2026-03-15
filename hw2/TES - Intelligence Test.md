# TES - Intelligence Test
> https://www.luogu.com.cn/problem/P3500

## 思路讲解

### 核心问题
判断 B 是否是 A 的子序列，即能否在 A 中**按顺序**找到 B 的每个元素。

### 预处理思路

**关键观察**：对于 B 中每个元素 `b[j]`，需要在 A 中找到一个位置，这个位置必须**严格大于**上一个匹配位置。

**预处理**：建立一个 `map`（或数组），记录每个值在 A 中出现的所有位置（有序）。

```
A = [1, 5, 4, 5, 7, 8, 6]
位置(0-indexed):
  1 -> [0]
  5 -> [1, 3]
  4 -> [2]
  7 -> [4]
  8 -> [5]
  6 -> [6]
```

### 贪心 + 二分搜索

对于查询 B，维护一个变量 `cur_pos`（当前已匹配到 A 的哪个位置之后）：

1. 对 B 中每个元素 `b[j]`，在该值的位置列表中，用**二分查找**找第一个 `> cur_pos` 的位置
2. 如果找到，更新 `cur_pos` 为该位置
3. 如果找不到，说明 B 不是 A 的子序列，输出 `NIE`

### 图示

```
B = [1, 5, 5, 8, 6]
cur_pos = -1

b[0]=1: 在[0]中找>-1的 -> 找到0,  cur_pos=0
b[1]=5: 在[1,3]中找>0的 -> 找到1, cur_pos=1
b[2]=5: 在[1,3]中找>1的 -> 找到3, cur_pos=3
b[3]=8: 在[5]中找>3的  -> 找到5, cur_pos=5
b[4]=6: 在[6]中找>5的  -> 找到6, cur_pos=6
全部匹配 -> TAK ✓
```

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    
    // 预处理：每个值对应在A中出现的位置列表
    // 值域 1~10^6，用数组代替map更快
    const int MAXV = 1e6 + 1;
    vector<vector<int>> pos(MAXV); // pos[v] = A中值v出现的位置列表
    
    for(int i = 0; i < n; i++){
        int a; cin >> a;
        pos[a].push_back(i);
    }
    
    int q; cin >> q;
    while(q--){
        int m; cin >> m;
        
        int cur_pos = -1; // 当前匹配到A的位置
        bool ok = true;
        
        for(int i = 0; i < m; i++){
            int b; cin >> b;
            
            if(!ok) continue; // 已经失败，但还要读完输入
            
            // 在 pos[b] 中找第一个 > cur_pos 的位置
            // upper_bound 找第一个 > cur_pos 的迭代器
            auto& v = pos[b];
            auto it = upper_bound(v.begin(), v.end(), cur_pos);
            
            if(it == v.end()){
                // 找不到，匹配失败
                ok = false;
            } else {
                cur_pos = *it; // 更新当前位置
            }
        }
        
        cout << (ok ? "TAK" : "NIE") << "\n";
    }

    return 0;
}
```

### 复杂度分析

| 阶段 | 复杂度 |
|------|--------|
| 预处理 | O(n) |
| 每次查询 | O(m · log n) |
| 总计 | O(n + sum(m) · log n) |

完全满足 n, sum(m) ≤ 10^6 的要求 ✓

## lower_bound & upper_bound
```cpp
vector<int> v = {1, 3, 3, 5, 7, 9};

// 返回的是迭代器（可以理解为指针）
auto it1 = lower_bound(v.begin(), v.end(), 3);
auto it2 = upper_bound(v.begin(), v.end(), 3);

cout << *it1 << endl;  // 3  (下标1的值)
cout << *it2 << endl;  // 5  (下标3的值)

// 转换成下标
int idx1 = it1 - v.begin();  // 1
int idx2 = it2 - v.begin();  // 3

// 找不到时（超出末尾）
auto it3 = upper_bound(v.begin(), v.end(), 100);
if(it3 == v.end()){
    cout << "不存在" << endl;  // 会走这里
}
```

需求：在 pos[b] 中找第一个 > cur_pos 的下标

cur_pos = 1（已经用了A的下标1）
pos[5]  = [1, 3]

用 upper_bound(pos[5].begin(), pos[5].end(), cur_pos=1)
-> 找第一个 > 1 的 -> 找到 3 ✓

如果用 lower_bound(找>=1的) -> 找到 1
但下标1已经用过了，不能重复用！所以必须用 upper_bound