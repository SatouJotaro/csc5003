# Path Sum III/路径总和 III medium

给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

> https://leetcode.cn/problems/path-sum/description/
> https://leetcode.cn/problems/path-sum-ii/
> https://leetcode.cn/problems/path-sum-iii/

## 一、读懂输入输出

### 输入
```
9          ← n = 9 个节点

10  1  2   ← 节点0：值=10，左孩子=节点1，右孩子=节点2
 5  3  4   ← 节点1：值=5，  左孩子=节点3，右孩子=节点4
-3 -1  5   ← 节点2：值=-3， 无左孩子，  右孩子=节点5
 3  6  7   ← 节点3：值=3，  左孩子=节点6，右孩子=节点7
 2 -1  8   ← 节点4：值=2，  无左孩子，  右孩子=节点8
11 -1 -1   ← 节点5：值=11， 叶节点
 3 -1 -1   ← 节点6：值=3，  叶节点
-2 -1 -1   ← 节点7：值=-2， 叶节点
 1 -1 -1   ← 节点8：值=1，  叶节点

8          ← targetSum = 8
```

### 对应树形结构
```
          10  (节点0)
         /  \
        5    -3  (节点1,2)
       / \     \
      3   2    11  (节点3,4,5)
     / \   \
    3  -2   1  (节点6,7,8)
```

### 输出
```
3   ← 有3条向下路径的节点值之和等于8
```

三条路径分别是：
- `5 → 3`（和 = 8）✓
- `5 → 2 → 1`（和 = 8）✓  
- `-3 → 11`（和 = 8）✓

---

## 二、知识点

| 知识点 | 说明 |
|--------|------|
| **二叉树 DFS** | 深度优先遍历整棵树 |
| **前缀和（Prefix Sum）** | 记录从根到当前节点的路径累加和 |
| **哈希表** | 快速查询之前出现过的前缀和次数 |

> 这是 LeetCode 437 的经典题，核心技巧：**前缀和 + 回溯**

---

## 三、解题思路

### 暴力思路（O(n²)）
对每个节点，向下遍历所有路径，统计和等于 targetSum 的路径数。

### 最优思路：前缀和 + 哈希表（O(n)）

**核心公式：**
> 若从根到当前节点的累计和为 `curSum`，  
> 若存在某个祖先节点，其从根到它的累计和为 `prefix`，  
> 且 `curSum - prefix == targetSum`，  
> 则从该祖先的**下一个节点**到当前节点构成一条满足条件的路径。

```
        prefix
root ──────────► 祖先节点 ──────────► 当前节点
                           这段路径和
                        = curSum - prefix
                        = targetSum  ✓
```

**算法步骤：**
1. 初始化哈希表 `map[0] = 1`（空路径，前缀和为0出现1次）
2. DFS遍历每个节点，维护 `curSum`（根到当前节点的累计和）
3. 到达当前节点时，查询 `map[curSum - targetSum]` 的次数并累加到答案
4. 将 `curSum` 加入哈希表
5. 递归左右子树
6. **回溯**：退出时将 `curSum` 从哈希表中移除（避免影响其他分支）

---

## 四、手动模拟

```
初始: map = {0:1}, result = 0

进入节点0(val=10): curSum=10, 查map[10-8=2]=0, map={0:1,10:1}
  进入节点1(val=5):  curSum=15, 查map[15-8=7]=0, map={0:1,10:1,15:1}
    进入节点3(val=3): curSum=18, 查map[18-8=10]=1 ✓ result=1 (路径:5→3)
      进入节点6(val=3): curSum=21, 查map[21-8=13]=0
      进入节点7(val=-2):curSum=16, 查map[16-8=8]=0
    退出节点3
    进入节点4(val=2): curSum=17, 查map[17-8=9]=0
      进入节点8(val=1): curSum=18, 查map[18-8=10]=1 ✓ result=2 (路径:5→2→1)
    退出节点4
  退出节点1
  进入节点2(val=-3): curSum=7, 查map[7-8=-1]=0, map={0:1,10:1,7:1}
    进入节点5(val=11):curSum=18, 查map[18-8=10]=1 ✓ result=3 (路径:-3→11)
  退出节点2

最终 result = 3 ✓
```

---

## 五、C++ 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val, left, right;
};

const int MAXN = 100005;
Node nodes[MAXN];
int n, targetSum;
long long result = 0;
unordered_map<long long, int> prefixCount;

