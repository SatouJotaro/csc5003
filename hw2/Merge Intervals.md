# Merge Intervals/合并区间

## 核心问题
将一组区间中**所有重叠的区间合并**，最终输出互不重叠的区间集合。

---

## 什么叫"重叠"？

两个区间 `[a, b]` 和 `[c, d]`（假设 a ≤ c），满足 **`c ≤ b`** 时即为重叠：

```
重叠示例：
[1, 3] 和 [2, 6]  → 2 ≤ 3，重叠 → 合并为 [1, 6]
[1, 4] 和 [4, 5]  → 4 ≤ 4，端点相接也算重叠 → 合并为 [1, 5]

不重叠示例：
[1, 3] 和 [5, 8]  → 5 > 3，不重叠，保持独立
```

---

## 输入输出解释

### 输入
| 行 | 内容 | 说明 |
|----|------|------|
| 第1行 | `n` | 区间总数 |
| 第2~n+1行 | `start_i  end_i` | 每个区间的起点和终点 |

### 输出
| 行 | 内容 | 说明 |
|----|------|------|
| 第1行 | `m` | 合并后的区间数 |
| 第2~m+1行 | `start  end` | 每个合并后的区间（按起点升序） |

---

## 样例图解

### 样例1
```
输入区间（数轴可视化）：
[1,3]     ████
[2,6]       ████████
[8,10]              ████
[15,18]                      ██████

合并过程：
[1,3] + [2,6] → 重叠 → [1,6]
[1,6] + [8,10]  → 不重叠，各自独立
[8,10] + [15,18] → 不重叠，各自独立

输出：3个区间
[1,6]  [8,10]  [15,18]
```

### 样例2
```
输入区间：
[1,4]   ████████
[4,5]          ██   ← 端点 4 相接，算重叠！

合并：[1,4] + [4,5] → [1,5]

输出：1个区间
[1,5]
```

---

## 解题思路（核心算法）
1. **按起点排序**所有区间
2. **逐个扫描**，若当前区间的起点 ≤ 上一个区间的终点 → 合并（终点取两者最大值）
3. 否则，将上一个区间加入结果，开始新区间

## 涉及的算法与数据结构知识点

## 1. 核心算法：贪心算法 (Greedy)

```
贪心策略：
每次只考虑当前区间与"已合并区间的末尾"的关系
局部最优 → 全局最优

为什么贪心可行？
排序后，区间按起点有序，只需向右扫描一次
不需要回头，不需要全局比较，O(n) 一次扫描搞定
```

---

## 2. 前置算法：排序 (Sorting)

```
为什么要先排序？

未排序：随机顺序，每个区间可能和任意区间重叠，需要 O(n²) 两两比较
已排序：按起点排序后，只需比较【当前区间】与【前一个区间】

排序方式：按 start_i 升序排列
时间复杂度：O(n log n)  ← 整道题的时间瓶颈
```

---

## 3. 数据结构

### 数组 / 列表 (Array / List)
```
用途：
① 存储输入的 n 个区间        → intervals[]
② 存储合并后的结果区间       → result[]

操作：
- 随机访问 O(1)
- 尾部追加 O(1) 均摊
```

### 二维数组 (2D Array)
```
每个区间本质是长度为2的数组 [start, end]
intervals = [[1,3], [2,6], [8,10], [15,18]]
               ↑      ↑      ↑        ↑
            一行代表一个区间
```

---

## 4. 编程技巧：线性扫描 (Linear Scan)

```
排序后只需一次从左到右扫描：

初始化：将第一个区间放入结果
for 每个后续区间:
    if 与结果末尾区间重叠:
        合并（更新末尾区间的 end）
    else:
        直接加入结果

时间复杂度：O(n)
```

---

## 知识点总览

```
┌─────────────────────────────────────────────────┐
│                  区间合并问题                    │
├──────────────┬──────────────────────────────────┤
│   数据结构   │  算法                            │
├──────────────┼──────────────────────────────────┤
│              │  排序算法          O(n log n)    │
│  二维数组    │  ─────────────────────────────── │
│              │  贪心算法          O(n)          │
│  动态列表    │  ─────────────────────────────── │
│              │  线性扫描          O(n)          │
└──────────────┴──────────────────────────────────┘
        总体时间复杂度：O(n log n)
        空间复杂度：O(n)
```

---

## 与其他知识点的关联

```
区间问题家族（同类型题目）：
                    
  区间合并          ← 本题
  区间插入          (在已合并区间中插入新区间)
  区间调度          (选最多不重叠区间 → 贪心)  
  区间覆盖          (最少区间覆盖全段 → 贪心)
  会议室问题        (判断是否有冲突 → 排序)
  
  核心思想都是：【排序】+【贪心/扫描】
```

