#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> edges(n);
    for(int i = 0; i < n; i++){
        cin >> edges[i];
    }

    vector<bool> visited(n, false);
    vector<int> visit_time(n, 0);
    int current_time = 1;
    int max_cycle = -1;

    for(int i = 0; i < n; i++){
        if(visited[i]) continue;
        int start_time = current_time;
        int node = i;
        while(node != -1 && !visited[node]){
            visited[node] = true;
            visit_time[node] = current_time;
            current_time++;
            node = edges[node];
        }
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