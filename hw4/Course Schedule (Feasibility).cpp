#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n); // 邻接表：adj[b] 存 b 的后继课程
    vector<int> indegree(n, 0); // 入度数组

    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        // b -> a（先修b才能学a）
        adj[b].push_back(a);
        indegree[a]++;
    }

    // 将所有入度为0的课程入队
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(indegree[i] == 0){
            q.push(i);
        }
    }

    int count = 0; // 已能学完的课程数
    while(!q.empty()){
        int node = q.front();
        q.pop();
        count++;

        // 学完node后，其后继课程入度-1
        for(int next : adj[node]){
            indegree[next]--;
            if(indegree[next] == 0){
                q.push(next);
            }
        }
    }

    cout << (count == n ? "YES" : "NO" )  << endl;
    return 0;
}