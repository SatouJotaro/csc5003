# Longest Cycle in a Graph/图中的最长环 hard
### 题目理解
这道题要求在给定的有向图中找到最长的有向循环的长度。图有 `n` 个节点，节点编号从 0 到 `n-1`，每个节点最多有一条出边。输入是一个数组 `edges`，其中 `edges[i] = v` 表示有一条从节点 `i` 到节点 `v` 的边，如果 `edges[i] = -1`，则节点 `i` 没有出边。如果图中存在循环，返回最长循环的长度；否则返回 -1。

**输入格式**：
- 第一行：一个整数 `n`（节点数量，2 ≤ n ≤ 10^5）。
- 第二行：`n` 个整数 `edges[0..n-1]`，用空格分隔。

**输出格式**：
- 一个整数：最长循环的长度，如果无循环则输出 -1。

**约束**：
- `-1 ≤ edges[i] < n` 且 `edges[i] != i`。

**示例**：
- 输入 #1：`5` 和 `3 3 4 2 3`，输出 `3`。
- 输入 #2：`4` 和 `2 -1 3 1`，输出 `-1`。

### 知识点
这道题涉及图论中的循环检测和长度计算。具体知识点包括：
- **有向图**：节点之间有方向性的边。
- **循环检测**：在图中检测是否存在从某节点出发能回到自身的路径。
- **深度优先搜索（DFS）或迭代遍历**：由于每个节点最多一条出边，图的结构类似于链表或树，因此可以使用线性遍历来检测循环。
- **时间戳技术**：通过记录节点访问的时间戳来高效检测循环，避免重复访问。

### 解题思路
由于每个节点最多有一条出边，图的结构由一些链（无循环的路径）和循环组成。关键思路是遍历每个未访问的节点，沿着出边链式前进，同时记录每个节点的访问时间戳。如果遇到一个已经访问过的节点，需要判断该节点是否在当前遍历的路径中（即是否在当前时间戳范围内）。如果是，则计算循环长度；否则，继续遍历。

**算法步骤**：
1. 初始化两个数组：
   - `visited`：标记节点是否已访问，初始值为 `false`。
   - `visit_time`：记录节点第一次访问的时间戳，初始值为 `0`。
2. 维护一个全局变量 `current_time`，初始值为 `1`，用于生成时间戳。
3. 遍历每个节点 `i`：
   - 如果 `visited[i]` 为 `true`，跳过该节点。
   - 否则，从 `i` 开始遍历，记录当前遍历的起始时间 `start_time = current_time`。
   - 沿着出边链式前进：
     - 对于当前节点 `node`，如果 `node` 为 `-1` 或已访问，则停止遍历。
     - 否则，标记 `visited[node] = true`，设置 `visit_time[node] = current_time`，然后 `current_time++`。
     - 移动到下一个节点 `node = edges[node]`。
   - 遍历结束后，如果 `node != -1`（即遇到了已访问的节点），检查 `visit_time[node] >= start_time`。如果为真，说明节点 `node` 在当前遍历路径中，计算循环长度 `cycle_len = current_time - visit_time[node]`，并更新最大循环长度。
4. 返回最大循环长度，如果无循环则保持为 `-1`。

**正确性证明**：
- 每个节点只访问一次，因此时间复杂度为 O(n)。
- 时间戳机制确保了只检测当前遍历路径中的循环：当遇到已访问节点时，只有当该节点的时间戳不小于起始时间时，才表示它在当前路径中。
- 循环长度计算基于时间戳差值：当前时间戳 `current_time` 减去节点 `node` 的时间戳 `visit_time[node]` 即为循环长度。

### C++ 代码实现
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> edges(n);
    for (int i = 0; i < n; i++) {
        cin >> edges[i];
    }
    
    vector<bool> visited(n, false);
    vector<int> visit_time(n, 0);
    int current_time = 1;
    int max_cycle = -1;
    
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        int start_time = current_time;
        int node = i;
        while (node != -1 && !visited[node]) {
            visited[node] = true;
            visit_time[node] = current_time;
            current_time++;
            node = edges[node];
        }
        if (node != -1) {
            if (visit_time[node] >= start_time) {
                int cycle_len = current_time - visit_time[node];
                if (cycle_len > max_cycle) {
                    max_cycle = cycle_len;
                }
            }
        }
    }
    
    cout << max_cycle << endl;
    return 0;
}
```

### 代码解释
- **输入读取**：读取 `n` 和 `edges` 数组。
- **初始化**：`visited` 数组标记节点是否已访问，`visit_time` 数组记录时间戳，`current_time` 初始为 1，`max_cycle` 初始为 -1。
- **遍历节点**：对于每个未访问节点，记录起始时间，然后沿着出边链式前进，标记访问并更新时间戳。
- **循环检测**：遇到已访问节点时，检查其时间戳是否在当前遍历范围内，如果是，则计算循环长度并更新最大值。
- **输出结果**：打印最大循环长度，无循环时输出 -1。

该算法高效且正确，时间复杂度为 O(n)，空间复杂度为 O(n)，适用于大规模图。