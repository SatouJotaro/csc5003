# Binary Tree Maximum Path Sum/二叉树中的最大路径和 hard
### 问题详细解析

#### 输入输出说明
- **输入格式**：
  - 第一行：一个整数 `n`，表示二叉树的节点数。
  - 接下来 `n` 行：每行三个整数 `val_i left_i right_i`，其中：
    - `val_i` 是节点 `i` 的值。
    - `left_i` 是节点 `i` 的左子节点的索引（如果不存在，则为 `-1`）。
    - `right_i` 是节点 `i` 的右子节点的索引（如果不存在，则为 `-1`）。
  - 根节点是节点 `0`。
- **输出格式**：
  - 输出一个整数：最大路径和。路径可以是任意非空简单路径（节点序列中相邻节点通过边连接，每个节点最多出现一次）。

#### 示例解释
- **示例输入**：
  ```
  5
  -10 1 2
  9 -1 -1
  20 3 4
  15 -1 -1
  7 -1 -1
  ```
  - 节点 `0`（根）：值 `-10`，左子节点 `1`，右子节点 `2`。
  - 节点 `1`：值 `9`，无子节点。
  - 节点 `2`：值 `20`，左子节点 `3`，右子节点 `4`。
  - 节点 `3`：值 `15`，无子节点。
  - 节点 `4`：值 `7`，无子节点。
- **示例输出**：`42`
  - 最大路径是 `15 -> 20 -> 7`（路径和为 `15 + 20 + 7 = 42`）。注意，路径可以经过中间节点（如节点 `20`），并连接左右子树。

#### 知识点
- **二叉树遍历**：使用深度优先搜索（DFS）遍历树结构。
- **动态规划**：在树结构上应用动态规划思想，计算每个节点的最大贡献值（即以该节点为结尾的路径和）。
- **全局最大值更新**：在遍历过程中维护全局最大路径和。

#### 解题思路
核心思想是使用递归DFS计算每个节点的最大路径和。具体步骤如下：
1. **定义递归函数**：`maxGain(node)` 返回以当前节点为根的子树中，从该节点向下延伸的最大路径和（即以当前节点结尾的路径和，不包括父节点部分）。
2. **递归处理子树**：
   - 递归计算左子节点的最大增益 `left_gain = max(0, maxGain(node.left))`。如果增益为负，则不包含左子节点（因为路径可以只包含当前节点）。
   - 同样计算右子节点的最大增益 `right_gain = max(0, maxGain(node.right))`。
3. **计算当前节点路径和**：以当前节点为路径中间节点的总路径和为 `current_path_sum = node.val + left_gain + right_gain`。
4. **更新全局最大值**：`max_sum = max(max_sum, current_path_sum)`。
5. **返回当前节点贡献**：返回 `node.val + max(left_gain, right_gain)`，以便父节点计算其增益。
6. **初始化全局最大值**：由于节点值可能为负，需初始化为负无穷（`INT_MIN`）。

最终，`max_sum` 即为整个树的最大路径和。

#### C++ 实现代码
```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// 定义树节点结构
struct TreeNode {
    int val;
    int left;
    int right;
    TreeNode(int v, int l, int r) : val(v), left(l), right(r) {}
};

int max_sum = INT_MIN; // 全局变量存储最大路径和

// 递归函数：计算以节点 index 为根的子树中，从该节点向下延伸的最大路径和
int maxGain(const vector<TreeNode>& nodes, int index) {
    if (index == -1) return 0; // 空节点返回0
    const TreeNode& node = nodes[index];
    
    // 递归计算左右子节点的最大增益（忽略负增益）
    int left_gain = max(0, maxGain(nodes, node.left));
    int right_gain = max(0, maxGain(nodes, node.right));
    
    // 计算以当前节点为中间节点的路径和
    int current_path_sum = node.val + left_gain + right_gain;
    
    // 更新全局最大路径和
    max_sum = max(max_sum, current_path_sum);
    
    // 返回当前节点的值加上左或右增益中的较大值（供父节点使用）
    return node.val + max(left_gain, right_gain);
}

int main() {
    int n;
    cin >> n;
    vector<TreeNode> nodes;
    nodes.reserve(n);
    
    // 读取输入并构建节点数组
    for (int i = 0; i < n; ++i) {
        int val, left, right;
        cin >> val >> left >> right;
        nodes.emplace_back(val, left, right);
    }
    
    // 从根节点开始递归计算
    maxGain(nodes, 0);
    
    // 输出结果
    cout << max_sum << endl;
    return 0;
}
```

#### 代码解释
- **节点结构**：使用 `TreeNode` 存储节点值和左右子索引。
- **递归函数** `maxGain`：
  - 如果节点为空，返回0。
  - 递归计算左右子节点的最大增益（确保只取非负值）。
  - 计算以当前节点为中间节点的路径和，并更新全局最大值。
  - 返回当前节点的贡献值。
- **主函数**：读取输入，构建节点数组，调用递归函数，并输出结果。

#### 时间复杂度
- **时间复杂度**：O(n)，每个节点只访问一次。
- **空间复杂度**：O(h)，其中 h 是树的高度（递归栈的空间），最坏情况下为 O(n)（链状树）。

这个方法高效地解决了二叉树最大路径和的问题，确保覆盖所有可能路径。