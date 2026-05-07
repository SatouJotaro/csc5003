## 一、结论建议

这道题是典型的**子串统计与词频匹配问题**。

*   **题目含义**：在长字符串 $s$ 中，寻找所有满足以下条件的子串起始索引：该子串由给定的单词列表 `words` 中所有单词不计顺序地“拼接”而成。
*   **输入输出**：
    *   **输入**：$m, n, k$（$s$ 长度、单词数、单词长度），字符串 $s$，以及 $n$ 行单词。
    *   **输出**：第一行输出符合条件的索引总数 $c$；第二行按升序输出这些索引。
*   **最简做法**：利用 **`unordered_map` 统计频次 + 暴力枚举起始点**。虽然 $O(m \cdot n)$ 的复杂度在最坏情况下接近 $10^8$，但由于 $m$ 仅为 $10^4$ 且存在大量剪枝（非列表单词直接跳过），这种做法代码量最少且足以通过测试。

---

## 二、逻辑拆解与实现步骤

### 1. 核心逻辑：滑动窗口与词频对比
由于所有单词长度同为 $k$，一个合法的子串长度必然是 $n \times k$。我们只需要检查 $s$ 中每一个可能的起点 $i \in [0, m - n \cdot k]$：
1.  **预处理**：用一个哈希表 `target` 记录 `words` 中每个单词出现的次数。
2.  **枚举起点**：从 $i$ 开始，每次截取长度为 $k$ 的片段。
3.  **内部验证**：
    - 如果截取的片段不在 `target` 中，则该起点 $i$ 无效，跳出。
    - 如果截取的片段在当前窗口出现的次数超过了 `target` 中的次数，也无效，跳出。
    - 如果成功匹配了 $n$ 个单词，记录该索引 $i$。

### 2. 为什么选择暴力映射（Naive Map Check）？
*   **逻辑最简**：不需要考虑复杂的滑动窗口优化（即 $k$ 个偏移量的分组滑动），逻辑极其直观。
*   **代码量最小**：利用 C++ 标准库的 `unordered_map` 和 `substr`，核心检查逻辑仅需几行。

---

