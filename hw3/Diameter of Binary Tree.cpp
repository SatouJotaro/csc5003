#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int val[MAXN]; // 节点的值
int lc[MAXN];  // 左孩子索引
int rc[MAXN];  // 右孩子索引
int n;
int ans = 0;   // 全局最大直径

/*
 * DFS 后序遍历
 * 返回值：以 node 为根的子树深度（边数）
 *   node == -1 时返回 -1（空节点，贡献0条边）
 *   叶子节点返回 0
 */
int dfs(int node){
    // 空节点，返回 -1
    if( node == -1 ) return -1; 

    // 后序：先递归左右子树
    int left_d = dfs(lc[node]);
    int right_d = dfs(rc[node]);

    // 经过当前节点的路径长度：
    // left_d  + 1 = 当前节点 到 左子树最远叶子 的边数
    // right_d + 1 = 当前节点 到 右子树最远叶子 的边数
    // 若某侧为空（返回-1），则 -1+1=0，即贡献0条边 ✓
    ans = max(ans, (left_d + 1) + (right_d + 1));

    // 返回当前子树深度（取较深一侧 +1）
    return max(left_d, right_d) + 1;
}

 int main(){
    cin >> n;

    // 读入所有节点
    for(int i = 0; i < n; i++){
        cin >> val[i] >> lc[i] >> rc[i];
    }

    // 特判：n <= 1 直径为 0
    if(n <= 1){
        cout << 0 << endl;
        return 0;
    }

    // 从根节点（索引0）开始DFS
    dfs(0);

    cout << ans << endl;

    return 0;
 }