---

## 难度分析

| 知识点 | 难度 | 重要性 |
|--------|------|--------|
| 数组操作 | ⭐ | ★★★★★ |
| 排序 | ⭐⭐ | ★★★★★ |
| 线性扫描逻辑 | ⭐⭐ | ★★★★★ |
| 贪心理解 | ⭐⭐⭐ | ★★★☆☆ |

> 💡 **总结**：这道题是 **排序 + 贪心** 的经典组合，是学习区间类问题的入门必做题！

## 代码细节
# 代码问题分析

你的直觉是对的，代码确实有几处错误！逐一解释：

## 你的代码存在的问题

```cpp
vector<vector<int>> intervals;          // ❌ 问题1：空vector，没有空间
for(int i = 0; i < n; i++){
    cin >> intervals[i][0]              // ❌ 越界！没有resize就访问
             >> intervals[0][i];        // ❌ 问题2：下标写错了，应该是intervals[i][1]
}
sort(intervals.begin());                // ❌ 问题3：sort需要两个迭代器参数
```

---

## 三种正确写法

### 方法一：vector\<vector\<int\>\> + resize ✅
```cpp
vector<vector<int>> intervals;
intervals.resize(n, vector<int>(2));  // resize成 n行 × 2列

for(int i = 0; i < n; i++){
    cin >> intervals[i][0] >> intervals[i][1];  // 注意：是[i][1]不是[0][i]
}

sort(intervals.begin(), intervals.end());  // 默认按第一个元素排序 ✅
```

### 方法二：vector\<vector\<int\>\> + push_back ✅（更常用）
```cpp
vector<vector<int>> intervals;

for(int i = 0; i < n; i++){
    int start, end;
    cin >> start >> end;
    intervals.push_back({start, end});  // 直接追加，不需要提前resize
}

sort(intervals.begin(), intervals.end());
```

### 方法三：pair + vector（语义更清晰）✅
```cpp
vector<pair<int,int>> intervals;

for(int i = 0; i < n; i++){
    int start, end;
    cin >> start >> end;
    intervals.push_back({start, end});
}

sort(intervals.begin(), intervals.end()); // pair自动按first排序
// 访问时用 intervals[i].first 和 intervals[i].second
```

---

## 下标错误的图解

```
intervals[i][0]  intervals[i][1]
     ↓                ↓
  [ start,            end   ]   ← 第i个区间
  [ start,            end   ]   ← 第i+1个区间

你写的 intervals[0][i] 是什么意思？
  [ start,  ?, ?, ?, ... ]  ← 只访问第0行，列在变化 ❌
```

---

## 完整正确代码

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    int n;
    cin >> n;
    
    vector<vector<int>> intervals;
    
    for(int i = 0; i < n; i++){
        int start, end;
        cin >> start >> end;
        intervals.push_back({start, end});  // ✅ push_back无需提前resize
    }
    
    sort(intervals.begin(), intervals.end());  // ✅ 需要begin和end两个参数
    
    return 0;
}
```

---

## 三种方法对比

| 方法 | 写法难度 | 可读性 | 推荐度 |
|------|---------|--------|--------|
| `vector<vector<int>>` + resize | 中 | 一般 | ⭐⭐⭐ |
| `vector<vector<int>>` + push_back | 低 | 好 | ⭐⭐⭐⭐ |
| `vector<pair<int,int>>` | 低 | 最好 | ⭐⭐⭐⭐⭐ |

> 💡 **建议**：用 `push_back` 方式，不需要考虑resize，也不会越界！

# 结构体 vs 二维数组

## 结构体完全可以用！

```cpp
struct Interval {
    int start, end;
};
```

但是有一个**关键问题**：

---

## 核心区别：sort() 能否直接用

### ❌ 结构体：sort 不能直接用
```cpp
struct Interval {
    int start, end;
};

vector<Interval> intervals;
sort(intervals.begin(), intervals.end()); 
// ❌ 编译报错！
// 结构体不知道怎么比较大小，必须手动告诉它
```

**必须额外写比较函数：**
```cpp
// 方法一：重载运算符
struct Interval {
    int start, end;
    bool operator<(const Interval& other) const {
        return start < other.start;  // 额外写这个
    }
};

// 方法二：传入lambda
sort(intervals.begin(), intervals.end(), [](Interval a, Interval b){
    return a.start < b.start;        // 额外写这个
});
```

---

### ✅ 二维数组：sort 直接可用
```cpp
vector<vector<int>> intervals;
sort(intervals.begin(), intervals.end()); 
// ✅ 直接可用！
// vector默认按字典序比较：先比[0]，再比[1]
// 恰好就是按start排序，完美符合需求！
```

---

## 为什么 vector 默认排序恰好正确？

```
字典序比较规则：
先比第一个元素 → 就是 start  ✅
若相等再比第二个 → 就是 end   ✅

