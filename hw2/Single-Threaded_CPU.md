# Single-Threaded_CPU/单线程CPU - medium
## 📥 输入输出分析

**输入：**
- 第一行：整数 `n`（任务数量）
- 接下来 `n` 行：每行两个整数 `enqueueTime_i`（任务进入队列的时刻）和 `processingTime_i`（CPU处理所需时间）

**输出：**
- 一行 `n` 个整数，表示 CPU **按顺序处理任务的原始下标**

---

## 🔑 涉及知识点

| 知识点 | 用途 |
|--------|------|
| **模拟** | 模拟 CPU 调度过程 |
| **排序** | 按入队时间排序，方便判断哪些任务已可用 |
| **最小堆（优先队列）** | 在所有可用任务中快速选出处理时间最短的 |
| **贪心算法** | 每次选局部最优（最短处理时间）的任务 |

---

## 💡 解题思路（Step by Step）

### 核心策略：
> **排序 + 最小堆 模拟**

### 步骤：

```
1. 记录每个任务的原始下标，然后按 enqueueTime 排序
2. 维护一个最小堆，Key = (processingTime, 原始下标)
   → 自动实现"时间最短优先，时间相同则下标小的优先"
3. 模拟 currentTime，每次：
   a. 将所有 enqueueTime ≤ currentTime 的任务加入堆
   b. 若堆为空（没有可用任务）→ 直接跳到下一个任务的 enqueueTime
   c. 若堆非空 → 弹出堆顶任务，记录下标，currentTime += processingTime
4. 重复直到处理完所有 n 个任务
```

---

## 📝 手动追踪 Sample #1

**任务列表：**
| 下标 | enqueueTime | processingTime |
|------|-------------|----------------|
| 0    | 1           | 2              |
| 1    | 2           | 4              |
| 2    | 3           | 2              |
| 3    | 4           | 1              |

| 步骤 | currentTime | 加入堆的任务 | 堆内容(procTime,idx) | 处理任务 | 结果 |
|------|-------------|------------|---------------------|---------|------|
| 初始 | 0 → 跳到1   | -          | 空                  | -       | []   |
| 1    | 1           | Task0      | {(2,0)}             | Task0   | [0]  |
| 2    | 1+2=**3**   | Task1,Task2| {(2,2),(4,1)}       | Task2   | [0,2]|
| 3    | 3+2=**5**   | Task3      | {(1,3),(4,1)}       | Task3   | [0,2,3]|
| 4    | 5+1=**6**   | -          | {(4,1)}             | Task1   | [0,2,3,1]|

✅ 输出：`0 2 3 1`

---

## 💻 C++ 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    // 存储 (enqueueTime, processingTime, 原始下标)
    vector<tuple<long long, long long, int>> tasks(n);
    for (int i = 0; i < n; i++) {
        long long e, p;
        cin >> e >> p;
        tasks[i] = {e, p, i};
    }
    
    // 按 enqueueTime 排序
    sort(tasks.begin(), tasks.end());
    
    // 最小堆：(processingTime, 原始下标)
    // pair 的比较是字典序：先比 processingTime，相同再比 index → 完美满足题意
    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > pq;
    
    vector<int> result;
    long long currentTime = 0;
    int taskIdx = 0; // 排序后的任务指针
    
    while ((int)result.size() < n) {
        // 将所有已可用的任务加入堆
        while (taskIdx < n && get<0>(tasks[taskIdx]) <= currentTime) {
            pq.push({get<1>(tasks[taskIdx]), get<2>(tasks[taskIdx])});
            taskIdx++;
        }
        
        if (pq.empty()) {
            // CPU 空闲且无可用任务，直接跳到下一个任务的入队时间
            currentTime = get<0>(tasks[taskIdx]);
        } else {
            // 选处理时间最短的任务（自动处理 tie）
            auto [procTime, idx] = pq.top();
            pq.pop();
            result.push_back(idx);
            currentTime += procTime;  // 注意用 long long！
        }
    }
    
    // 输出结果
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << "\n";
    
    return 0;
}
```

---

## ⚠️ 易错点提示

| 易错点 | 说明 |
|--------|------|
| **整数溢出** | `currentTime` 最坏情况 = n × 10^9 = 10^14，必须用 `long long` |
| **空堆跳转** | CPU 空闲且无任务时，需直接跳时间，否则会死循环 |
| **保留原始下标** | 排序会改变顺序，必须在排序前保存原始下标 |
| **堆的排序规则** | `pair<processingTime, index>` 的字典序自然实现双重排序 |

---

## ⏱️ 复杂度分析

- **时间复杂度**：O(n log n)，排序 + 堆操作各 O(n log n)
- **空间复杂度**：O(n)，堆最多存 n 个元素

---

## 1️⃣ `greater` — 到底弹出大的还是小的？

**结论：`greater` 让小的先弹出（最小堆）**

```cpp
// 默认 priority_queue → 最大堆，大的先出
priority_queue<int> maxHeap;
maxHeap.push(3); maxHeap.push(1); maxHeap.push(2);
maxHeap.top(); // 输出 3（最大值先出）

