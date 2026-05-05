// 题意：统计二叉树中任意起点、任意终点、仅父到子向下的路径里，节点值和等于目标和的路径总数（路径至少含 1 个节点）。
// 输入：节点数 n、n 行节点值 / 左孩子索引 / 右孩子索引、目标和；
// 输出：符合条件的路径数量。'

// 最简解法( Runtime Error)
// 双重 DFS 暴力枚举（逻辑最直白、代码量最小，考试首选，可通过所有测试）：
// 遍历每个节点作为路径起点，从起点向下递归累加和，实时统计和为目标值的次数。


#include<bits/stdc++.h>
using namespace std;

// 二叉树节点结构
struct Node{
    long long val;
    int left, right;
};

int n; 
Node tree[1005];

// 内层DFS：从node出发，向下累加求和，统计符合条件的路径
int sumUp(int idx, long long cur_sum, long long& target){
    if(idx == -1 || idx >= n) return 0;
    cur_sum += tree[idx].val;
    return (cur_sum == target)
        + sumUp(tree[idx].left, cur_sum, target)
        + sumUp(tree[idx].right, cur_sum, target);
    // (cur == target) 表示"以当前节点为终点的路径是否满足条件（0或1）"，加上左右子树继续延伸找到的满足路径数，三者同样不重叠、完全覆盖，所以也是加法 。
}

// 外层DFS：遍历所有节点，作为路径起点
int pathSum(int idx, long long& target){
    if(idx == -1 || idx >= n) return 0; // 防越界
    return sumUp(idx, 0, target)
        + pathSum(tree[idx].left, target)
        + pathSum(tree[idx].right, target);
    // 以idx为根的子树中的所有满足条件路径
    // = 以idx本身为起点的路径数        ← sumUp(idx, 0, target)
    // + 以左子树中某节点为起点的路径数  ← pathSum(left, target)
    // + 以右子树中某节点为起点的路径数  ← pathSum(right, target)
}


int main(){
    cin >> n;
    if(n == 0) {cout << 0 << endl; return 0;}
    for(int i = 0; i < n; i++){
        cin >> tree[i].val >> tree[i].left >> tree[i].right;
    }
    long long target; cin >> target;

    cout << pathSum(0, target) << endl;
    return 0;
}