#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
    string S, P;
    cin >> S >> P;

    int n = S.length();
    int m = P.length();

    // 1. 计算 pi 数组
    // 为了方便，这里采用 1-based indexing 逻辑的数组大小
    vector<int> pi(m + 1, 0);
    for(int i = 2, j = 0; i <= m; i++){
        while(j > 0 && P[j] != P[i - 1]) j = pi[j];
        if(P[j] == P[i - 1]) j++;
        pi[i] = j;
    }

    for(int i = 0, j = 0; i < n; i++){
        while(j > 0 && P[j] != S[i]) j = pi[j];
        if(P[j] == S[i]) j++;
        if(j == m){
            cout << i - m + 2 << "\n";
            j = pi[j];
        }
    }

    for(int i = 1; i <= m; i++){
        cout << pi[i] << (i == m ? "" : " ");
    }
    cout << endl;
    return 0;
}