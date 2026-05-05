// 给定一棵 n 个节点的树，每个节点有一个字符，求一条最长路径使得路径上相邻节点的字符都不同，返回路径上的节点数

// 做法：树形 DFS（后序遍历合并两条子链）
// 核心思路：对每个节点 u，用 DFS 递归计算从 u 向下延伸的最长合法链长度。 同时在每个节点维护"最长"和"次长"两条子链，合并得到过 u 的最长路径，更新全局答案。


#include <bits/stdc++.h>
using namespace std;

int ans = 1;
vector<vector<int>> children;
string s;

// 返回从节点u出发，向下的最长合法链长度（含u自身算1）
int dfs(int u){
    int best1 = 0, best2 = 0; // 最长、次长的有效子链长度（不含u）

    for(int v : children[u]){
        int children = dfs(v);      // v子树的最长下行链（含v）
        if(s[v] == s[u]) continue;  // 字符相同，不能延伸

        // childLen+1 是从u经v向下的链长（含u）
        // 为了方便合并，这里存"不含u"的部分即childLen
        if(children >= best1) { best2 = best1; best1 = children;}
        else if(children > best2) { best2 = children; }
    }
    // 过u的最长路径 = u本身(1) + best1 + best2
    ans = max(ans, 1 + best1 + best2);
    return 1 + best1;  // 向上只能传递一条最长链
} 

int main(){
    int n; cin >> n;
    children.resize(n);

    for(int i = 0; i < n; i++){
        int p; cin >> p;
        if(p != -1) children[p].push_back(i);
    }
    cin >> s;

    dfs(0);
    cout << ans << "\n";
    return 0;
}