// 加了 greater → 最小堆，小的先出
priority_queue<int, vector<int>, greater<int>> minHeap;
minHeap.push(3); minHeap.push(1); minHeap.push(2);
minHeap.top(); // 输出 1（最小值先出）
```

```
记忆方法：
greater（更大的）放到堆底 → 小的浮到顶 → 小的先出
```

---

## 2️⃣ `get<0>` `get<1>` `get<2>` — tuple的元素访问

**`tuple` 是什么？**

```
tuple 就像一个可以装不同类型的盒子
pair  只能装 2 个东西
tuple 可以装 任意多个东西
```

```cpp
// pair 只能装两个
pair<int, string> p = {1, "hello"};
p.first;   // 1
p.second;  // "hello"

// tuple 可以装三个甚至更多
tuple<int, string, double> t = {1, "hello", 3.14};

// 不能用 .first .second，要用 get<下标>
get<0>(t);  // 1        第0个元素
get<1>(t);  // "hello"  第1个元素
get<2>(t);  // 3.14     第2个元素
```

**对应题目中的用法：**
```cpp
// tasks[i] 是 tuple<long long, long long, int>
//                      ↑第0个        ↑第1个     ↑第2个
//                  enqueueTime  processingTime  原始下标

tasks[i] = {e, p, i};

get<0>(tasks[taskIdx])  // 取 enqueueTime
get<1>(tasks[taskIdx])  // 取 processingTime  
get<2>(tasks[taskIdx])  // 取 原始下标
```

---

## 3️⃣ `auto` — 自动推断类型

**`auto` 让编译器自动判断变量类型，不用手动写**

```cpp
// 不用 auto，要手写类型（很麻烦）
int a = 5;
vector<int>::iterator it = vec.begin();
pair<long long, int> p = pq.top();

// 用 auto，编译器自动推断（简洁）
auto a = 5;                // 自动推断为 int
auto it = vec.begin();     // 自动推断为 vector<int>::iterator
auto p = pq.top();         // 自动推断为 pair<long long, int>
```

```
注意：auto 不是"不知道类型"
      而是"我知道类型，但让编译器帮我写"
      编译时类型已经完全确定
```

---

## 4️⃣ `auto [procTime, idx]` — C++17 结构化绑定

**这是 C++17 的新语法，叫「结构化绑定」，用来自动拆解 pair/tuple**

```cpp
pair<long long, int> p = {100, 3};

// 旧写法：手动取
long long procTime = p.first;
int idx = p.second;

// C++17新写法：一行拆解，自动定义变量！
auto [procTime, idx] = p;
// procTime 自动 = p.first  = 100
// idx      自动 = p.second = 3
```

**对应题目中的用法：**
```cpp
// pq.top() 返回 pair<long long, int>
//                       ↑               ↑
//                  processingTime    原始下标

auto [procTime, idx] = pq.top();
// 等价于：
// long long procTime = pq.top().first;
// int idx = pq.top().second;
```

---

## 📊 总结对比

| 语法 | 作用 | 等价写法 |
|------|------|---------|
| `greater<T>` | 构造最小堆（小的先出） | 无简化写法 |
| `get<N>(tuple)` | 取 tuple 第N个元素 | 无简化写法 |
| `auto x = ...` | 自动推断类型 | 手写完整类型名 |
| `auto [a,b] = pair` | 一行拆解pair/tuple | `a=p.first; b=p.second;` |

---

## 🔧 如果不想用这些新语法，等价的"传统写法"

```cpp
// 原代码（使用新语法）
auto [procTime, idx] = pq.top();
pq.pop();

// ↓ 等价的传统写法 ↓
long long procTime = pq.top().first;
int idx = pq.top().second;
pq.pop();
```

```cpp
// 原代码（使用新语法）
while (taskIdx < n && get<0>(tasks[taskIdx]) <= currentTime) {
    pq.push({get<1>(tasks[taskIdx]), get<2>(tasks[taskIdx])});
    taskIdx++;
}

// ↓ 等价的传统写法（用结构体更清晰）↓
struct Task {
    long long enqueueTime, processingTime;
    int index;
};
// 然后直接用 tasks[taskIdx].enqueueTime 访问
```

## 问题5：tuple 排序规则

```cpp
sort(tasks.begin(), tasks.end());
```

**tuple 默认按「字典序」比较：先比第0个，相等再比第1个，再相等比第2个...**

```
tasks[i] = {enqueueTime, processingTime, 原始下标}
            ↑第0个          ↑第1个              ↑第2个