void dfs(int idx, long long curSum) {
    if (idx == -1) return;
    
    curSum += nodes[idx].val;  // 更新当前前缀和
    
    // 查询有多少祖先的前缀和 = curSum - targetSum
    long long need = curSum - (long long)targetSum;
    if (prefixCount.count(need)) {
        result += prefixCount[need];
    }
    
    // 将当前前缀和加入哈希表
    prefixCount[curSum]++;
    
    // 递归左右子树
    dfs(nodes[idx].left,  curSum);
    dfs(nodes[idx].right, curSum);
    
    // 回溯：退出时撤销
    prefixCount[curSum]--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nodes[i].val >> nodes[i].left >> nodes[i].right;
    }
    cin >> targetSum;
    
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    
    // 空路径前缀和为0，初始放入哈希表
    prefixCount[0] = 1;
    
    dfs(0, 0);  // 从根节点(节点0)开始
    
    cout << result << endl;
    
    return 0;
}
```

---

## 六、复杂度分析

| 项目 | 复杂度 |
|------|--------|
| 时间复杂度 | O(n)，每个节点只访问一次 |
| 空间复杂度 | O(n)，哈希表 + 递归栈 |

---

## 七、关键细节提醒

> ⚠️ **为什么要回溯？**  
> 哈希表存的是**当前根到当前节点这条路径上**的前缀和，不能让一个分支的数据影响另一个分支，因此退出节点时必须撤销。

> ⚠️ **为什么初始化 `map[0] = 1`？**  
> 代表从根节点直接开始的路径（前缀和为0的"空路径"存在），否则会漏掉从根出发的路径。

---
## 指针 solution

这是一个经典的题目，通常被称为“路径总和 III”（Path Sum III）。它比你之前做的题目更复杂，因为它**不要求从根节点出发，也不要求到叶子节点结束**。只要是“向下”的路径都可以。

### 一、 题目含义与输入输出

#### 1. 题目逻辑（核心难点）
*   **不一定要根节点开头**：例如路径可以是从中间某个子节点开始。
*   **向下移动**：只能顺着父子关系往下走。
*   **逻辑转换**：由于路径中间可能中断，我们不需要遍历所有可能的起点（那样复杂度太高）。我们可以利用**前缀和 (Prefix Sum)** 的思想：
    *   设从根到节点 $u$ 的路径和为 `curSum`。
    *   如果我们想找一条和为 `targetSum` 的路径，那么在这条路径中间某处，一定存在一个节点（前缀），使得 `(从根到该节点的路径和) == curSum - targetSum`。
    *   我们只需要在路径遍历过程中，用哈希表实时记录“从根到当前路径上各个节点的前缀和发生了多少次”即可。

#### 2. 输入输出解释
*   **输入方式**：这道题没有直接给你 `TreeNode` 指针，而是给了一个数组 `nodes[MAXN]`。其中的 `left` 和 `right` 存的是**数组的下标**。
*   **输入格式**：第一行是节点总数，后面 $N$ 行定义了每个节点的数值及左右子节点的“索引”。
*   **输出**：满足条件的路径个数。

---

### 二、 如何将其“指针化/面向对象化”？

你现在的代码用的是“数组存节点”的静态写法（这是竞赛中的常用手段）。如果想让它更符合 C++ 面向对象编程的习惯（指针化），我们可以定义 `struct Node` 并动态分配内存。

**清晰的指针递归思路：**

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// 1. 定义经典的指针式结构
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    unordered_map<long long, int> prefixCount;
    int target;
    long long count = 0;

public:
    void dfs(TreeNode* node, long long curSum) {
        if (!node) return;

        // 累计当前路径和
        curSum += node->val;

        // 2. 匹配逻辑：curSum - oldSum = target  =>  oldSum = curSum - target
        if (prefixCount.count(curSum - target)) {
            count += prefixCount[curSum - target];
        }

        // 3. 将当前累加和存入哈希表
        prefixCount[curSum]++;

        // 递归子树
        dfs(node->left, curSum);
        dfs(node->right, curSum);

        // 4. 回溯：退出节点时，移除当前的前缀和，防止影响其他分支
        prefixCount[curSum]--;
    }

    int pathSum(TreeNode* root, int targetSum) {
        target = targetSum;
        prefixCount[0] = 1; // 重要：基础前缀和 0 出现了一次
        dfs(root, 0);
        return (int)count;
    }
};
```

---

### 三、 为什么要这么改？（指针化的优点）

1.  **解耦（Decoupling）**：
    *   原先你的 `dfs` 函数高度依赖全局变量 `nodes[]` 数组。如果程序里有多棵树需要处理，全局数组会变得极其混乱且难以维护。
    *   使用指针后，`dfs` 只需要知道“当前节点是谁”，逻辑完全封装在类里，非常容易测试和迁移。

2.  **安全性（Memory Management）**：
    *   在真实工程中，树的结构是动态生成的。使用指针和 `new` 操作符，可以根据实际情况动态分配内存，而不是预先占用一个巨大的 `MAXN` 数组。

3.  **递归可读性**：
    *   `dfs(node->left, curSum)` 读起来比 `dfs(nodes[idx].left, curSum)` 更加直观——你在表达“处理左孩子”，而不是“处理编号为 X 的数据”。

### 对你目前代码的建议：
你原本的逻辑其实是**非常完美的**！这就是标准的“前缀和+哈希+回溯”。
如果这是算法竞赛题，保留原来的数组下标写法没有问题（效率甚至更高）。但如果你是在做项目或者是为了提升代码重构能力，记得把“**下标访问节点**”的习惯向“**指针传递对象**”转变，这是从“题目解法”迈向“软件工程”的一大步。

