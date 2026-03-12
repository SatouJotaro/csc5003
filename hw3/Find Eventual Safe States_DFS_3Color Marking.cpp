// B. 深度优先搜索 + 三色标记法 (DFS + Three-Color Marking)
// 使用 DFS 判断图中是否有环（判断节点是否处于环中）：
// 状态标记：
    // 0 (未访问)：该节点还没被处理。
    // 1 (访问中 / Visiting)：该节点正在当前的 DFS 路径中（如果再次遇到该状态，说明触环了）。
    // 2 (安全 / Safe)：该节点已经被确认为安全节点。
// 逻辑：如果一个节点在 DFS 过程中遇到了处于“访问中”状态的祖先节点，则该节点不安全。如果一个节点的所有邻居都能走通（递归返回 True），则该节点被标记为 2（安全）。

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> state;
vector<vector<int>> adj;

bool isSafe(int u){
    if(state[u] != 0) return state[u] == 2; // 该节点已经被确认为安全节点。

    state[u] = 1; // 标记为正在访问
    for(int v : adj[u]){
        // 如果邻居不安全，自己也不安全
        if(!isSafe(v)) return false; 
    }
    state[u] = 2; // 标记为安全
    return true;
}

int main(){
    int n;
    cin >> n;
    adj.resize(n);
    state.assign(n, 0); // 将 vector 的大小重置为 n，并将所有元素初始化为 value

    // 除了填充固定值，assign 还可以用来把另一个容器（或数组）的一段数据直接赋值给当前的 vector。
    // vector<int> v1 = {1, 2, 3};
    // vector<int> v2 = {10, 20};
        // 把 v1 的内容替换成 v2
    // v1.assign(v2.begin(), v2.end()); 
        // 现在 v1 变成了 {10, 20}


    for(int i = 0; i < n; ++i){
        int d;
        cin >> d;
        for(int j = 0; j < d; ++j){
            int v;
            cin >> v;
            adj[i].push_back(v);
        }
    }

    vector<int> result;
    for(int i = 0; i < n; ++i){
        if(isSafe(i)) result.push_back(i);
    }

    cout << result.size() << endl;
    for(int i = 0; i < result.size(); ++i){
        cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}