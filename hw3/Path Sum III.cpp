#include<bits/stdc++.h>
using namespace std;

struct Node{
    int val, left, right;
};

const int MAXN = 100005;
Node nodes[MAXN];
int n, targetSum;
long long result = 0;
unordered_map<long long, int> prefixCount;

void dfs(int idx, long long curSum){
    if(idx == -1) return;
    curSum += nodes[idx].val;

    long long need = curSum - (long long)targetSum;
    if(prefixCount.count(need)){ // 检查 need 这个前缀和是否出现过
        result += prefixCount[need];
    }

    prefixCount[curSum]++;

    dfs(nodes[idx].left, curSum);
    dfs(nodes[idx].right, curSum);

    prefixCount[curSum]--;
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> nodes[i].val >> nodes[i].left >> nodes[i].right;
    }
    cin >> targetSum;

    if(n == 0){
        cout << 0 << endl;
        return 0;
    }

    prefixCount[0] = 1;

    dfs(0, 0);

    cout << result << endl;

    return 0;
}