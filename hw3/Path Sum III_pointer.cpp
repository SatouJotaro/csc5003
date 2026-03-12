#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// 1. 定义标准的链式二叉树结构
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// 2. 辅助结构用于存储临时的输入数据
struct RawNode {
    int val, left, right;
};

// 全局变量，用于构建树
vector<RawNode> rawNodes;

// 3. 将数组下标表示的树，转化成指针表示的树
TreeNode* buildTree(int idx) {
    if (idx == -1) return nullptr;
    TreeNode* node = new TreeNode(rawNodes[idx].val);
    node->left = buildTree(rawNodes[idx].left);
    node->right = buildTree(rawNodes[idx].right);
    return node;
}

// 4. 基于指针的 DFS 逻辑
long long result = 0;
unordered_map<long long, int> prefixCount;
int target;

void dfs(TreeNode* node, long long curSum) {
    if (!node) return;

    curSum += node->val;

    // 前缀和逻辑
    if (prefixCount.count(curSum - target)) {
        result += prefixCount[curSum - target];
    }

    prefixCount[curSum]++;

    dfs(node->left, curSum);
    dfs(node->right, curSum);

    // 回溯
    prefixCount[curSum]--;
}

int main() {
    // 提升 I/O 速度
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if (!(cin >> n) || n == 0) {
        cout << 0 << endl;
        return 0;
    }

    rawNodes.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> rawNodes[i].val >> rawNodes[i].left >> rawNodes[i].right;
    }
    cin >> target;

    // --- 指针化操作开始 ---
    TreeNode* root = buildTree(0);
    
    prefixCount[0] = 1;
    dfs(root, 0);
    // --- 指针化操作结束 ---

    cout << result << endl;

    return 0;
}