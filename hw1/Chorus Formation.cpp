#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> line(n);
    for(int i = 0; i < n; i++){
        cin >> line[i];
    }
    
    vector<int> f(n, 1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            if(line[i] > line[j]){
                f[i] = max(f[i], f[j] + 1);
            }
        }
    }

    vector<int> g(n, 1);
    for(int i = n - 1; i >= 0; i--){
        for(int j = n - 1; j > i; j--){
            if(line[i] > line[j]){
                g[i] = max(g[i], g[j] + 1);
            }
        }
    }
    
    int max_k = 0;
    for(int i = 0; i < n; i++){
        max_k = max(max_k,f[i] + g[i] - 1);
    }

    cout << n - max_k << endl;
    return 0;
}