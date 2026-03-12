#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int INF = 1e9;

int main(){
    int n, m;
    cin >> n >> m; // n 是顶点数量，m 是边数量

    vector<vector<int>> adj(n);
    for(int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int min_cycle = INF;

    vector<int> dist(n);
    vector<int> parent(n);

    for(int i = 0; i < n; i++){
        fill(dist.begin(), dist.end(), -1);
        fill(parent.begin(), parent.end(), -1);

        queue<int> q;
        dist[i] = 0;
        q.push(i);

        while(!q.empty()){
            int u = q.front(); q.pop();

            for(int v : adj[u]){
                // 情况1：v 未被访问，正常入队
                if(dist[v] == -1){
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                } 
                // 情况2：v 已访问且不是父节点，发现环
                else if(v != parent[u]){
                    min_cycle = min(min_cycle, dist[u] + dist[v] + 1);
                }
            }
        }
    }

    if(min_cycle == INF) cout << -1 << endl;
    else cout << min_cycle << endl;
    return 0;
}