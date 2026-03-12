#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

pair<int, int> bfs(int start, int n, const vector<vector<int>>& adj){
    vector<int> dist(n + 1, -1);

    // 1. 为什么 dist 要开 n + 1？
    // 这主要是为了“下标对齐”，避免代码逻辑混乱。
    // 题目中的节点通常编号是从 1 到 n。
    // 如果我们只开 n 个空间，数组下标范围是 0 到 n-1。这时候你去访问第 n 号节点，就会发生下标越界。
    // 开 n+1，我们就可以直接使用 dist[1] 到 dist[n]，省去了要把所有编号减去 1 的麻烦，代码也更清晰，完全不用担心“编号与下标不匹配”的问题。多浪费这一个 int 的内存（4字节）在现代计算机看来是非常划算的。

    queue<int> q;

    q.push(start);
    dist[start] = 0;

    // 2. 为什么是 q.push(start) 而不是 push_back？
    // 这是 std::queue 这个容器的定义决定的。
    // vector 是一个“数组”，它有很多位置，所以添加元素时，明确要在“后面”加，所以叫 push_back。
    // queue 是一个“队列（先进先出）”。根据队列的定义，你只能在队尾加入（Push），只能在队头取出（Front）。
    // 在 C++ 标准库中，为了保持接口统一和语义明确，队列的添加操作就规定叫 push，它默认就是向队尾添加。

    int farthestNode = start;
    int maxDist = 0;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        // 3. 取出元素为什么一定要 pop？
        // 这是因为 front() 和 pop() 的职能完全不同：
        // front()：它的作用仅仅是“看一眼”队头是什么。它不会把你手里的球（元素）拿走，它只会让你看到上面的数字。
        // pop()：它的作用是“把队头扔掉”。将这个元素从队列中移除，这样队列的下一个元素才会变成新的队头。
        // 为什么要连用？
        // 如果你只 front() 不 pop()，你永远在处理同一个点，程序会陷入死循环。
        // 形象理解：你正在排队买票。front() 是看到排在最前面的人是谁，pop() 是买完票的人离开队伍。如果你不把买完票的人“踢出去”，他会永远挡在队伍最前面，后面的人就永远买不到票了。
    
        if(dist[u] > maxDist){
            maxDist = dist[u];
            farthestNode = u;
        }

        for(int v : adj[u]){
            if(dist[v] == - 1){
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }

    }
    // 4. 出队/入队的是什么？怎么更新到最远端？
    // 这是 BFS 的核心逻辑，我们分步骤看：
    // 出队入队的是什么？
        // 入队 (Push)：放入的是“待处理的节点编号”。
        // 出队 (Pop)：取出的是“当前正在探索的起点”，我们会以这个点为中心，向它的“邻居”扩散。
    // 它是怎么实现更新到最远端的？
        // 这依赖于 dist 数组的传递性：
        // 初始状态：dist[start] = 0，其他都是 -1。
    // 扩散规则：
        // 当我们从 u 移动到邻居 v 时，如果 v 未被访问过（即 dist[v] == -1），我们就令 dist[v] = dist[u] + 1。
        // 这一步是核心：它保证了每一个点记录的距离都是从 start 到该点的最短路。
    // 寻找最远：
        // 在每一次 q.pop() 取出节点 u 时，我们都检查一下：dist[u] 是不是比我们目前找到的 maxDist 还要大？
        // 如果是，就更新 maxDist = dist[u]，并记住 farthestNode = u。
    // 最后结果：
        // 当队列为空，说明能走的点都走完了。此时 maxDist 记录的一定是所有点中距离最远的数值，而 farthestNode 就是那个最远点的编号。
    // 总结一下： 你把队列想象成一滴墨水在纸上晕开。
        // q 控制着墨水晕开的进度。
        // 你每走到一个点，都在纸上写下离起点的距离。
        // 由于 BFS 是层层扩散的，你最后写下的那个距离最大的点，一定就是离起点最远的点。
    
    return {farthestNode, maxDist};
}

int main(){
    int n; cin >> n;
    
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < n - 1; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    pair<int, int> p1 = bfs(1, n, adj);

    pair<int, int> p2 = bfs(p1.first, n, adj);

    cout << p2.second << endl;
    return 0;
}