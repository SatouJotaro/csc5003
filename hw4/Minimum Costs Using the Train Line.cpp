// 我们可以把“转换路线”和“继续前进”这两个动作拆解开来看。
// 只要记住两个状态：
    // reg: 我现在在常规轨道上（哪怕刚切换过来）。
    // exp: 我现在在快速轨道上（哪怕刚切换过来）。

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    int n;
    long long expressCost;
    cin >> n >> expressCost;

    vector<long long> reg_cost(n);
    vector<long long> exp_cost(n);
    for(auto &x : reg_cost) cin >> x;
    for(auto &x : exp_cost) cin >> x;
    
    // dp_reg: 目前在常规线上的最小成本
    // dp_exp: 目前在快速线上的最小成本
    // 初始：第0站出发
    long long dp_reg = 0;
    long long dp_exp = expressCost;

    for(int i = 0; i < n; i++){
        // 先计算“下一站”的情况
        // 到达下一站的常规：选原本的常规 或 快速切常规(免费)
        long long next_reg = min(dp_reg, dp_exp) + reg_cost[i];

        // 到达下一站的快速：选原本的快速 或 常规切快速(收费)
        long long next_exp = min(dp_exp, dp_reg + expressCost) + exp_cost[i];

        // 更新状态供下次循环使用
        dp_reg = next_reg;
        dp_exp = next_exp;

        // 本站最终答案就是两者较小值
        // 在 C++ 中，三元运算符 ? : 的优先级低于 << 输出运算符。
        cout << min(dp_reg, dp_exp) << (i == n - 1 ? "" : " ");
    }

    return 0;
}