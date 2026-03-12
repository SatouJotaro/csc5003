#include<iostream>
#include<vector>
using namespace std;

int main(){
    // 一个整数 n，表示节点的总数（0 到 n-1）
    int n;
    cin >> n;
    // 一个数组 edges，其中 edges[i] = v 表示从 i 指向 v
    // 如果 edges[i] == -1，表示该节点没有出边
    vector<int> edges(n);
    for(int i = 0; i < n; i++){
        cin >> edges[i];
    }

    vector<bool> visited(n, false); // 记录节点是否被全局访问过
    vector<int> visit_time(n, 0);   // 记录节点被访问时的“时刻”（用于计算环长）
    int current_time = 1;           // 全局时间戳，每走一步增加 1
    int max_cycle = -1;             // 记录找到的最长环长度

    for(int i = 0; i < n; i++){
        // 如果节点已被访问过，说明它已经归入之前的探测路径中，跳过
        if(visited[i]) continue;
        
        // 记录当前这一轮搜索开始的时间
        int start_time = current_time;
        int node = i;
        
        // 沿着路径探测，直到遇到没出边的点(-1)或遇到已经访问过的点
        while(node != -1 && !visited[node]){
            visited[node] = true;
            visit_time[node] = current_time; // 给该节点打上时间戳
            current_time++;
            node = edges[node];
        }

        // 如果是因为遇到已访问节点而跳出循环，判断是否该节点是在“当前这一轮”访问到的
        // visit_time[node] >= start_time 意味着 node 是在当前轮被遍历到的，而不是之前的
        if(node != -1){
            if(visit_time[node] >= start_time){
                int cycle_len = current_time - visit_time[node];
                if (cycle_len > max_cycle){
                    max_cycle = cycle_len;
                }
            }
        }
    }

    cout << max_cycle <<endl;
    return 0;
}