intervals = [[3,5], [1,4], [1,2]]
排序后      → [[1,2], [1,4], [3,5]]
               ↑先按start升序，start相同再按end升序
               完全符合区间合并的需求！
```

---

## 访问方式对比

```cpp
// 结构体：语义清晰，但需要额外定义
interval.start
interval.end

// 二维数组：简洁，索引有通用性
intervals[i][0]   // start
intervals[i][1]   // end

// pair：折中方案
interval.first    // start
interval.second   // end
```

---

## 总结对比表

| 对比项 | 结构体 | vector\<vector\<int\>\> | pair |
|--------|--------|------------------------|------|
| sort直接用 | ❌ 需要写比较函数 | ✅ 开箱即用 | ✅ 开箱即用 |
| 代码量 | 多（需定义结构体） | 少 | 少 |
| 可读性 | 最好(.start/.end) | 一般([i][0]/[i][1]) | 一般(.first/.second) |
| LeetCode题目标准格式 | ❌ | ✅ | ❌ |
| 推荐度 | ⭐⭐ | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ |

---

> 💡 **结论**：结构体能用，但要多写比较函数。
> 用 `vector<vector<int>>` 的最大优势就是 **sort 开箱即用**，
> 而且这也是 LeetCode 此类题目的**标准输入格式**，直接匹配！

你的代码逻辑大体方向是对的，但在**算法逻辑**和**边界处理**上有几个致命的问题，导致程序会崩溃或输出错误答案。

### 1. 致命错误：数组越界与逻辑错误
*   **越界**：在 `for(int i = 0; i < n; i++)` 中，当你访问 `intervals[i+1]` 时，当 `i = n-1` 时，`i+1` 等于 `n`，这会导致程序崩溃（数组访问越界）。
*   **逻辑错误**：区间合并通常需要维护一个“当前正在处理的区间”。你目前的逻辑是：每遍历到一个就试图“立刻”合并，这在处理多段交叉（如 `[1,4], [2,5], [3,6]`）时会逻辑混乱。

### 2. 推荐的“合并区间”标准逻辑
通常的做法是：**维护一个当前的 `last_interval`**，不断尝试把新区间“吞入”它。

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    int n;
    cin >> n;
    if (n == 0) return 0; // 边界处理

    vector<vector<int>> intervals;
    for(int i = 0; i < n; i++){
        int start, end;
        cin >> start >> end;
        intervals.push_back({start, end});
    }
    
    sort(intervals.begin(), intervals.end()); 

    vector<vector<int>> result;
    // 1. 把第一个区间放进去作为起始
    result.push_back(intervals[0]);

    // 2. 从第二个开始遍历
    for(int i = 1; i < n; i++){
        // 如果当前区间的起点 <= 结果集中最后一个区间的终点，说明有重叠
        if(intervals[i][0] <= result.back()[1]){
            // 合并：更新结果集中最后一个区间的终点为两者的较大值
            result.back()[1] = max(result.back()[1], intervals[i][1]);
        }
        else{
            // 没有重叠，直接放入新区间
            result.push_back(intervals[i]);
        }
    }

    // 3. 输出结果
    for(int i = 0; i < result.size(); i++){
        cout << result[i][0] << " " << result[i][1] << endl; // 加个空格！
    }
    return 0;
}
```

### 做了哪些修改？
1.  **逻辑优化**：不再遍历原始数组试图合并，而是通过 `result.back()` 获取当前已经合并好的区间的“尾巴”，与 `intervals[i]` 进行比较。
2.  **避免指针/下标错误**：直接用 `i=1` 到 `n-1` 的循环，规避了 `i+1` 越界的问题。
3.  **输出优化**：在 `result[i][0]` 和 `result[i][1]` 之间加了空格 `" "`，否则 `1` 和 `5` 会输出成 `15`。
4.  **合并策略**：这才是标准的“贪心”算法，能够正确处理形如 `[1,2], [2,3], [3,4]` 合并成 `[1,4]` 的情况。

### 调试建议
*   **输入测试**：测试 `3` 个区间 `[1,3], [2,6], [8,10]`。
*   **逻辑模拟**：
    *   初始：`result = [[1,3]]`
    *   i=1: `intervals[1]= [2,6]`, `2 <= 3` (有重叠)，修改 `result` 为 `[[1,6]]`
    *   i=2: `intervals[2]= [8,10]`, `8 > 6` (无重叠)，`result` 追加，变成 `[[1,6], [8,10]]`
    *   完美！

这是非常经典的题目，你的思路是正确的，代码逻辑只要根据上面微调一下就完全没问题了！