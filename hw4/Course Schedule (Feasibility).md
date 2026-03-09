# Course Schedule (Feasibility)/课程表问题详解

---

## 📋 题目输入输出

### 输入
| 行 | 内容 |
|---|---|
| 第1行 | 两个整数 `n`（课程数）和 `m`（先修关系数）|
| 接下来m行 | 每行两个整数 `a b`，表示**必须先学b，才能学a** |

### 输出
- 能完成所有课程 → `YES`
- 不能（存在循环依赖）→ `NO`

---

## 🔍 样例分析

**样例1：** `2 1` + `1 0`
```
b=0 必须在 a=1 之前
图：0 ──→ 1   无环 → YES
```

**样例2：** `2 2` + `1 0` + `0 1`
```
0 必须在 1 之前，1 又必须在 0 之前
图：0 ──→ 1
    ↑      │
    └──────┘   有环 → NO
```

---

## 💡 知识点：拓扑排序（Kahn算法）

**核心思想：** 判断有向图中是否存在环
- **无环（DAG）** → 可以完成所有课程 → YES
- **有环** → 循环依赖，永远无法开始 → NO

---

## 🚀 解题思路（Kahn算法 / BFS拓扑排序）

```
步骤1：建立邻接表 + 计算每个节点的"入度"（有多少门课是它的先修课）
步骤2：将所有入度为0的节点（无需先修）放入队列
步骤3：每次从队列取出节点：
        - 计数 count++
        - 将它的后继课程入度 -1
        - 若某后继入度变为0，加入队列
步骤4：若 count == n，说明所有课都能学完 → YES
        否则还有课被"卡住"在环里 → NO
```

**图解过程（样例1）：**
```
初始入度：0号=0，1号=1
         ┌────┐
队列：   │ 0  │   
         └────┘
取出0 → count=1，1号入度变0 → 1号入队
取出1 → count=2，队列空
count(2) == n(2) → YES ✓
```

---

## 💻 C++ 代码

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adj(n);   // 邻接表：adj[b] 存 b 的后继课程
    vector<int> indegree(n, 0);   // 入度数组
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        // b -> a（先修b才能学a）
        adj[b].push_back(a);
        indegree[a]++;
    }
    
    // 将所有入度为0的课程入队
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    int count = 0; // 已能学完的课程数
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;
        
        // 学完node后，其后继课程入度-1
        for (int next : adj[node]) {
            indegree[next]--;
            if (indegree[next] == 0) {
                q.push(next); // 先修课全学完了，可以学了
            }
        }
    }
    
    cout << (count == n ? "YES" : "NO") << endl;
    
    return 0;
}
```

---

## 📊 复杂度分析

| 项目 | 复杂度 |
|---|---|
| 时间复杂度 | O(n + m)，每个节点和边各访问一次 |
| 空间复杂度 | O(n + m)，邻接表和入度数组 |

完全满足题目约束（n≤2×10⁵，m≤3×10⁵）✅

# 课程表Ⅱ

## 🔄 两题本质区别

| 对比项 | 上一题 | 这一题 |
|---|---|---|
| **问的是** | 能不能完成？| 按什么顺序完成？|
| **返回值** | YES / NO | 具体顺序数组 / [] |
| **算法核心** | 相同（拓扑排序）| 相同（拓扑排序）|
| **变的地方** | 只需判断 count==n | **还要记录出队顺序** |

> 你的感觉是对的！**算法框架完全一样**，只是在原来的基础上**多记录一个结果数组**

---

## 🔍 变化只有一处

**上一题代码的核心循环：**
```cpp
while (!q.empty()) {
    int node = q.front();
    q.pop();
    count++;          // ← 只是计数
    
    for (int next : adj[node]) {
        indegree[next]--;
        if (indegree[next] == 0) q.push(next);
    }
}
return count == n ? "YES" : "NO";
```

**这一题只需改两行：**
```cpp
vector<int> result;   // 🆕 多加一个结果数组

