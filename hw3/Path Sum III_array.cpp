#include<bits/stdc++.h>
using namespace std;

struct Node{
    int val, left, right;
};

const int MAXN = 100005;
Node nodes[MAXN]; // 静态申请数组，直接通过下标索引节点，模拟指针
int n, targetSum;
long long result = 0;

// 核心：哈希表存储“从根到当前路径上，每个出现过的前缀和及其次数”
// 作用：快速寻找是否存在一个祖先节点，使得从该祖先到当前节点路径和 == targetSum
unordered_map<long long, int> prefixCount;

void dfs(int idx, long long curSum){
    if(idx == -1) return;

    curSum += nodes[idx].val;

    // 3. 逻辑判断：前缀和公式
    // 如果存在一段路径和为 targetSum，则有：curSum - oldSum = targetSum
    // 即：oldSum = curSum - targetSum
    long long need = curSum - (long long)targetSum;
    if(prefixCount.count(need)){
        result += prefixCount[need]; // 加上历史上出现了多少次这个 need
    }

    // 4. 将当前 curSum 加入哈希表，供后续的子节点查找
    prefixCount[curSum]++;

    dfs(nodes[idx].left, curSum);
    dfs(nodes[idx].right, curSum);

    // 6. 回溯：离开当前节点时，必须将当前节点的 curSum 从哈希表中移除
    // 原因：我们只关心“从根到当前路径上”的前缀和，不能跨分支干扰
    prefixCount[curSum]--;
}

int main(){
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> nodes[i].val >> nodes[i].left >> nodes[i].right;
    }
    cin >> targetSum;

    if(n == 0) {cout << 0 << endl; return 0;}

    // 初始化：空路径和为 0，出现 1 次（代表从根节点开始的路径）
    prefixCount[0] = 1; 
    dfs(0, 0);
    cout << result << endl;
    return 0;
}

// 当你面对这种题时，不要试图一次性写出完整代码，请遵循以下三步思维法：
// 第一步：化繁为简（将其视为线性问题）
    // 把二叉树想象成一个“串”。任意一条向下的路径，其实就是序列中的一段连续子数组。对于连续子数组求和问题，最强大的工具就是前缀和 (Prefix Sum)。
    // 记住结论：只要看到“求和等于某值”的路径问题，第一反应就是 Map<前缀和, 次数>。
// 第二步：理解“回溯”的意义（为什么要有 prefixCount[curSum]--）
    // 初学者最容易漏掉这一步。请这样想象：
    // 哈希表就像一本书，记录了你从根走到当前位置，沿途所有的“印记”。
    // 当你从左子树回来，准备去右子树时，你在左子树留下的“印记”对于右子树来说是不存在的。
    // 所以，回溯不是为了“删掉数据”，而是为了“恢复状态”，保证每一条路径遍历都是独立的。
// 第三步：建立数组下标的心理模型
    // 别把 nodes[idx].left 当作数组访问。在你的脑海里，你可以把这行代码想象成一个箭头：
    // idx 是“我所在的点”。
    // nodes[idx] 是“点上的标签”。
    // nodes[idx].left 是“从当前点出发，通往左边的那条路的牌号”。
    // ACM 模式优势：数组下标写法让你无需管理 TreeNode 指针是否释放、是否内存泄露，你只需要关注 idx 这个“身份ID”即可。
// 总结
// 这种写法本质上是 “递归 + 前缀和 + 哈希优化搜索”。
    // 什么时候查表？ 在进入节点，更新 curSum 后，查有没有 curSum - targetSum。
    // 什么时候填表？ 在进入节点，查完表之后，把当前的 curSum 填进去。
    // 什么时候撤销？ 在递归函数结束前（即离开节点时）。
// 掌握了这三点，你会发现所有的“路径总和”类题目，代码结构几乎是一模一样的。