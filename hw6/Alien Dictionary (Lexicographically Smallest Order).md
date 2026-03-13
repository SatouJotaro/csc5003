这道题是经典的 **“外星人字典”（Alien Dictionary）** 问题，它是图论中 **拓扑排序（Topological Sort）** 的变种。

下面我将分维度为你详细讲解。

---

### 1. 题目输入输出理解
*   **输入**：
    *   第一行是一个整数 $k$，代表单词的数量。
    *   接下来的 $k$ 行，每一行是一个由小写字母组成的字符串。这些单词已经按照“外星语”的字典序排好了。
*   **输出**：
    *   输出一个字符串，即推导出的“外星语”字母表顺序（包含所有出现的字母）。
    *   如果逻辑上不存在这样的顺序（例如出现了环，如 a < b 且 b < a），则输出空字符串。
    *   如果存在多种合法的顺序，题目要求选取**字典序最小**的那一个（即按 'a', 'b', 'c'... 的顺序优先排列字母）。

---

### 2. 核心知识点
1.  **拓扑排序 (Topological Sort)**：处理有向无环图（DAG）的节点排序问题。
2.  **Kahn 算法**：利用入度（In-degree）进行拓扑排序的常用方法。
3.  **优先队列（Priority Queue）**：本题要求“输出字典序最小的顺序”，因此在处理拓扑排序时，不能使用普通的队列，而要使用**最小堆（Min-Heap）**。
4.  **字符串比较逻辑**：如何从两个相邻单词找出隐藏的字母先后关系。

---

### 3. 解题思路分析

#### 第一步：构建图
我们要把字符看作图的节点，字符之间的先后关系看作有向边。
遍历输入的单词数组，比较相邻的 `words[i]` 和 `words[i+1]`：
*   找到第一个不相等的字符 `words[i][j]` 和 `words[i+1][j]`。
*   这就意味着在“外星语”中，`words[i][j]` 必须在 `words[i+1][j]` 前面，即建立一条有向边：`words[i][j] -> words[i+1][j]`。
*   **注意特例**：如果 `words[i+1]` 是 `words[i]` 的前缀，但 `words[i+1]` 更短（如 "abc", "ab"），这是违法的，直接返回空字符串。

#### 第二步：初始化入度
统计所有出现过的字符，并计算它们对应的入度。如果 `A -> B`，则 `B` 的入度 `+1`。

#### 第三步：拓扑排序（最小字典序版）
1.  将所有入度为 0 的字符放入一个**最小优先队列（min-heap）**中。
2.  循环取出队头字符（这保证了优先选出字母表中小的字符）：
    *   将其加入结果字符串。
    *   遍历该字符指向的所有邻居，将邻居入度 `-1`。
    *   如果邻居入度变回 0，将其加入优先队列。
3.  **判断是否有环**：如果最终生成的字符串长度不等于所有出现过的字符总数，说明图中存在环，返回空字符串。

---

### 4. C++ 实现方案

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

string findOrder(int k, vector<string>& words) {
    unordered_map<char, int> in_degree;
    unordered_map<char, unordered_set<char>> adj;
    
    // 初始化：确保所有出现的字符都在表中
    for (const string& w : words) {
        for (char c : w) in_degree[c] = 0;
    }

    // 建立图
    for (int i = 0; i < k - 1; ++i) {
        string w1 = words[i], w2 = words[i+1];
        int len = min(w1.size(), w2.size());
        bool found = false;
        for (int j = 0; j < len; ++j) {
            if (w1[j] != w2[j]) {
                if (adj[w1[j]].find(w2[j]) == adj[w1[j]].end()) {
                    adj[w1[j]].insert(w2[j]);
                    in_degree[w2[j]]++;
                }
                found = true;
                break;
            }
        }
        // 特殊情况：如果是前缀关系但顺序反了
        if (!found && w1.size() > w2.size()) return "";
    }

    // 优先队列保证最小值优先
    priority_queue<char, vector<char>, greater<char>> pq;
    for (auto const& [node, deg] : in_degree) {
        if (deg == 0) pq.push(node);
    }

    string res = "";
    while (!pq.empty()) {
        char u = pq.top(); pq.pop();
        res += u;
        for (char v : adj[u]) {
            if (--in_degree[v] == 0) pq.push(v);
        }
    }

    // 若 res 长度不等于总字符数，说明存在环
    return res.size() == in_degree.size() ? res : "";
}

int main() {
    int k;
    cin >> k;
    vector<string> words(k);
    for (int i = 0; i < k; ++i) cin >> words[i];
    
    cout << findOrder(k, words) << endl;
    return 0;
}
```

### 总结
这道题的核心在于将“字典序规则”理解为“图的约束边”。使用**Kahn算法**实现拓扑排序时，引入**优先队列**是实现“字典序最小且最优”的关键技巧。你需要重点掌握的就是如何构建这个邻接表（Edge）以及如何判断是否存在环（入度检查）。