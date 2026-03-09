#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    if(!(cin >> n )) return 0;

    vector<vector<int>> revAdj(n);
    vector<int> outDeg(n, 0);

    for(int i = 0; i < n; ++i){
        int d;
        cin >> d;
        outDeg[i] = d;
        for(int k = 0; k < d; ++k){
            int v;
            cin >> v;
            revAdj[v].push_back(i);
        }
    }

    queue<int> q;
    for(int i = 0; i < n; ++i){
        if(outDeg[i] == 0) q.push(i);
    }
    vector<char> isSafe(n, 0);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        isSafe[v] = 1;
        for(int u : revAdj[v]){
            outDeg[u]--;
            if(outDeg[u] == 0){
                q.push(u);
            }
        }
    }

    vector<int> ans;
    for(int i = 0; i < n; ++i){
        if(isSafe[i]) ans.push_back(i);
    }

    cout << ans.size() << "\n";
    if(!ans.empty()){
        for(size_t i = 0; i < ans.size(); ++i){
            if (i) cout << ' ';
            cout << ans[i];
        }
    }
    cout << "\n";
    return 0;
}