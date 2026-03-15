#include<bits/stdc++.h>

using namespace std;

struct Node{
    int val;
    int left;
    int right;
};

const int MAXN = 100005; 
Node nodes[MAXN]; // 开全局变量 dfs要用
int n, targetSum; // 拉过来全局变量，dfs要用
long long result = 0;
unordered_map<long long, int> prefixCount; // 开个哈希表存前缀和

void dfs(int idx, long long curSum){ // dfs需要当前在哪个节点的索引，和当前路径和
    if(idx == -1) return; // 根节点 返回

    curSum += nodes[idx].val; // 把当前节点的值加到路径和上

    long long need = curSum - (long long)targetSum; // 还差多少
    if(prefixCount.count(need)){ // 数一下出现过多少次
        result += prefixCount[need]; // 次数加到结果里
    }

    prefixCount[curSum]++; // 准备回溯，prefixCount存的是路径和

    dfs(nodes[idx].left, curSum);  // 当前这个节点的左子节点，和当前这个节点的路径和
    dfs(nodes[idx].right, curSum);

    prefixCount[curSum]--;
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> nodes[i].val >> nodes[i].left >> nodes[i].right; // 数组存
    }
    cin >> targetSum;

    if(n == 0) {cout << 0 << endl; return 0;}
    
    prefixCount[0] = 1; // 空路径和为0，出现1次
    dfs(0, 0); // 0节点， 路径和为0
    cout << result << endl;
    return 0;
}