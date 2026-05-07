// 判断机器人在有“底部障碍物”（每列高度为a[i]）的网格中，能否以固定步长 k 从起点跳转到终点而不越界或碰撞
// 输入输出：输入网格大小、每列障碍高度及多组查询（起点、终点、步长）；输出每一组是否可达（YES/NO）

// 针对区间最值查询 (RMQ)，ST 表是逻辑最简单且运行效率最高的做法。
// 它能在 O(mlogm) 时间内预处理，并以 O(1) 时间完成每次查询。
// ST 表的循环嵌套比线段树的递归结构更简洁，不容易出错，非常适合考试。
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXM = 200005;
const int LOGM = 19; // 2^18 < 200000 < 2^19
int st[MAXM][LOGM];
int lg2[MAXM];

// 预处理 log2 表，避免使用 log() 函数
void precompute_logs(int m){
    lg2[1] = 0;
    for(int i = 2; i <= m; i++){
        lg2[i] = lg2[i / 2] + 1;
    }
}

// 查询区间 [l, r] 的最大值
int query_max(int l, int r){
    if(l > r) swap(l, r);
    int j = lg2[r-l+1];
    return max(st[l][j], st[r - (1 << j) + 1][j]);
}

int main(){
    int n, m; cin >> n >> m;
    for(int i = 1; i <= m; i++){
        cin >> st[i][0];
    }

    // 构建 ST 表
    precompute_logs(m);
    for(int j = 1; j < LOGM; j++){
        for(int i = 1; i + (1 << j) - 1 <= m; i++){
            st[i][j] = max(st[i][j-1], st[i+(1 << (j-1))][j-1]);
        }
    }

    int q; cin >> q;
    while(q--){
        int xs, ys, xf, yf, k;
        cin >> xs >> ys >> xf >> yf >> k;

        // 1. 检查步长是否匹配
        if(abs(xs - xf) % k != 0 || abs(ys - yf) % k != 0){
            cout << "NO\n";
            continue;
        }
        // 2. 计算机器人能跳到的最高有效行
        int max_h = xs + (n - xs) / k * k;
        // 3. 检查区间内障碍物最大值是否小于该高度
        if(query_max(ys, yf) < max_h){
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}

