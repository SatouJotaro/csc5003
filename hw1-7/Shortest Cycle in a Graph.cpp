// 给定一个无向图，找出其中边数最少的环（最短环长度），若图中无环则输出 -1

// 思路：BFS 枚举起点（最简单）
// 对每个节点做一次 BFS，当 BFS 过程中发现某条边连向**已访问**且**不是当前节点父节点**的节点时，就说明找到了一个环
// 环长 = dist[cur] + dist[next] + 1
// 对所有节点做完 BFS 后取最小值即为答案，n ≤ 1000 完全可行

#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<int> adj[1001];
int ans = INT_MAX;;

void bfs(int src){ // src 是 source（源/起点）的缩写，在这道题的 BFS 函数里，它表示本次 BFS 的出发节点，即"从哪个顶点开始搜索"。
    vector<int> dist(n, -1), pre(n, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while(!q.empty()){
        int cur = q.front(); q.pop();
        for(int next : adj[cur]){
            if(dist[next] == -1){
                dist[next] = dist[cur] + 1;
                pre[next] = cur;
                q.push(next);
            } else if(pre[cur] != next){
                ans = min(ans, dist[cur] + dist[next] + 1);
            }
        }
    }
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 0; i < n; i++){
        bfs(i);
    }
    cout << (ans == INT_MAX ? -1 : ans) << endl;
    return 0;
}

// dist 数组：同时承担"距离"和"是否访问过"
// dist 全部初始化为 -1，含义是"还没访问过这个节点"。 当某个节点被访问时，就记录它到起点的距离（≥0），所以：

// dist[x] == -1 → 未访问过
// dist[x] >= 0 → 已访问，且值就是离起点的边数

// BFS 本身是按层扩展的（一层一层向外），先入队的节点先处理，所以第一次访问到某节点时，走过的边数一定是最短的。 队列就是实现这个"按层扩展"的工具，每次取出队头节点，把它的邻居放入队尾。

// pre 数组：记录父节点，防止"假环"
// 在无向图中，0-1 这条边是双向的，从 0 走到 1，再从 1 看邻居时会看到 0。但 0→1→0 不是环，只是走了个来回。
// pre[cur] 记录的是"cur 是从哪个节点走过来的"，即父节点。

// 当 BFS 从 cur 出发，探索邻居 next 时：
// if (pre[cur] != next)   // 如果 next 不是 cur 的父节点
//     → 说明找到真正的环
// 如果 pre[cur] == next，说明 next 是走来的方向，直接跳过即可。

// 环长公式 dist[cur] + dist[next] + 1
// 当 BFS 发现 cur 和 next 都已访问，且它们之间有一条边时，这意味着从 src 出发，有两条不同路径分别到达 cur 和 next
// 这两条路径加上 cur-next 这条边，就构成了一个环。 环的总长 = src→cur 的距离 + src→next 的距离 + 1条 cur-next 边。