#include<bits/stdc++.h>

using namespace std;

int main(){
    int n; cin >> n;
    vector<int> line;
    line.resize(n);
    for(int i = 0; i < n; i++){
        cin >> line[i];
    }

    vector<int> up(n, 1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            if(line[i] > line[j]){
                up[i] = max(up[i], up[j] + 1);
            }
        }
    }

    // 反向：求以i为起点的最长递减子序列长度
    vector<int> down(n, 1);
    for(int i = n - 2; i >= 0; i--){
        for(int j = n - 1; j > i; j--){
            if(line[i] > line[j]){
                down[i] = max(down[i], down[j] + 1);
            }
        }
    }

    int largest = 0;
    for(int i = 0; i < n; i++){
        largest = max(largest, up[i] + down[i] - 1);
    }

    cout << n - largest << endl;
    return 0;
}