比较规则：
1. 先比 enqueueTime（第0个）→ 小的前面
2. 如果 enqueueTime 相等 → 比 processingTime（第1个）
3. 再相等 → 比原始下标（第2个）
```

**形象理解：**
```
tuple 比较就像查字典
{1, 5, 3}  vs  {2, 1, 1}  →  1 < 2，所以 {1,5,3} 在前面
{3, 2, 0}  vs  {3, 5, 0}  →  3=3，然后 2 < 5，所以 {3,2,0} 在前面
```

---

## 问题6：pair 比较规则

**`pair` 也有字典序比较规则：先比 first，再比 second**

```cpp
priority_queue<
    pair<long long, int>,
    vector<pair<long long, int>>,
    greater<pair<long long, int>>
> pq;
```

**压入队列的任务：**
```cpp
pq.push({processingTime, 原始下标});
//             ↑first           ↑second
```

**堆内部如何排序？**
```
pair<A, B> 的比较规则：
1. 先比 A（processingTime）→ 小的优先级高
2. 如果 A 相等 → 比 B（原始下标）→ 小的优先级高

例子：
(2,0) vs (2,3)  →  2=2，0<3 → (2,0) 先出
(1,5) vs (2,0)  →  1<2 → (1,5) 先出
```

---

## 问题7：taskIdx 指针 vs 原始下标

**这是最容易混淆的点！让我画个图：**

```
┌─────────────────────────────────────────────────────────────┐
│  原始输入（按输入顺序）                                       │
│  ┌───────────────────────────────────────────────────────┐ │
│  │ 原始下标: 0    1    2    3                             │ │
│  │ enqueue:  1    2    3    4                             │ │
│  │ procTime: 2    4    2    1                             │ │
│  └───────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────┘
                         ↓
                         ↓ sort()
                         ↓
┌─────────────────────────────────────────────────────────────┐
│  排序后数组（tasks 数组）                                     │
│  ┌───────────────────────────────────────────────────────┐ │
│  │ taskIdx:  0    1    2    3    ← 这是数组的下标/指针     │ │
│  │ enqueue:  1    2    3    4    ← 排序后的顺序            │ │
│  │ procTime: 2    4    2    1                             │ │
│  │ 原始idx:  0    1    2    3    ← 记住原始任务编号        │ │
│  └───────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────┘
```

**关键区别：**
| 变量 | 含义 | 取值范围 |
|------|------|---------|
| `taskIdx` | **排序后数组**中的位置指针 | 0, 1, 2, ... 递增遍历 |
| `get<2>(tasks[taskIdx])` | **原始任务**的编号 | 0, 1, 2, ... (可能是乱序) |

**举个例子，如果入队时间打乱：**

```
原始输入：
下标0: enqueue=5, proc=10
下标1: enqueue=1, proc=20  
下标2: enqueue=3, proc=30

↓ sort() 按 enqueue 排序 ↓

排序后 tasks 数组：
位置0 → (enqueue=1, proc=20, 原始下标=1)  ← get<0>=1, get<1>=20, get<2>=1
位置1 → (enqueue=3, proc=30, 原始下标=2)  ← get<0>=3, get<1>=30, get<2>=2
位置2 → (enqueue=5, proc=10, 原始下标=0)  ← get<0>=5, get<1>=10, get<2>=0

此时：
taskIdx = 0 → get<2>(tasks[0]) = 1（原始下标是1！）
taskIdx = 2 → get<2>(tasks[2]) = 0（原始下标是0！）
```

---

## 问题8：get<0>(tasks[taskIdx]) 语法解释

**逐层拆解：**

```
get<0>(tasks[taskIdx])
        └────┬─────┘
            │
            └── tasks 是一个 vector<tuple>
                tasks[taskIdx] 是 tuple 中的第 taskIdx 个元素
                get<0>(...)   是取这个 tuple 的第0个成员
```

**代码对应：**
```cpp
// 定义
vector<tuple<long long, long long, int>> tasks;
//       ↑ tuple 包含 3 个元素: enqueue, proc, 原始下标

// 赋值
tasks[i] = {e, p, i};  
//           ↑0  ↑1  ↑2