while (!q.empty()) {
    int node = q.front();
    q.pop();
    result.push_back(node);  // ← 把 count++ 换成记录节点
    
    for (int next : adj[node]) {
        indegree[next]--;
        if (indegree[next] == 0) q.push(next);
    }
}
// 有环时result.size() < n，返回空数组
return result.size() == n ? result : vector<int>{};
```

---

## 💻 完整C++代码

```cpp
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);
        
        // 建图：bi -> ai
        for (auto& p : prerequisites) {
            int a = p[0], b = p[1];
            adj[b].push_back(a);
            indegree[a]++;
        }
        
        // 入度为0的先入队
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) q.push(i);
        }
        
        vector<int> result;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            result.push_back(node);  // ⭐ 记录顺序
            
            for (int next : adj[node]) {
                indegree[next]--;
                if (indegree[next] == 0) q.push(next);
            }
        }
        
        // 有环则返回空数组
        return result.size() == numCourses ? result : vector<int>{};
    }
};
```

---

## 📊 图解示例2

```
输入：4门课，[[1,0],[2,0],[3,1],[3,2]]

建图：
0 ──→ 1 ──→ 3
└──→ 2 ──→ 3

入度：0:0  1:1  2:1  3:2

第1步：入度0的入队 → [0]
       取出0，result=[0]，1和2入度变0 → 队列[1,2]

第2步：取出1，result=[0,1]，3入度变1 → 队列[2]

第3步：取出2，result=[0,1,2]，3入度变0 → 队列[3]

第4步：取出3，result=[0,1,2,3]，队列空

result.size()==4==numCourses → 返回[0,1,2,3] ✓
```

---

## 💡 总结

```
上一题 = 拓扑排序 + 判断是否成功
这一题 = 拓扑排序 + 判断是否成功 + 记录路径
                               ↑
                        只加了这一步！
```

所以你的直觉完全正确，这就是同一道题的**输出形式变种**，算法思路零变化 ✅

# 课程表Ⅲ：不是图论问题！是贪心算法 🧠
> 大根堆 → 选多了就反悔，放弃之前选的时间最长的课
## 🍰 这道题像什么？

想象成**吃自助餐**：

```
courses = [duration, lastDay]
          ↓
[需要吃多久, 最晚几点前吃完]
```

你胃口有限，想吃尽可能多的菜，但每道菜有"用餐时间"和"截止时间"。

---

## 🎯 贪心策略

### 核心思路：
1. **按截止时间排序** —— 先吃截止时间早的（紧急的先处理）
2. **用大根堆记录已选课程** —— 如果选不下了，移除持续时间最长的课

### 为什么这样对？

```
举例：课程A[100, 200]，课程B[200, 1300]，课程C[1000, 1250]

按截止日期排序后：C → A → B
                  ↑ ↑
                1250  200  1300

遍历过程：
- 选C：总时间1000，时间<=1250 ✓
- 选A：总时间1100，时间<=1250 ✓  
- 选B：总时间1300，时间>1250 ✗
  → 移除最大的(1000)，总时间300 ✓
  → 尝试加B：总时间500 <= 1300 ✓

最终选A和B，2门课
```

---

## ✅ 正确解法

```cpp
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        // 1. 按截止日期排序
        sort(courses.begin(), courses.end(), 
             [](auto& a, auto& b) {
                 return a[1] < b[1];
             });
        
        // 2. 大根堆，存已选课程的持续时间
        priority_queue<int> pq;
        long long totalTime = 0;
        
        // 3. 遍历每门课
        for (auto& course : courses) {
            int duration = course[0];
            int lastDay = course[1];
            
            // 能加上就加
            if (totalTime + duration <= lastDay) {
                pq.push(duration);
                totalTime += duration;
            } 
            // 不能加，但堆顶持续时间更长，替换掉
            else if (!pq.empty() && pq.top() > duration) {
                totalTime -= pq.top();  // 移除最长的
                pq.pop();
                pq.push(duration);       // 加入当前的
                totalTime += duration;
            }
            // 否则跳过这门课
        }
        
        return pq.size();  // 堆里存的就是能上的课
    }
};
```

---

## 📊 过程图解

```
courses = [[100,200], [200,1300], [1000,1250], [2000,3200]]
按lastDay排序: [[100,200], [1000,1250], [200,1300], [2000,3200]]

遍历:
┌─────────────────────────────────────────────────┐
│ 课          总时间   lastDay   堆(持续时间)      │
├─────────────────────────────────────────────────┤
│ [100,200]   100      200      [100]    ✓加入   │
│ [1000,1250] 1100     1250     [100,1000] ✓加入 │
│ [200,1300]  1300>1250 不行!                       │
│             但1000>200，替换!                    │
│             总时间: 1100-1000+200=300             │
│             堆: [200]                            │
│ [2000,3200] 3200>1300 不行!                       │
│             堆顶200不大于2000，不替换            │
└─────────────────────────────────────────────────┘

