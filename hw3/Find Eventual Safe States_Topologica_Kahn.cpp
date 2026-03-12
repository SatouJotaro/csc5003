// A. 拓扑排序 (Topological Sort / Kahn's Algorithm)
// 这是本题最优雅的解法：
// 反转图：我们将原图中的所有边方向取反（即如果原图有 i→j，现在改为 j→i）。
// 计算入度：在反转后的图中，计算每个节点的入度。
// 拓扑排序：
    // 将所有出度为 0（反转后入度为 0）的节点加入队列。
    // 不断取出节点，将其加入结果集，并减少其邻居的入度。
    // 如果某邻居入度变为 0，则加入队列。
// 结论：最终被处理过的所有节点即为安全节点。因为在反转图中，无法到达任何节点的本质就是不参与环的逻辑。

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int main(){
    int n;
    if(!(cin >> n)) return 0;

    vector<vector<int>> rev_graph(n);   // 反向图
    vector<int> out_degree(n, 0);       // 原图的出度
    vector<int> in_degree(n, 0);        // 反向图的入度

    for(int i = 0; i < n; ++i){
        int d;
        cin >> d;
        out_degree[i] = d;
        for(int j = 0; j < d; ++j){
            int v;
            cin >> v;
            rev_graph[v].push_back(i);  // 边反向
            in_degree[i]++;             // 对应反向图的入度增加
        }
    }

    queue<int> q;
    for(int i = 0; i < n; ++i){
        if(out_degree[i] == 0) q.push(i); // 将原图中所有终端节点入队
    }

    vector<int> safe_nodes;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        safe_nodes.push_back(v);

        for(int u : rev_graph[v]){
            if(--in_degree[u] == 0){ // 它先将 in_degree[u] 减 1，然后再判断减完之后是否等于 0。
                q.push(u);
            }
        }
    }

    sort(safe_nodes.begin(), safe_nodes.end());
    cout << safe_nodes.size() << endl;
    for(int i = 0; i < safe_nodes.size(); ++i){
        // 如果 i 是最后一个元素，就输出空字符串（即什么都不加）
        // 否则输出一个空格
        cout << safe_nodes[i] << ( i == safe_nodes.size() - 1 ? "" : " ");
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