## 结论
这道题的核心是**离散化差分统计**。
**简单概括**：题目要求统计在数轴上，被恰好 $k$ 条线段覆盖的整数点个数；其本质是处理海量坐标范围下的区间覆盖次数统计问题。

---

## 💡 题目含义与输入输出

### 1. 题目含义
在 $10^{18}$ 长度的数轴上放 $n$ 条线段。由于坐标范围极大，无法开数组记录每个点，必须通过线段的**起点和终点**来计算覆盖变化。你需要求出覆盖层数为 $1, 2, \dots, n$ 的整数点分别有多少个。

### 2. 输入输出
*   **输入**：第一行 $n$，随后 $n$ 行每行两个整数 $[l_i, r_i]$ 表示闭区间。
*   **输出**：$n$ 个整数，第 $i$ 个数表示被覆盖了 $i$ 次的点总数。

---

## 🛠️ 逻辑分析：为什么这样做？

### 核心原理：差分 (Difference Array) + 坐标压缩思想
由于坐标范围是 $0$ 到 $10^{18}$，我们不能像常规差分那样开数组。但覆盖次数只在**端点处**发生改变。

1.  **事件转化**：
    *   每条线段 $[l_i, r_i]$ 对点的覆盖产生影响。
    *   在 $l_i$ 处，覆盖次数 $+1$。
    *   在 $r_i + 1$ 处，覆盖次数 $-1$（因为 $r_i$ 还是被覆盖的，从 $r_i + 1$ 开始覆盖数才减少）。
2.  **排序**：
    *   将所有的 $l_i$ 和 $r_i + 1$ 存入一个数组并排序。
3.  **区间计算**：
    *   排序后的相邻两个坐标 $x_j$ 和 $x_{j+1}$ 之间，所有整数点的覆盖次数是**恒定**的。
    *   这两个点之间的整数点个数为 $x_{j+1} - x_j$。
    *   通过累加当前的 `count`（覆盖层数），将这段长度累加到对应的 `ans[count]` 中。

---

## 🚀 C++ 代码实现 (最简 ACM 模式)

这是逻辑最清晰、代码量最小且能通过 $2 \cdot 10^5$ 数据量的实现方式。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    // 1. 优化输入输出
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // 2. 存储事件：坐标和增量
    // 使用 pair<坐标, 增量>，long long 处理 10^18
    vector<pair<ll, int>> events;
    for (int i = 0; i < n; ++i) {
        ll l, r;
        cin >> l >> r;
        events.push_back({l, 1});     // 起点覆盖记录增加
        events.push_back({r + 1, -1}); // 终点的下一个点覆盖记录减少
    }

    // 3. 按坐标排序
    sort(events.begin(), events.end());

    vector<ll> ans(n + 1, 0); // 存储结果 ans[k]
    ll current_coverage = 0;

    // 4. 扫描线处理
    for (int i = 0; i < events.size() - 1; ++i) {
        current_coverage += events[i].second;
        // 计算当前坐标到下一个变化坐标之间的跨度
        ll length = events[i + 1].first - events[i].first;
        if (current_coverage > 0) {
            ans[current_coverage] += length;
        }
    }

    // 5. 输出
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << endl;

    return 0;
}
```

---

## 📝 关键细节说明

*   **$r+1$ 的逻辑**：题目是闭区间。如果线段是 `[1, 3]`，点 1, 2, 3 都被覆盖。我们的差分标记在 1 处 `+1`，在 4 处 `-1`。这样 `4-1=3` 正好是三个点。
*   **坐标重合处理**：`sort` 默认会对 `pair` 的第一个元素排序。如果坐标相同，`events[i+1].first - events[i].first` 会等于 0，虽然执行了 `ans[cnt] += 0`，但并不影响最终统计结果，因此不需要特殊去重，逻辑极其简洁。
*   **复杂度分析**：
    *   **时间**：$O(N \log N)$，主要耗时在排序。
    *   **空间**：$O(N)$，存储 $2N$ 个端点。
    *   对于 $N=2 \times 10^5$ 的约束，此算法在 200ms 内即可完成，远低于通常 1s-2s 的时限。