// 访问
tasks[taskIdx]              // 取 vector 中第 taskIdx 个元素（一个 tuple）
get<0>(tasks[taskIdx])      // 取这个 tuple 的第0个元素 → enqueueTime
get<1>(tasks[taskIdx])      // 取这个 tuple 的第1个元素 → processingTime
get<2>(tasks[taskIdx])      // 取这个 tuple 的第2个元素 → 原始下标
```

---

## 问题9：双重 while 循环完整流程图解

**用 Sample #1 完整走一遍：**

```
初始状态：
currentTime = 0
taskIdx = 0      ← 指向排序后数组的第0个位置
pq = 空
result = []
```

```
┌─────────────────────────────────────────────────────────────────────┐
│  while(result.size() < 4)                                            │
├─────────────────────────────────────────────────────────────────────┤
│  【第1次外层循环】currentTime=0                                       │
│  ┌─────────────────────────────────────────────────────────────────┐│
│  │ 内层 while: taskIdx=0, tasks[0].enqueue=1                       ││
│  │ 1 <= 0 ?  不满足！循环不执行                                     ││
│  │ pq 为空 → 执行 if 分支                                           ││
│  │ currentTime = tasks[0].enqueue = 1                               ││
│  └─────────────────────────────────────────────────────────────────┘│
│                                                                     │
│  【第2次外层循环】currentTime=1                                       │
│  ┌─────────────────────────────────────────────────────────────────┐│
│  │ 内层 while: taskIdx=0, tasks[0].enqueue=1                       ││
│  │ 1 <= 1 ?  满足！执行循环体：                                     ││
│  │   pq.push({2, 0})    ← processingTime=2, 原始下标=0             ││
│  │   taskIdx++ → taskIdx=1                                         ││
│  │                                                                  ││
│  │ 继续内层: taskIdx=1, tasks[1].enqueue=2                         ││
│  │ 2 <= 1 ?  不满足！退出内层 while                                 ││
│  │                                                                  ││
│  │ pq 不为空 → 执行 else 分支                                       ││
│  │ 弹出 pq.top() = (2, 0)                                          ││
│  │ result.push_back(0)                                             ││
│  │ currentTime = 1 + 2 = 3                                         ││
│  └─────────────────────────────────────────────────────────────────┘│
│                                                                     │
│  【第3次外层循环】currentTime=3                                       │
│  ┌─────────────────────────────────────────────────────────────────┐│
│  │ 内层 while: taskIdx=1, tasks[1].enqueue=2                       ││
│  │ 2 <= 3 ?  满足！                                                 ││
│  │   pq.push({4, 1})    ← processingTime=4, 原始下标=1             ││
│  │   taskIdx=2                                                          ││
│  │                                                                  ││
│  │ 内层 while: taskIdx=2, tasks[2].enqueue=3                       ││
│  │ 3 <= 3 ?  满足！                                                 ││
│  │   pq.push({2, 2})    ← processingTime=2, 原始下标=2             ││
│  │   taskIdx=3                                                          ││
│  │                                                                  ││
│  │ 内层 while: taskIdx=3, tasks[3].enqueue=4                       ││
│  │ 4 <= 3 ?  不满足！退出                                           ││
│  │                                                                  ││
│  │ pq 不为空，弹出 (2,2)  ← processingTime 更小！                   ││
│  │ result.push_back(2)                                             ││
│  │ currentTime = 3 + 2 = 5                                         ││
│  └─────────────────────────────────────────────────────────────────┘│
│                                                                     │
│  【第4次外层循环】currentTime=5                                       │
│  ┌─────────────────────────────────────────────────────────────────┐│
│  │ 内层 while: taskIdx=3, tasks[3].enqueue=4                       ││
│  │ 4 <= 5 ?  满足！                                                 ││
│  │   pq.push({1, 3})    ← processingTime=1, 原始下标=3             ││
│  │   taskIdx=4  ← 已遍历完所有任务！                                ││
│  │                                                                  ││
│  │ pq 不为空，弹出 (1,3)  ← processingTime 最小！                   ││
│  │ result.push_back(3)                                             ││
│  │ currentTime = 5 + 1 = 6                                         ││
│  └─────────────────────────────────────────────────────────────────┘│
│                                                                     │
│  【第5次外层循环】currentTime=6                                       │
│  ┌─────────────────────────────────────────────────────────────────┐│
│  │ 内层 while: taskIdx=4, 4 < 4 不满足，循环不执行                  ││
│  │                                                                  ││
│  │ pq 不为空，弹出 (4,1)                                            ││
│  │ result.push_back(1)                                             ││
│  │ currentTime = 6 + 4 = 10                                        ││
│  └─────────────────────────────────────────────────────────────────┘│
│                                                                     │
│  result = [0, 2, 3, 1]  ✓ 完成！                                    │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 一句话总结 taskIdx 的作用

```
taskIdx = 排序后数组的"进度指针"
         告诉我"已经有多少个任务检查过了"
         避免重复检查已经加入堆的任务
```