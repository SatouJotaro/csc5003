#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int diameter = 0;

int dfs(int u, int p, const vector<vector<int>>& adj){
    int d1 = 0, d2 = 0;

    for(int v : adj[u]){
        if(v == p) continue;

        int d = dfs(v, u, adj) + 1;

        if(d > d1){
            d2 = d1;
            d1 = d;
        }
        else if(d > d2) d2 = d;
    }
    diameter = max(diameter, d1 + d2);
    return d1;
}
int main(){
    int n;
    if(!(cin >> n)) return 0;
    if(n == 1){
        cout << 0 << endl;
        return 0;
    }

    vector<vector<int>> adj(n+1);
    for(int i = 0; i < n - 1; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1, adj);
    cout << diameter << endl;
    return 0;
}