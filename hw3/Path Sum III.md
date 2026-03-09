# Path Sum III/路径总和 III medium

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