这道题是经典的动态规划（Dynamic Programming）题目，通常被称为**“回文切割”（Palindrome Partitioning）**问题。

### 1. 题目理解

*   **输入**：一个长度不超过 1000 的字符串 $s$。
*   **输出**：将字符串切分成若干个回文子串，所需的**最少切割次数**。
*   **核心逻辑**：
    *   如果整个字符串本身就是回文，切割次数为 0。
    *   切一刀会产生 2 个子串，切 $k$ 刀会产生 $k+1$ 个子串。我们的目标是使得切出来的每一个片段都是回文，同时让切的刀数最少。

---

### 2. 涉及知识点

1.  **动态规划 (Dynamic Programming)**：这是解决此类划分问题的标准方法。我们需要利用子问题的最优解来推导大问题的最优解。
2.  **字符串处理与回文预处理**：判断子串是否为回文可以用预处理的表格（$O(n^2)$）来快速查询。

---

### 3. 解题思路

我们将问题分为两步：

#### 第一步：预处理所有子串是否为回文
我们需要快速知道 $s[i \dots j]$ 是否为回文。可以使用一个二维数组 `isPal[i][j]` 来记录：
*   如果 $s[i] == s[j]$ 且（中间子串 $s[i+1 \dots j-1]$ 是回文或者长度小于等于 2），那么 `isPal[i][j]` 就是 `true`。
*   循环遍历填表：
    ```cpp
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                if (len <= 2) isPal[i][j] = true;
                else isPal[i][j] = isPal[i+1][j-1];
            }
        }
    }
    ```

#### 第二步：DP 计算最少切割次数
定义 `dp[i]` 为字符串前缀 $s[0 \dots i-1]$ 的最少切割次数。
*   **初值**：`dp[0] = -1` （空字符串，理解为分割成 0 个回文串，计算切割数时引入这个基准值方便逻辑处理）。
*   **转移方程**：对于每个位置 $i$（代表前缀长度），遍历所有可能的断点 $j \in [0, i-1]$：
    *   如果 $s[j \dots i-1]$ 是回文，则：
        `dp[i] = min(dp[i], dp[j] + 1)`
    *   这样，$dp[n]$ 就是将整个字符串切割成回文子串的最小切割数。

---

### 4. C++ 实现

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int minCuts(string s) {
    int n = s.length();
    if (n == 0) return 0;

    // 1. 预处理回文表
    vector<vector<bool>> isPal(n, vector<bool>(n, false));
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                if (len <= 2) isPal[i][j] = true;
                else isPal[i][j] = isPal[i + 1][j - 1];
            }
        }
    }

    // 2. DP 计算最小切割
    // dp[i] 表示前 i 个字符组成的字符串最少需要切割多少次
    vector<int> dp(n + 1, n); // 初始化为最大值 n
    dp[0] = -1; // 空串切0刀（对应后续逻辑，即切成回文段需要的刀数）

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (isPal[j][i - 1]) {
                dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }

    return dp[n];
}

int main() {
    string s;
    if (cin >> s) {
        cout << minCuts(s) << endl;
    }
    return 0;
}
```

### 为什么 `dp[0]` 要设为 `-1`？
这是一个技巧：
*   当整个字符串 $s[0 \dots n-1]$ 本身就是回文时，我们在遍历 $j=0$ 时会发现它是回文。
*   根据公式 `dp[n] = dp[0] + 1`，则 `dp[n] = -1 + 1 = 0`。
*   这样正好符合题目要求（如果是回文，切割数为0）。如果不是回文，$dp[j]$ 会叠加前面计算出的切割数，逻辑非常顺畅。

### 总结
*   **复杂度**：时间复杂度为 $O(n^2)$，因为有两层嵌套循环；空间复杂度为 $O(n^2)$，用于存储回文表。
*   对于 $n=1000$ 的数据量，$1000^2 = 1,000,000$，在 C++ 中可以在毫秒级内完成，完全满足要求。

