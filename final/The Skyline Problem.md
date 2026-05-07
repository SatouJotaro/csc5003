## 一、结论：题目概括

**含义概括**：给定若干重叠矩形（建筑物），求它们合并后的外轮廓（天际线），即由所有高度发生变化的转折点 $(x, y)$ 按顺序构成的序列。

**输入输出**：
- **输入**：建筑数量 $n$ 及每个建筑的左边界、右边界、高度。
- **输出**：轮廓转折点的总数 $m$，以及每个转折点的坐标 $(x, y)$。

---

## 二、逻辑拆解：扫描线法 (Sweep Line)

这道题是经典的“天际线问题”。由于 $x$ 坐标范围极大（高达 $2^{31}-1$），不能使用数组模拟。最简单且高效的方法是**扫描线法**搭配**有序集合（优先队列）**，复杂度为 $O(n \log n)$。

### 1. 核心原理
想象一根垂直线从左向右扫描：
- 碰到建筑的**左边界**，意味着有一个高度加入。
- 碰到建筑的**右边界**，意味着有一个高度离开。
- 在任何位置，天际线的高度取决于**当前活跃建筑中的最高高度**。
- 只有当“当前最高高度”发生变化时，才会产生一个新的轮廓转折点。

### 2. 技巧：如何处理边界重合？
为了简化逻辑并一次性排好序，我们将每个建筑拆成两个事件：
1.  **左边界**：记为 `(left, -height)`（高度存为负数）。
2.  **右边界**：记为 `(right, height)`（高度存为正数）。

**为什么要用负数区分？**
通过对事件按 $x$ 坐标升序排序，如果 $x$ 相同，则：
- 两个左边界：高度绝对值大的优先处理（负数更小，排在前面），避免中间产生低点的冗余记录。
- 两个右边界：高度绝对值小的优先处理，确保平滑过渡。
- 一左一右：左边界（负数）排在右边界（正数）前面，处理重合建筑时不会错断。

---

## 三、C++ 代码实现 (ACM 模式)

这是逻辑最清晰、代码量最小的实现方式。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // 1. 存储事件：first为x坐标，second为高度（左边界存负，右边界存正）
    vector<pair<ll, ll>> events;
    for (int i = 0; i < n; ++i) {
        ll l, r, h;
        cin >> l >> r >> h;
        events.push_back({l, -h});
        events.push_back({r, h});
    }

    // 2. 按x坐标排序，x相同时按高度存的负/正值排序
    sort(events.begin(), events.end());

    // 3. 扫描线处理
    multiset<ll> heights = {0}; // 存放当前扫描线覆盖的所有高度，初始有地平线0
    vector<pair<ll, ll>> res;
    ll curMax = 0;

    for (auto& e : events) {
        ll x = e.first;
        ll h = e.second;

        if (h < 0) {
            heights.insert(-h); // 左边界，存入高度
        } else {
            heights.erase(heights.find(h)); // 右边界，移除一个对应高度
        }

        ll nowMax = *heights.rbegin(); // 获取当前最大高度
        if (nowMax != curMax) {       // 高度发生变化，记录关键点
            res.push_back({x, nowMax});
            curMax = nowMax;
        }
    }

    // 4. 按要求输出
    cout << res.size() << "\n";
    for (auto& p : res) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}
```

---

## 四、关键点补充

### 1. 为什么使用 `multiset`？
- `multiset` 内部自动排序，可以在 $O(\log n)$ 内插入和删除。
- `*heights.rbegin()` 可以直接获取当前集合中的最大值。
- 使用 `heights.erase(heights.find(h))` 而不是 `heights.erase(h)`：
    > **警示**：`heights.erase(h)` 会删掉所有等于 $h$ 的值，而 `heights.find(h)` 只获取其中一个的迭代器，从而只删掉一个对应的高度。

### 2. 复杂度分析
- **时间复杂度**：$O(n \log n)$。主要是排序和 $2n$ 次 `multiset` 操作。
- **空间复杂度**：$O(n)$。用于存储事件和高度集合。

<details>
<summary>💭 <strong>详细推导：为什么左边界用负数？</strong>（点击展开）</summary>

假设两个建筑在 $x=5$ 处重叠：
- A: (2, 5, 10)
- B: (5, 8, 15)

如果我们先处理 B 的进入（负数 -15 较小，排在前面），扫描线的高度会直接从 10 升到 15，只产生一个转折点。
如果先处理 A 的离开（正数 10 排在后面），高度会先降到 0 再升到 15，产生错误的冗余点。
利用 `(x, 负高度)` 排序技巧，可以完美规避 $x$ 轴相同位置时的各种逻辑判断。
</details>