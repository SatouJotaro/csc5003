**一、题目回顾**

- 有 `n` 条公交线路，线路 `i` 是一条由 **互不相同的站点** 组成的循环列表。  
- 你可以在任意站点上车，坐完后可以在该线路的任意站点下车，然后换乘另一条线路。  
- 给定起点站 `source` 与终点站 `target`，要求 **最少需要乘坐多少条线路**（即乘坐多少辆车）才能从 `source` 到达 `target`。  
- 若 `source == target`，答案为 `0`。  
- 若无法到达，输出 `-1`。

**输入格式**

```
n                     // 线路数
k1  s11 s12 … s1k1    // 第 1 条线路的站点数以及站点编号
k2  s21 s22 … s2k2    // 第 2 条线路 …
…
kn  sn1 sn2 … snkn    // 第 n 条线路
source target        // 起点、终点
```

- `1 ≤ n ≤ 2000`  
- `∑ ki ≤ 2·10⁵`（所有线路站点总数）  
- 站点编号范围 `0 … 10⁶`

**输出格式**

```
一个整数  // 最少乘坐的线路数，-1 表示不可达
```

---

**二、涉及的知识**

| 知识要点 | 说明 |
|----------|------|
| **图的建模** | 把每条线路看作一个“节点”，把两条线路的**公共站点**看作它们之间的**边**，构成 **线路图**。 |
| **BFS（广度优先搜索）** | 在无权图中求最短路径（最少边数）——这里每条边等价于一次换乘。 |
| **二部图 / 站点‑线路映射** | 同一个站点可能出现在多条线路中，直接构建线路间的完全图会导致 `O(n²)` 边。通过“站点 → 经过该站点的线路列表”的映射，可以**按站点遍历**邻接线路，复杂度只和站点总数线性相关。 |
| **visited 标记** | 为了防止在 BFS 中对同一站点多次展开，使用 `visited_stop`；同理使用 `visited_route` 防止线路被重复入队。 |
| **多源 BFS** | 所有包含起点 `source` 的线路都可以作为 **第一辆车**，于是把它们的距离设为 `1` 同时入队。 |

---

**三、解题思路（逐步拆解）**

> 核心思想：**把“坐车”看成在“线路节点”之间的转移**，求从“起点所在的线路集合”到“终点所在的线路集合”的最短路径（最少换乘次数 + 1）。

1. **读取输入，保存每条线路的站点列表**  
   `routes[i]` 为第 `i` 条线路的所有站点（`i` 从 `0` 开始）。

2. **建立 “站点 → 经过该站点的线路列表” 的映射**  
   用 `unordered_map<int, vector<int>> stop2routes;`  
   对每条线路的每个站点 `s`，把当前线路编号 `i` 加入 `stop2routes[s]`。

3. **预处理哪些线路直接经过终点 `target`**  
   `vector<char> routeHasTarget(n, 0);`  
   在遍历 `routes[i]` 时，若出现 `target`，把 `routeHasTarget[i]=1`。

4. **特殊情况**  
   - `source == target` → 直接输出 `0`。  
   - `source` 没有出现在任何线路中 → 绝对不可达，输出 `-1`（除非 `source==target` 已处理）。

5. **BFS（多源）**  
   - `queue<pair<int,int>> q;` 保存 `(线路编号, 已经乘坐的车辆数)`。  
   - 把所有包含 `source` 的线路 `r` 入队，距离设为 **1**（表示已经坐了第一辆车），并标记 `visited_route[r]=1`。  
   - 当队首弹出 `(r, dist)` 时：  
        - 若 `routeHasTarget[r]==1`，说明在该线路的某个站点可以直接下车到达 `target`，答案就是 `dist`（因为已经坐了 `dist` 辆车），结束 BFS。  
        - 否则遍历 `routes[r]` 中的每个站点 `s`：  
            - 若该站点已经被 `visited_stop[s]` 访问过，跳过（防止重复展开）。  
            - 否则标记 `visited_stop[s]=1`，并遍历 `stop2routes[s]` 中出现的所有线路 `nr`：  
                - 若 `nr` 还未被 `visited_route[nr]` 访问，则标记并把 `(nr, dist+1)` 入队（换乘一次）。  

6. **结束**  
   - 若 BFS 正常结束仍未遇到 `target`，说明不可达，输出 `-1`。

> **为什么 BFS 能得到最少车辆数？**  
> 把每条线路看成无权图的一个节点，节点之间的边只表示“可以换乘”。BFS 在无权图中保证第一次到达终点的路径是最短的（最少边数）。这里的“边数”正好等于 **换乘次数 + 1**（因为第一条线路已经坐上车），所以返回的 `dist` 正是最少车辆数。

---

**四、正确性证明（简要）**

*定义*  
- `R_i` 为第 `i` 条线路。  
- `S(s)` 为所有经过站点 `s` 的线路集合。  
- 目标：从任意 `R_a ∈ S(source)` 到达任意 `R_b ∈ S(target)` 的最短路径。

*引理 1*（线路图是合法的转移模型）  
若在 `R_i` 上乘坐并在站点 `x` 下车，则可以直接换乘到 `R_j ∈ S(x)`。这正好对应图中从节点 `i` 到节点 `j` 的一条无向边。  

