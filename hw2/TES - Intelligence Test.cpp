#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;

    int MAXN = 1e6;
    vector<vector<int>> pos(MAXN+1);

    for(int i = 0; i < n; i++){
        int x; cin >> x;
        pos[x].push_back(i);
    }

    int q; cin >> q;
    while(q--){
        int m; cin >> m;
        vector<int> b(m);
        for(int i = 0; i < m; i++){
            cin >> b[i]; 
        } // 输入是输入 对输入完的子串再做循环

        int cur = -1;
        bool ok = true;

        for(int i = 0; i < m; i++){
            int x = b[i];
            const vector<int>& vec = pos[x];

            if(vec.empty()){
                ok = false;
                break;
            }

            auto it = lower_bound(vec.begin(), vec.end(), cur+1);

            if(it == vec.end()){ // 如果指针跑到vec最后面了 == 没找到
                ok = false;
                break;
            }
            else{
                cur = *it; // 更新cur的值
            }
        }
        cout << (ok ? "TAK" : "NIE" ) << endl; 
    }

    return 0;
}