最终堆大小 = 3 → [0,2,1,3] 这三门！
```

---

## 💡 总结

| 题型 | 方法 |
|---|---|
| 课程表 I/II（图有依赖） | BFS/DFS + 拓扑排序 |
| 课程安排 III（时间限制） | **贪心 + 大根堆** |

> 记住：**不是图！是贪心！** 🎯

# 这道题是「课程表 IV」📌

和前面的贪心完全不同！**这是一道图论题** 🎯

---

## 题目在问什么？

```
prerequisites = [[0,1], [1,2], [0,3]]  意思是：
   0 → 1 → 2     (0是1的先决条件, 1是2的先决条件)
   0 → 3         (0是3的先决条件)

queries = [[0,3], [0,2], [1,0]]
          [0,3] → 0是3的先决条件吗？ ✓ (0→3)
          [0,2] → 0是2的先决条件吗？ ✓ (0→1→2)
          [1,0] → 1是0的先决条件吗？ ✗ (没有1→0的路径)
```

**本质：判断有向图中，从节点 u 能否到达节点 v**

---

## 解题思路

```
┌─────────────────────────────────────────────┐
│ 两种经典方法：                               │
│                                             │
│ 方法1: 对每个query单独做BFS/DFS              │
│        → 简单，但query多时可能慢              │
│                                             │
│ 方法2: 预处理 + Tarjan求强连通分量            │
│        → 缩点成DAG，在DAG上做可达性           │
└─────────────────────────────────────────────┘
```

---

## 方法1：逐个查询 BFS/DFS（面试常用）

```cpp
class Solution {
public:
    vector<bool> checkPrerequisite(int numCourses, 
                                    vector<vector<int>>& prerequisites,
                                    vector<vector<int>>& queries) {
        // 1. 建图 (邻接表)
        vector<vector<int>> graph(numCourses);
        for (auto& pre : prerequisites) {
            graph[pre[0]].push_back(pre[1]);  // 0 → 1
        }
        
        vector<bool> answer;
        
        // 2. 对每个query单独BFS
        for (auto& query : queries) {
            int u = query[0], v = query[1];
            answer.push_back(bfs(graph, u, v, numCourses));
        }
        
        return answer;
    }
    
    bool bfs(vector<vector<int>>& graph, int start, int target, int n) {
        vector<int> visited(n, 0);
        queue<int> q;
        q.push(start);
        visited[start] = 1;
        
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            
            if (cur == target) return true;
            
            for (int next : graph[cur]) {
                if (!visited[next]) {
                    visited[next] = 1;
                    q.push(next);
                }
            }
        }
        return false;
    }
};
```

---

## 方法2：预处理 + bitset（高效）

```cpp
class Solution {
public:
    vector<bool> checkPrerequisite(int numCourses, 
                                    vector<vector<int>>& prerequisites,
                                    vector<vector<int>>& queries) {
        // 1. 建图 + 计算所有节点的可达性
        vector<vector<int>> graph(numCourses);
        vector<bitset<100>> reach(numCourses);  // reach[i][j] = i能否到j
        
        for (auto& pre : prerequisites) {
            graph[pre[0]].push_back(pre[1]);
            reach[pre[0]].set(pre[1]);
        }
        
        // 2. Floyd-Warshall思想（优化版）
        // 对每个节点做DFS，把可达信息合并
        for (int i = 0; i < numCourses; i++) {
            dfs(i, i, graph, reach);
        }
        
        // 3. 直接查表回答query
        vector<bool> answer;
        for (auto& q : queries) {
            answer.push_back(reach[q[0]].test(q[1]));
        }
        return answer;
    }
    
    void dfs(int start, int node, 
             vector<vector<int>>& graph,
             vector<bitset<100>>& reach) {
        for (int next : graph[node]) {
            if (!reach[start].test(next)) {
                reach[start].set(next);
                dfs(start, next, graph, reach);
            }
        }
    }
};
```

---

## 三道课程表对比

| 题号 | 题目 | 方法 |
|------|------|------|
| 课程表 I | 判断是否有环 | **拓扑排序** / DFS检测环 |
| 课程表 II | 返回上课顺序 | **拓扑排序** + 记录顺序 |
| 课程表 III | 最多能上几门课 | **贪心 + 大根堆** ✅ |
| 课程表 IV | 判断先决条件 | **DFS/BFS可达性** ✅ |

---

## 一句话总结

> 这道题**不是贪心**，是**有向图可达性**问题！
> 
> 问 u 是不是 v 的先决条件 → 从 u 出发能否走到 v → BFS/DFS 即可 🎯