*引理 2*（每条边对应一次换乘）  
在 `R_i` 与 `R_j` 之间出现公共站点时，两条线路在模型中相邻，且从 `R_i` 到达 `R_j` 必须换乘一次（再坐一辆车）。  

*引理 3*（BFS 的距离对应车辆数）  
把每条线路节点的距离初始化为 `1`（表示已经坐了第一辆车），每次通过一条边到达新节点时距离加 `1`。因此任意路径的长度（边数）等于 **换乘次数 + 1** = 乘坐的车辆数。  

*定理*（算法返回的值是最少车辆数）  
BFS 在无权图中第一次访问到任意 `R_b ∈ S(target)` 时得到的距离 `d` 为所有从 `S(source)` 到 `S(target)` 路径中最小的边数。依据引理 3，`d` 正好等于所需的最少车辆数。若不存在这样的一条路径，则 BFS 结束而未访问到 `target`，算法输出 `-1`，符合题意。∎

---

**五、复杂度分析**

| 步骤 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| 读取数据 & 建立映射 | `O(∑ki)`（≤ 2·10⁵） | `O(∑ki)`（存放站点列表 + 映射） |
| BFS（每条站点只展开一次） | `O(∑ki + ∑_{s} |S(s)|)` = `O(∑ki)`（因为每条记录只遍历一次） | `O(n + maxStop)`（`visited_route`、`visited_stop`） |
| 总体 | **`O(∑ki)`**（线性） | **`O(∑ki + n + maxStop)` ≤ `O(2·10⁵ + 2·10³ + 10⁶)` ≈ `1 MB` 级别** |

在题目给定的约束下完全安全。

---

**六、参考实现（C++17）**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;               // 防止空输入

    // 1. 读取线路站点列表
    vector<vector<int>> routes(n);
    unordered_map<int, vector<int>> stop2routes;
    stop2routes.reserve(200000);
    int maxStop = 0;

    for (int i = 0; i < n; ++i) {
        int k;  cin >> k;
        routes[i].reserve(k);
        for (int j = 0; j < k; ++j) {
            int stop; cin >> stop;
            routes[i].push_back(stop);
            stop2routes[stop].push_back(i);
            if (stop > maxStop) maxStop = stop;
        }
    }

    int source, target;
    cin >> source >> target;

    // 特殊情况：起点即终点
    if (source == target) {
        cout << 0 << "\n";
        return 0;
    }

    // 检查 source 是否出现过
    if (stop2routes.find(source) == stop2routes.end()) {
        cout << -1 << "\n";
        return 0;
    }

    // 2. 预处理哪些线路经过 target
    vector<char> routeHasTarget(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int s : routes[i]) {
            if (s == target) {
                routeHasTarget[i] = 1;
                break; // 只需要一次标记
            }
        }
    }

    // 3. BFS（多源）
    vector<char> visited_route(n, 0);
    vector<char> visited_stop(maxStop + 1, 0);   // maxStop ≤ 1e6，安全

    queue<pair<int,int>> q; // (routeIdx, distance = busCount)

    // 初始：所有包含 source 的线路，距离设为 1（已经坐了第一辆车）
    for (int r : stop2routes[source]) {
        visited_route[r] = 1;
        q.emplace(r, 1);
    }

    int answer = -1;
    while (!q.empty()) {
        auto [r, dist] = q.front(); q.pop();

        // 如果该线路已经经过 target，直接返回
        if (routeHasTarget[r]) {
            answer = dist;
            break;
        }

        // 展开该线路的每个站点，尝试换乘到其他线路
        for (int s : routes[r]) {
            if (visited_stop[s]) continue;   // 已经从该站点展开过
            visited_stop[s] = 1;

            for (int nr : stop2routes[s]) {
                if (!visited_route[nr]) {
                    visited_route[nr] = 1;
                    q.emplace(nr, dist + 1);
                }
            }
        }
    }

    cout << answer << "\n";
    return 0;
}
```

**代码要点解释**

| 代码位置 | 说明 |
|----------|------|
| `stop2routes.reserve(200000);` | 为 unordered_map 预留足够空间，避免频繁 rehash。 |
| `vector<char> visited_stop(maxStop + 1, 0);` | 使用 `char`（1 byte）保存 “已访问站点”。`maxStop ≤ 10⁶`，占约 1 MB。 |
| `queue<pair<int,int>> q;` | BFS 队列保存 `(线路编号, 已乘坐车辆数)`。 |
| `if (routeHasTarget[r]) { answer = dist; break; }` | 第一次遇到终点所在的线路时即得到最优解，BFS 保证此距离最小。 |
| `if (visited_stop[s]) continue;` | 每条站点只展开一次，整体复杂度线性。 |

---

**七、总结**

- 本题把 “最少乘坐车辆数” 转化为 **在线路节点图上求最短路径**。  
- 关键在于 **通过“站点 → 经过的线路”映射** 避免 `O(n²)` 的邻接矩阵，使得整体时间线性于站点总数。  
- 使用 **多源 BFS** 并在展开站点时加入 `visited_stop` 标记，实现对每条站点只遍历一次，从而在约束范围内轻松通过。  

希望上述解析能帮助你彻底弄清题目含义、思路以及代码实现。祝你编程顺利 🚍！