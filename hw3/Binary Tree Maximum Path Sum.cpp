#include<iostream>
#include<vector>
#include<climits>
using namespace std;

struct TreeNode
{
    int val;
    int left;
    int right;
    // 构造函数：利用初始化列表高效赋值
    TreeNode(int v, int l, int r) : val(v), left(l), right(r) {}
};

int max_sum = INT_MIN; // 全局变量，用于记录路径和的最大值

int maxGain(const vector<TreeNode>& nodes, int index){
    if(index == -1) return 0; // 递归终点：空节点贡献为0
    const TreeNode& node = nodes[index];

    // 获取左右子树的贡献，如果贡献为负，则舍弃(取0)
    int left_gain = max(0, maxGain(nodes, node.left));
    int right_gain = max(0, maxGain(nodes, node.right));

    // 计算经过当前节点的“最大路径和”，注意这包含了左右两边，形成一个“拱门”状路径
    int current_path_sum = node.val + left_gain + right_gain;

    // 更新全局最大值
    max_sum = max(max_sum, current_path_sum);

    // 返回给父节点：当前节点值 + 左右子树中贡献较大的一方（递归路径必须是单向的）
    return node.val + max(left_gain, right_gain);
}

int main(){
    int n;
    cin >> n;
    vector<TreeNode> nodes;
    nodes.reserve(n);

    for(int i = 0; i < n; i++){
        int val, left, right;
        cin >> val >> left >> right;
        // 使用 emplace_back 原地构造，省去临时对象拷贝
        nodes.emplace_back(val, left, right);
    }

    maxGain(nodes, 0); // 从根节点(下标0)开始
    cout << max_sum << endl;
    return 0;
}