## 三、C++ 代码实现（ACM 模式）

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    // 1. 输入处理
    int m, n, k;
    if (!(cin >> m >> n >> k)) return 0;
    
    string s;
    cin >> s;
    
    unordered_map<string, int> target;
    for (int i = 0; i < n; ++i) {
        string word;
        cin >> word;
        target[word]++;
    }

    vector<int> res;
    // 2. 暴力枚举起点
    int total_len = n * k;
    for (int i = 0; i <= m - total_len; ++i) {
        unordered_map<string, int> seen;
        int j = 0;
        for (; j < n; ++j) {
            // 截取第 j 个单词
            string w = s.substr(i + j * k, k);
            // 检查该单词是否在目标列表中
            if (target.find(w) != target.end()) {
                seen[w]++;
                // 如果出现次数超过目标，提前结束
                if (seen[w] > target[w]) break;
            } else {
                // 如果单词根本不在列表中，提前结束
                break;
            }
        }
        // 如果 n 个单词全部匹配成功
        if (j == n) res.push_back(i);
    }

    // 3. 输出处理
    cout << res.size() << endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << (i == res.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
```

---

## 四、复杂度与优化说明

<details>
<summary>💭 <strong>性能与考点分析</strong>（点击展开）</summary>

1.  **时间复杂度**：
    *   外部循环次数 $m$。
    *   内部循环次数 $n$。
    *   字符串截取与哈希操作 $O(k)$。
    *   理论最坏复杂度为 $O(m \cdot n \cdot k)$。但在本题中 $n \cdot k \le m$，且无效单词会迅速 `break`（剪枝），实际运行效率非常高。
2.  **空间复杂度**：
    *   $O(n \cdot k)$ 用于存储哈希表。
3.  **更优解法（面试/竞赛进阶）**：
    *   **滑动窗口优化**：可以维护 $k$ 个滑动窗口，将复杂度降低到 $O(m \cdot k)$。
    *   **原理**：将 $s$ 分为 $k$ 组（起点分别为 $0, 1, \dots, k-1$），每一组通过两个指针维护一个大小固定的窗口。这种做法代码量会翻倍，除非 $m$ 达到 $10^5$ 以上，否则本题不推荐使用。
4.  **注意点**：
    *   题目要求 `c = 0` 时输出空行，上述代码中的 `cout << endl` 保证了即使 `res` 为空，也会输出换行符。

</details>

> **考试技巧**：在 $m=10^4$ 级别的字符串题目中，如果逻辑上能通过 `std::unordered_map` 解决，优先选择最简单的暴力组合法，以节省考试中的思考和调试时间。


## 一、原因分析

之前的做法出现 4 个 TLE（超时），是因为**暴力枚举 + 频繁构造子串**导致的复杂度过高：
- **时间瓶颈**：原代码在每个 $i$ 位置都会创建一个新的 `unordered_map` 并进行多次 `substr` 字符串拷贝。在最坏情况下，复杂度为 $O(m \cdot n \cdot k)$。
- **计算量**：$10^4 \times 5000 \times 30$ 的量级远超 1 秒能处理的范围（约 $10^8$ 次操作）。

---

## 二、优化策略：K-偏移滑动窗口

要通过此题，必须将复杂度降到 **$O(m \cdot k)$**。

### 1. 核心逻辑：分组滑动
由于每个单词长度固定的为 $k$，我们可以将字符串 $s$ 分成 $k$ 组。例如，$k=3$ 时：
- 第一组从索引 $0, 3, 6 \dots$ 开始看
- 第二组从索引 $1, 4, 7 \dots$ 开始看
- 第三组从索引 $2, 5, 8 \dots$ 开始看

在每一组中，我们使用**双指针（滑动窗口）**来维护当前匹配的单词频率。这样每个字符只会被处理常数次。

### 2. 怎么做：
1. **预处理目标词频**：用一个 `unordered_map` 记录 `words` 中每个单词的出现次数。
2. **多起点搜索**：循环 `i` 从 `0` 到 `k-1`。
3. **窗口滑动**：
   - 维护一个 `window` 哈希表和一个 `count`（当前窗口内有效单词数）。
   - 右指针 `R` 每次向右跳 $k$ 个步长，截取一个长为 $k$ 的单词。
   - 如果该单词在目标中，加入 `window`。如果 `window` 中该词频率超过目标频率，左指针 `L` 向右跳，直到频率恢复正常。
   - 如果截取的单词不在目标中，直接清空 `window`，左指针 `L` 跳到 `R` 的下一个位置。

---

## 三、代码实现（代码量小且性能高效）

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0); // 加速快读
    int m, n, k;
    if (!(cin >> m >> n >> k)) return 0;
    string s; cin >> s;
    
    unordered_map<string, int> target;
    for (int i = 0; i < n; ++i) {
        string w; cin >> w;
        target[w]++;
    }

    vector<int> res;
    // 如果 s 长度不足以容纳所有单词，直接输出 0
    if (m < n * k) {
        cout << 0 << endl << endl;
        return 0;
    }

    // 只需枚举 k 种起始偏移
    for (int i = 0; i < k; ++i) {
        unordered_map<string, int> win;
        int count = 0;
        int left = i;
        // 步长为 k 的滑动窗口
        for (int right = i; right <= m - k; right += k) {
            string w = s.substr(right, k);
            if (target.count(w)) {
                win[w]++;
                count++;
                // 如果当前单词多了，从左边缩减直到不多为止
                while (win[w] > target[w]) {
                    string left_w = s.substr(left, k);
                    win[left_w]--;
                    count--;
                    left += k;
                }
                // 窗口内的单词数量正好等于 n，说明匹配成功
                if (count == n) res.push_back(left);
            } else {
                // 遇到不在列表中的单词，重置窗口
                win.clear();
                count = 0;
                left = right + k;
            }
        }
    }

    // 题目输出要求排序
    sort(res.begin(), res.end());
    cout << res.size() << endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << (i == (int)res.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
```

---

## 四、为什么这个能过？

1.  **复杂度大幅降低**：外层循环 $k$ 次，内层循环 $m/k$ 次，总的字符串操作量是 $O(m)$ 级别的。总时间复杂度约为 $O(m \cdot k)$。
2.  **避免重复计算**：滑动窗口利用了“上一个窗口的结果”，不需要像暴力法那样对每一个索引都从头开始统计 `n` 个单词。
3.  **内存友好**：虽然还在用 `substr`，但调用的次数从 $O(m \cdot n)$ 降到了 $O(m)$，不会再触发大规模的内存申请和拷贝导致的 TLE。

<details>
<summary>💭 <strong>考试避坑指南</strong>（点击展开）</summary>

- **快读**：`ios::sync_with_stdio(false); cin.tie(0);` 在处理 $10^4$ 以上数据时很重要。
- **边界条件**：如果 $n \times k > m$，必须特判处理，否则 `m - k` 可能会出现负数或逻辑错误。
- **排序**：因为我们是按 $k$ 个偏移量并行计算的，最后得到的索引列表不是天然有序的，必须 `sort`。
- **输出格式**：题目要求 `c=0` 时第二行为空行，代码中的 `cout << endl` 确保了即使结果为空，也会满足换行要求。

</details>