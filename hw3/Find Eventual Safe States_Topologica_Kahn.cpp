// A. 拓扑排序 (Topological Sort / Kahn's Algorithm)
// 这是本题最优雅的解法：
// 反转图：我们将原图中的所有边方向取反（即如果原图有 i→j，现在改为 j→i）。
// 计算入度：在反转后的图中，计算每个节点的入度。
// 拓扑排序：
    // 将所有出度为 0（反转后入度为 0）的节点加入队列。
    // 不断取出节点，将其加入结果集，并减少其邻居的入度。
    // 如果某邻居入度变为 0，则加入队列。
// 结论：最终被处理过的所有节点即为安全节点。因为在反转图中，无法到达任何节点的本质就是不参与环的逻辑。

#include<bits/stdc++.h>

using namespace std;

int main(){
    int n; cin >> n;
    vector<vector<int>> rev_graph(n);
    vector<int> outdegree(n);

    for(int u = 0; u < n; u++){
        int d; cin >> d;
        outdegree[u] = d;
        for(int i = 0; i < d; i++){
            int v; cin >> v;
            rev_graph[v].push_back(u);
        }
    }

    queue<int> q;
    for(int i = 0; i < n; i++){
        if(outdegree[i] == 0){
            q.push(i);
        }
    }

    vector<int> safe_node;
    while(!q.empty()){
        int node = q.front(); q.pop();
        safe_node.push_back(node);

        for(auto u : rev_graph[node]){
            outdegree[u]--;
            if(outdegree[u] == 0){
                q.push(u);

            }
        }
    }

    sort(safe_node.begin(), safe_node.end());
    cout << safe_node.size() << endl;
    for(int i = 0; i < safe_node.size(); i++){
        cout << safe_node[i] << " ";
    }
    cout << endl;
    return 0;
}

// 将所有出度为 0 的节点（终端节点）放入队列
// ↓
// 每次从队列中取出一个节点 v（它已确认是安全的）
// ↓
// 找到反向图中 v 的所有邻居 u（即原图中所有"指向 v"的节点）
// ↓
// 将 u 的入度减 1（相当于"移除"了 u->v 这条边）
// ↓
// 如果 u 的入度变为 0（u 的所有出边都已被处理），说明 u 也是安全的
// ↓
// 将 u 加入队列，继续处理