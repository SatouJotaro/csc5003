### 题目分析

这道题要求计算从站点0到达站点1到站点n的最小总成本。铁路系统有两条路线：常规路线和快速路线。每条路线上的移动成本已知，且在站点切换路线时，从常规切换到快速需要额外费用expressCost，从快速切换回常规免费。目标是输出每个站点i的最小成本costs[i]，即到达站点i的最小总成本（到达方式可以是常规或快速路线）。

#### 输入输出
- **输入**:
  - 第一行：两个整数 `n`（站点数）和 `expressCost`（切换费用）。
  - 第二行：`n` 个整数 `regular[1..n]`，表示常规路线上从站点i-1到i的成本。
  - 第三行：`n` 个整数 `express[1..n]`，表示快速路线上从站点i-1到i的成本。
- **输出**:
  - 一行，`n` 个整数 `costs[1..n]`，用空格分隔，表示每个站点i的最小成本。

#### 知识点
本题属于**动态规划（DP）**问题，具体是路径选择问题。动态规划通过分解问题为子问题，并利用子问题的最优解来构建整体最优解。这里，我们跟踪到达每个站点的最小成本，考虑不同的路线选择和切换操作。

#### 解题思路
1. **状态定义**：
   - `dp_reg[i]`：到达站点i的最小成本，且到达时在常规路线上。
   - `dp_exp[i]`：到达站点i的最小成本，且到达时在快速路线上。
   - `costs[i] = min(dp_reg[i], dp_exp[i])`：到达站点i的最小成本（无论路线）。

2. **初始状态**：
   - 站点0：在常规路线上，所以 `dp_reg[0] = 0`（未移动时成本为0）。
   - 如果要到达站点0 via快速路线，需要在站点0切换到快速路线，成本为 `expressCost`，所以 `dp_exp[0] = expressCost`。

3. **递推关系**：
   - 对于站点i（i从1到n）：
     - `dp_reg[i] = min(dp_reg[i-1], dp_exp[i-1]) + regular[i]`：到达站点i via常规路线，可以从站点i-1 via常规路线直接移动，或从站点i-1 via快速路线切换回常规（免费）后移动。
     - `dp_exp[i] = express[i] + min(dp_exp[i-1], dp_reg[i-1] + expressCost)`：到达站点i via快速路线，可以从站点i-1 via快速路线直接移动，或从站点i-1 via常规路线切换到快速（付费）后移动。

4. **计算过程**：
   - 初始化 `dp_reg_prev = 0`（对应i=0）和 `dp_exp_prev = expressCost`（对应i=0）。
   - 对于i从1到n：
     - 计算 `dp_reg_curr` 和 `dp_exp_curr`。
     - `costs[i] = min(dp_reg_curr, dp_exp_curr)`。
     - 更新 `dp_reg_prev` 和 `dp_exp_curr` 为当前值，用于下一次迭代。

5. **复杂度分析**：
   - 时间复杂度：O(n)，只需一次遍历所有站点。
   - 空间复杂度：O(n)，用于存储 `costs` 数组（n最大为200,000，可接受）。

#### C++实现代码
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    long long expressCost;
    cin >> n >> expressCost;
    vector<long long> regular(n);
    vector<long long> express(n);
    for (int i = 0; i < n; i++) {
        cin >> regular[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> express[i];
    }

    // 初始化站点0的状态
    long long dp_reg_prev = 0;          // dp_reg[0]
    long long dp_exp_prev = expressCost; // dp_exp[0]
    vector<long long> costs(n);        // 存储costs[1..n]

    // 计算每个站点i的最小成本
    for (int i = 1; i <= n; i++) {
        // 计算当前站点的状态
        long long dp_reg_curr = min(dp_reg_prev, dp_exp_prev) + regular[i-1];
        long long dp_exp_curr = express[i-1] + min(dp_exp_prev, dp_reg_prev + expressCost);
        costs[i-1] = min(dp_reg_curr, dp_exp_curr); // costs[i-1] 对应站点i

        // 更新状态为下一次迭代做准备
        dp_reg_prev = dp_reg_curr;
        dp_exp_prev = dp_exp_curr;
    }

    // 输出结果
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << costs[i];
    }
    cout << endl;

    return 0;
}
```

#### 代码说明
- **输入处理**：读取n、expressCost、regular数组和express数组。
- **初始化**：设置初始状态 `dp_reg_prev` 和 `dp_exp_prev`。
- **动态规划循环**：对于每个站点i，计算当前状态并存储最小成本到 `costs`。
- **输出**：打印所有 `costs[i]` 值。

此代码高效且符合题目要求，能处理最大n=200,000的输入。