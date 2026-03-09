#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n;
    long long expressCost;
    cin >> n >> expressCost;

    vector<long long> regular(n);
    vector<long long> express(n);

    for(int i = 0; i < n; i++){
        cin >> regular[i];
    }
    for(int i = 0; i < n; i++){
        cin >> express[i];
    }


    long long dp_reg_prev = 0;
    long long dp_exp_prev = expressCost;
    vector<long long> costs(n);

    for(int i = 1; i <= n; i++){
        long long dp_reg_curr = min(dp_reg_prev, dp_exp_prev) + regular[i-1];
        long long dp_exp_curr = min(dp_exp_prev, dp_reg_prev + expressCost) + express[i-1] ;
        costs[i-1] = min(dp_reg_curr, dp_exp_curr);

        dp_reg_prev = dp_reg_curr;
        dp_exp_prev = dp_exp_curr;
    }

    for(int i = 0; i < n; i++){
        if(i > 0) cout << " ";
        cout << costs[i];
    }
    cout << endl;
    return 0;
}