## 力扣 solution 
这一行代码是 C++11 引入的非常强大的特性：**Lambda 表达式（匿名函数）** 配合 **`std::function` 包装器**。

为了让你彻底理解，我将它拆解成三个部分：为什么用它？它的结构是什么？它的灵魂是什么？

---

### 1. 为什么用它？（解决的问题）
在常规的类（`class Solution`）中，如果你想定义一个 `dfs` 函数，通常有两个选择：
*   **成员函数**：你需要把 `result` 和 `prefixCount` 作为成员变量放入 `class`，这会污染类的接口，且不适合多次执行。
*   **嵌套辅助函数 (lambda)**：直接在 `pathSum` 函数内部定义 `dfs`，这样 `dfs` 可以直接访问 `pathSum` 函数作用域内的局部变量（如 `result`, `prefixCount`, `targetSum`），**无需作为参数传递**。

### 2. 语法详细拆解
`function<void(TreeNode*, long long)> dfs = [&](TreeNode* idx, long long curSum) { ... };`

*   **`function<void(TreeNode*, long long)>`**：
    *   这是一个“类型包装器”。它告诉编译器：“`dfs` 是一个函数，它的返回值是 `void`，接收的参数是 `TreeNode*` 指针和 `long long` 数值”。
    *   它是为了解决 Lambda 递归调用时的“类型推导问题”。如果没有它，Lambda 内部无法直接调用自己（因为此时 `dfs` 变量还没完全定义完成）。

*   **`[&]` (捕获列表)**：
    *   这是 Lambda 的核心灵魂。
    *   `&` 的意思是：**引用捕获**。它告诉编译器：“在这个函数内部，可以直接使用 `pathSum` 函数里定义的所有局部变量（`result`, `prefixCount`, `targetSum`）”。
    *   因为是“引用”，所以你在 `dfs` 中修改 `result`，外面的 `result` 也会改变。

*   **`(TreeNode* idx, long long curSum)`**：
    *   这是 Lambda 的参数列表，和普通的函数参数写法一模一样。

---

### 3. 为什么一定要用 `std::function` 才能递归？

这是一个容易让人困惑的地方。如果直接写：
```cpp
auto dfs = [&](TreeNode* idx, long long curSum) {
    ... 
    dfs(idx->left, ...); // 编译器报错！
};
```
**原因**：编译器在解析 `dfs` 的定义时，还没有确定 `dfs` 的类型。`auto` 会卡死。

**解决办法**：
使用 `std::function<void(TreeNode*, long long)>` 显式定义类型，相当于先“挂牌”，告诉编译器：我知道以后会有一个叫 `dfs` 的函数，它的类型是 `void(TreeNode*, long long)`，所以即使在函数体内部引用 `dfs`，编译器也能认出来。

---

### 4. 总结：与传统写法的对比

在 ACM 模式中，你通常习惯这样写：

**传统写法（全局变量）**：
```cpp
long long res;
void dfs(...) { ... }
int main() { ... dfs(...) ... } 
// 缺点：不能在多组测试数据下安全重置状态，也不符合封装要求。
```

**现代 C++ 写法（Lambda）：**
```cpp
int pathSum(TreeNode* root, int target) {
    long long res = 0;
    // 逻辑被锁在了函数内部，极其清晰，互不干扰
    function<void(TreeNode*, long long)> dfs = [&](TreeNode* node, long long sum) {
        // 直接访问外层变量，简洁高效
    };
    dfs(root, 0);
    return res;
}
```

### 给你的建议
1.  **如果你是在刷力扣**：推荐掌握这种写法。它能让你把所有逻辑都封装在一个函数里，不需要写复杂的成员变量，代码看起来非常紧凑、专业。
2.  **如果你是在打 ACM 比赛**：
    *   如果在意**性能**：`std::function` 因为涉及函数指针的包装，会有微小的性能开销。竞赛高手往往会定义一个**全局的 Lambda** (直接用 `auto` 定义全局变量) 或者干脆写成类内部的私有成员函数。
    *   如果在意**可读性**：这种写法是目前 C++ 工业界的主流逻辑，建议熟练掌握。

**只需记住口诀**：`[&]` 自动捕获作用域，`std::function` 解决递归类型纠。

```cpp
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        long long result = 0;
        unordered_map<long long, int> prefixCount;
        prefixCount[0] = 1;

        function<void(TreeNode*, long long)> dfs = [&](TreeNode* idx, long long curSum){
            if ( idx == nullptr) return;

            curSum += idx->val;

            long long need = curSum - (long long)targetSum;
            if(prefixCount.count(need)){
                result += prefixCount[need];
            }

            prefixCount[curSum]++;

            dfs(idx->left, curSum);
            dfs(idx->right, curSum);

            prefixCount[curSum]--;
        };

        dfs(root, 0);
        return (int)result;
    }
};
```