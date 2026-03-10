# Merge K Sorted Lists/合并 K 个升序链表 hard
> 最小堆/优先队列

## 1. 题目背景与目标
我们要将 $K$ 个有序列表合并为一个新的有序列表。
*   **挑战点**：K 个列表各自有序，但合在一起是一个巨大的乱序集合。如果暴力排序，我们需要 $O(N \log N)$ 的时间。
*   **优化目标**：利用“每个列表内部有序”这一特性，通过使用**最小堆**（Min-Heap），将时间复杂度降至 $O(N \log K)$。

---

## 2. 核心算法思想：最小堆 (Min-Heap)

想象一种手动合并方式：
1.  你有 $K$ 个列表，每个列表都取出一个数放在桌上。
2.  你要在这 $K$ 个数里选出**最小的那个**，放入结果列表。
3.  一旦那个数被拿走，立刻从该数原本所在的列表中补充一个新的数到桌上。
4.  桌面始终保持 $K$ 个数，重复上述步骤，直到所有列表耗尽。

**为什么是最小堆？**
“在桌上 $K$ 个数中快速寻找最小值” —— 这正是**最小堆**最擅长的操作。
*   `top()` 获取最小值：$O(1)$
*   `pop()` 弹出最小值：$O(\log K)$
*   `push()` 插入新元素：$O(\log K)$

---

## 3. 设计实现：如何存储“位置信息”？

在数组合并中，单纯存数值是不够的，我们还需要知道：
1.  **这个值来自哪个列表？** (通过 `list_idx` 记录)
2.  **这个值是该列表的第几个元素？** (通过 `element_idx` 记录，以便快速找到下一个)

我们将这些封装在一个结构体 `Element` 中。

### 结构体定义
```cpp
struct Element {
    int value;         // 具体数值
    int list_idx;      // 所属列表的下标（第几个列表）
    int element_idx;   // 在该列表中的数组下标

    // 关键点：重载 > 运算符，配合 std::greater 实现最小堆
    // 当 a.value > b.value 为真时，a 的优先级低于 b（即 a 排在堆底层，b 排在堆顶）
    bool operator>(const Element& other) const {
        return value > other.value;
    }
};
```

---

## 4. 完整代码方案

这段代码针对你提供的 **Format** 进行编写，具备高效率 I/O 和标准实现规范。

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 1. 定义数据结构
struct Element {
    int value;
    int list_idx;
    int element_idx;

    // 为了使用 std::greater 创建最小堆，必须重载 > 运算符
    bool operator>(const Element& other) const {
        return value > other.value;
    }
};

int main() {
    // 性能优化：关闭流同步，在大数据量下输入输出更快
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k;
    if (!(cin >> k)) return 0;

    // 存储所有的列表
    vector<vector<int>> lists(k);
    
    // 初始化最小堆 (传入 greater 自定义比较规则)
    priority_queue<Element, vector<Element>, greater<Element>> min_heap;

    int total_elements = 0;

    // 2. 数据读取与入堆初始化
    for (int i = 0; i < k; ++i) {
        int len;
        cin >> len;
        total_elements += len;
        lists[i].resize(len);
        for (int j = 0; j < len; ++j) {
            cin >> lists[i][j];
        }
        // 如果列表不为空，把该列表的第 0 号元素放入堆中
        if (len > 0) {
            min_heap.push({lists[i][0], i, 0});
        }
    }

    // 3. 结果合并与处理
    cout << total_elements << endl;
    
    bool first = true;
    while (!min_heap.empty()) {
        // 取出堆顶（即当前所有列表中的最小值）
        Element top = min_heap.top();
        min_heap.pop();

        // 输出数值
        if (!first) cout << " ";
        cout << top.value;
        first = false;

        // 核心：若该元素所在的列表还有后续元素，将其压入堆中
        if (top.element_idx + 1 < lists[top.list_idx].size()) {
            int next_idx = top.element_idx + 1;
            min_heap.push({lists[top.list_idx][next_idx], top.list_idx, next_idx});
        }
    }
    
    if (total_elements > 0) cout << endl;

    return 0;
}
```

---

## 5. 原理解析与复杂性分析

### 复杂度分析
*   **时间复杂度**: $O(N \log K)$
    *   $N$ 是总元素数。
    *   每个元素都会进行一次 `push` 和 `pop` 操作，每次堆操作耗时 $O(\log K)$。
*   **空间复杂度**: $O(K)$
    *   堆中同时最多只存在 $K$ 个元素（每行取出一个）。

### 常遇坑点 (Tips)
1.  **最大堆 vs 最小堆**：
    *   C++ 的 `priority_queue` 默认为**最大堆**（top 是最大的）。
    *   要变为**最小堆**，可以使用 `priority_queue<T, vector<T>, greater<T>>`。
    *   使用 `greater<T>` 时，必须要求结构体 `T` 重载好 `operator>`。所以代码中 `bool operator>(...)` 是必不可少的。

2.  **空列表处理**：
    *   初始化时千万不要存入空列表的索引，否则在 `pop` 后去取 `lists[list_idx][next_idx]` 时会发生越界错误。代码中的 `if (len > 0)` 就是为了防止这一点。

3.  **输入输出效率**：
    *   在处理 $10^4$ 规模的数据时，`std::endl` 会强制缓冲区刷新，执行较慢。本代码改为用 `\n` (如果是处理大量行) 或者通过 `ios_base::sync_with_stdio(false)` 优化输入输出，这对于提高代码在 OJ 系统上的通过率非常关键。

### 总结
这道题的核心不在于“排序”，而在于**“如何在多个序列中维护候选集，并实时更新”**。掌握了最小堆的使用逻辑，你就掌握了此类“多路归并”问题的万能钥匙。