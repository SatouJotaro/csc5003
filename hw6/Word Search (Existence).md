# 题目解析

## 题目含义

在一个 **m×n 的字母网格**中，判断给定单词 `word` 是否能被找到。

单词必须由**相邻格子**（上下左右）中的字母**依次连接**构成，且**同一个格子不能重复使用**。

---

## 输入输出解释

### 输入
```
3 4        ← 网格大小：3行4列
ABCE       ← 第1行
SFCS       ← 第2行  
ADEE       ← 第3行
ABCCED     ← 要搜索的单词
```

### 网格可视化
```
A B C E
S F C S
A D E E
```

### 输出
```
YES   ← 单词存在则输出YES，否则输出NO
```

### 验证示例
`ABCCED` 的路径如下：
```
[A]→[B]→[C]  E
 S   F  [C]  S
 A  [D]←[E]  E
```
路径：(0,0)→(0,1)→(0,2)→(1,2)→(2,2)→(2,1) ✅

---

## 涉及的算法与数据结构

### 核心算法：回溯法（Backtracking）+ DFS深度优先搜索

```
对网格中每个格子作为起点：
  └── 若当前字母匹配 → 标记已访问
        ├── 向上下左右4个方向继续搜索下一个字母
        ├── 找到完整单词 → 返回YES
        └── 搜索失败 → 撤销标记（回溯）继续尝试
```

### 知识点总结

| 知识点 | 说明 |
|--------|------|
| **DFS** | 沿一条路径深入搜索 |
| **回溯** | 搜索失败时撤销选择，尝试其他路径 |
| **visited标记** | 防止同一格子重复使用 |
| **二维网格遍历** | 4个方向的相邻格子 |

---

## 核心代码框架

```python
def solve():
    m, n = map(int, input().split())
    board = []
    for _ in range(m):
        board.append(input())
    word = input()
    
    visited = [[False]*n for _ in range(m)]
    
    # 方向数组：上下左右
    dirs = [(-1,0),(1,0),(0,-1),(0,1)]
    
    def dfs(r, c, idx):
        # 找到完整单词
        if idx == len(word):
            return True
        # 越界或字母不匹配或已访问
        if r < 0 or r >= m or c < 0 or c >= n:
            return False
        if visited[r][c] or board[r][c] != word[idx]:
            return False
        
        visited[r][c] = True          # 标记访问
        for dr, dc in dirs:
            if dfs(r+dr, c+dc, idx+1):
                return True
        visited[r][c] = False         # 回溯撤销
        return False
    
    # 枚举每个起点
    for i in range(m):
        for j in range(n):
            if dfs(i, j, 0):
                print("YES")
                return
    print("NO")

solve()
```

### 时间复杂度
- **O(m × n × 4^L)**，L为单词长度
- 由于约束较小（m,n≤6，|word|≤15），完全可以接受 ✅

## vector<string>
这是一个非常好的直觉！在 C++ 中，`vector<string>` 实际上也就是我们常说的“二维字符数组”。

这里有两个层面的原因：**习惯用法**和**内存结构**。

### 1. 为什么常用 `vector<string>` 而不是 `string board[10][10]`？

*   **动态大小（灵活性）**：题目只给了限制 `m, n <= 6`，但在实际编程中，我们往往不知道输入的 `m` 和 `n` 具体是多少。`vector` 可以根据输入的大小动态开辟空间，而普通的二维数组在声明时必须给出常量维度（或者使用较麻烦的动态内存分配）。
*   **代码简洁**：`vector<string>` 将每一行作为一个 `string` 对象存储。访问某个格子时，语法非常直观：`board[i][j]`。这和访问二维数组是一模一样的。
*   **输入方便**：C++ 的 `cin >> string_variable` 会自动处理换行符和空格，逐行读取字符串非常方便。

### 2. 它们内存结构的本质是相同的

在内存中，`vector<string>` 和 `vector<vector<char>>` 的逻辑结构是非常相似的：

```cpp
// 如果你定义如下：
vector<string> board(m); // 声明 m 行
for(int i=0; i<m; i++) cin >> board[i]; // 每行读取一个字符串

// 访问方式：
// board[0] 得到的是第一行字符串 "ABCE"
// board[0][0] 得到的就是 'A'
```

对比 `vector<vector<char>>`：
```cpp
vector<vector<char>> board(m, vector<char>(n));
// 访问方式：
// board[0][0] 得到的就是 'A'
```

**结论：** 
对于这道题目，无论是用 `vector<string>` 还是 `vector<vector<char>>`，**代码里访问格子的形式都是 `board[i][j]`**，逻辑完全没有任何区别。

### 为什么要选 `vector<string>` 而不用 `char[][]`？

1.  **安全性**：`vector` 会进行越界检查（如果使用 `.at()` 方法），且自带内存管理，不会导致内存泄漏。
2.  **语义清晰**：在 C++ 中，字符串（`string`）本身就是字符的集合，对于“网格中每一行都是一个单词”的情况，`vector<string>` 天生契合题目描述。
3.  **方便交互**：题目输入示例每一行就是一个字符串（例如 `ABCE`），`vector<string>` 可以直接通过 `cin` 一次性读入一行，比用嵌套循环逐个读取字符要快得多。

**总结建议：**
既然题目输入是一行行给出的字符串，你就用 `vector<string> board(m)`，然后通过 `cin >> board[i]` 读入。访问时直接写 `board[i][j]` 即可。这在算法竞赛（如 LeetCode 或各类在线评测系统）中是最标准的写法。