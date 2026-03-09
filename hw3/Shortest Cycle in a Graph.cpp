#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;

    // 创建邻接表：adj[u]存储u的所有邻居
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        // 无向图：u可以到v，v也可以到u
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    const int INF = INT_MAX;
    int answer = INF;

    vector<bool> visited(n, false); // 节点是否已访问
    vector<int> depth(n, 0);        // BFS深度（到起点的距离）
    vector<int> parent(n, -1);      // BFS中的父节点

    // 遍历每个顶点作为BFS起点
    for(int start = 0; start < n; start++){
        // 如果已经访问过，跳过（避免重复计算）
        if(visited[start]) continue;

        // 初始化BFS
        queue<int> q;
        q.push(start);
        visited[start] = true;
        depth[start] = 0;
        parent[start] = -1;

        // BFS遍历
        while(!q.empty()){
            int u = q.front();
            q.pop();

            // 遍历u的所有邻居
            for(int v : adj[u]){
                if(!visited[v]){
                    // v未访问：继续BFS
                    visited[v] = true;
                    depth[v] = depth[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
                else if(v != parent[u]){
                    // v已访问，且v不是u的父节点 → 发现环！
                    // 计算环的长度
                    int cycle_len = depth[u] + depth[v] + 1;
                    answer = min(answer, cycle_len);
                }
            }
        }
    }

    if(answer == INF){
        cout << -1 << endl;
    } else {
        cout << answer << endl;
    }
    return 0;
}