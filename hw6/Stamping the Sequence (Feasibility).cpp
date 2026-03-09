#include<bits/stdc++.h>
using namespace std;

int main(){
    int T;
    cin >> T;

    while(T--){
        string stamp, target;
        cin >> stamp >> target;

        int n = (int)target.size();
        int m = (int)stamp.size();
        string t = target; // 工作字符串，逐步变成???...?

        bool changed= true;
        while(changed){
            changed = false;
            for(int i = 0; i <= n - m; i++){
                bool valid = true;
                bool hasNonQ = false;

                for(int j = 0; j < m; j++){
                    if(t[i+j] == '?') continue;
                    if(t[i+j] != stamp[j]){
                        valid = false;
                        break;
                    }
                    hasNonQ = true;
                }

                if(valid && hasNonQ){
                    for(int j = 0; j < m; j++) t[i+j] = '?';
                    changed = true;
                }
            }
        }

        bool allQ = (t == string(n, '?'));
        cout << (allQ ? "YES" : "NO") << "\n";
    }
    return 0;
}