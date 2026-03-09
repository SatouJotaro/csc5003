#include<iostream>
#include<vector>
#include<climits>
using namespace std;

struct TreeNode
{
    int val;
    int left;
    int right;
    TreeNode(int v, int l, int r) : val(v), left(l), right(r) {}
};

int max_sum = INT_MIN;

int maxGain(const vector<TreeNode>& nodes, int index){
    if(index == -1) return 0;
    const TreeNode& node = nodes[index];

    int left_gain = max(0, maxGain(nodes, node.left));
    int right_gain = max(0, maxGain(nodes, node.right));

    int current_path_sum = node.val + left_gain + right_gain;

    max_sum = max(max_sum, current_path_sum);

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
        nodes.emplace_back(val, left, right);
    }

    maxGain(nodes, 0);
    cout << max_sum << endl;
    return 0;
}