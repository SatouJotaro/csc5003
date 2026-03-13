#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    
    vector<vector<int>> routes(n);               // 存储每条线路包含的站点
    unordered_map<int, vector<int>> stop2routes; // 存储每个站点属于哪些线路
    int maxStop = 0;

    for(int i = 0; i < n; ++i){
        int k; cin >> k;
        routes[i].resize(k);
        for(int j = 0; j < k; ++j){
            cin >> routes[i][j];
            stop2routes[routes[i][j]].push_back(i); // 记录“该站点在哪些线路中出现”
            maxStop = max(maxStop, routes[i][j]);
        }
    }

    int source, target; cin >> source >> target;

    if(source == target) { cout << 0 << endl; return 0;}
    // 如果起点不在任何线路里，或者终点不在任何线路里（且不等），肯定不可达
    if(stop2routes.count(source) == 0 || stop2routes.count(target) == 0) { cout << -1 << endl; return 0;}

    // 2. BFS 初始化
    queue<int> q; // 只存“线路编号”
    vector<int> dist(n, -1); // 记录每条线路距离起点的距离（乘坐了几辆车）
    vector<bool> visited(maxStop + 1, false); // 防止站点重复处理
    
    // 把包含起点的所有线路加入队列
    for(int start : stop2routes[source]){
        dist[start] = 1;
        q.push(start);
    }

    // 3. 开始 BFS
    // 你现在在第 curr 条公交车上。
    // 只要你在这辆车上，你就可以在该线路的所有站点下车。
    // 一旦你在某个站点下车，你就可以立刻换乘所有经过该站点的“其他公交车”。
    while(!q.empty()){
        int curr = q.front(); q.pop();

        // 1. 检查：这一条线路里是否包含终点？包含就直接结束
        // 如果包含，说明我们已经在目标线路上，直接输出当前次数
        for(int stop : routes[curr]){
            if(stop == target) { cout << dist[curr] << endl; return 0;}
        }

        // 2. 换乘：遍历该线路所有站点，看看能跳到哪儿
        for(int stop : routes[curr]){  
            if(visited[stop]) continue; // 这一站已经作为“中转站”用过了，跳过
            visited[stop] = true;       // 标记该站点已用过

            // 看看经过这一站的其他公交车
            for(int next : stop2routes[stop]){
                // 如果这辆车/线路没坐过
                if(dist[next] == -1){
                    dist[next] = dist[curr] + 1;
                    q.push(next);
                }
            }
        }
    }

    cout << -1 << "\n";
    return 0;
}

// 为什么这样写最顺畅？（逻辑拆解）
// 第一步（检查目标）：你坐在第 r 辆车上。这辆车上是否有你要去的 target？如果有，不需要再换乘了，直接下车，结束。
// 第二步（寻找换乘）：如果你还没到达目标，说明你要找下一个中转站。只要是这辆车上的站点，你都可以下车，并换乘所有经过该站点的其他车辆 next_r。
// 第三步（去重）：visited_stop 是关键。因为一个站点可能被几十条线路同时经过，如果不加这个标记，你会在同一个站点反复把那几十条线路 push 进队列，导致死循环或性能爆炸。一旦这个站点处理过了，就不需要再处理它了。
// 这个版本的优点：
// 无需预处理：删掉了 routeHasTarget 数组，代码直接在 BFS 过程中找 target，省去了代码量。
// 逻辑分明：先看能不能直接到（检查），不能到再想办法换乘（跳车）。
// 一眼看懂：完全对应现实生活中的坐车逻辑：上车 -> 看看是不是终点站 -> 不是就找换乘站 -> 换乘下一辆车。