// 本题要求在给定的 k 次区间加（陨石雨）操作序列中，找出每个国家（拥有多个观测站）累计样本量达到其目标值 pi 的最小操作次数

// 核心方案： 
// 使用 整体二分（Parallel Binary Search） 配合 树状数组（Binary Indexed Tree）
// 这是处理“多个独立询问且具有单调性”的最优逻辑

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 300005;

struct Query{
    int l, r;
    long long a;
} q[MAXN];

// 记录国家的 id（为了最后按顺序输出）和 goal（目标值）
// 精妙之处：在二分过程中，如果一个国家还没达标，我们会更新 goal -= current_samples。
// 这反映了“还需要多少样本”，方便下一层递归直接计算。
struct Nation{
    int id;
    long long goal;
};

int n, m, k;
vector<int> sectors[MAXN];
int ans[MAXN];
long long bit[MAXN];

// 树状数组最底层操作，改变一个点的值
void add(int idx, long long val){
    for(; idx <= m; idx += idx & -idx) bit[idx] += val;
}

// 区间加法
// 利用差分思想：在 l 处加 a，在 r+1 处减 a。
// 这样查询前缀和时，l 到 r 之间的每个点都会加上 a，而 r 之后的部分不受影响。
void range_add(int l, int r, long long a){
    if(l <= r){
        add(l, a); add(r+1, -a);
    }
    else{
        // 环形处理：分为 [l, m] 和 [1, r]
        add(l, a); 
        // add(m + 1, -a); // 因为 idx > m 时 add 会自动停止，所以这行可省
        add(1, a);
        add(r+1, -a);
    }
}

// 返回该扇区当前累计的陨石样本数。
long long query(int idx){
    long long res = 0;
    for(; idx > 0; idx -= idx & -idx) res += bit[idx];
    return res;
}

// 整体二分的主体。它不只针对一个国家，而是针对“一群国家”在“一段时间”内的情况进行裁决。
void solve(int L, int R, vector<Nation>& nations){
    if(nations.empty()) return;
    if(L == R){
        for(auto& ntn : nations) ans[ntn.id] = L;
        return;
    }

    int mid = (L + R) >> 1;

    // 1. 在 BIT 中应用 [L, mid] 时间段的陨石雨
    // 1. 将前 mid 个操作应用到树状数组
    for(int i = L; i <= mid; i++) range_add(q[i].l, q[i].r, q[i].a);

    vector<Nation> left, right;
    for(auto& ntn : nations){
        long long cnt = 0;
        for(int s : sectors[ntn.id]){
            cnt += query(s);
            if(cnt >= ntn.goal) break; // 防止溢出，提前跳出
        }

        if(cnt >= ntn.goal){
            left.push_back(ntn);
        } else{
            ntn.goal -= cnt; // 减去已获得的，去右边找剩下的
            right.push_back(ntn);
        }
    }

    // 2. 还原 BIT (回溯)，保证分治各层独立
    for(int i = L; i <= mid; i++) range_add(q[i].l, q[i].r, -q[i].a);

    solve(L, mid, left);
    solve(mid+1, R, right);
}
int main(){
    if(!(cin >> n >> m)) return 0;

    // 读入每个扇区属于哪个国家
    for(int i = 1; i <= m; i++){
        int owner;
        cin >> owner;
        sectors[owner].push_back(i);
    }

    // 读入各国的目标
    vector<Nation> nations(n);
    for(int i = 0; i < n; i++){
        nations[i].id = i + 1;
        cin >> nations[i].goal;
    }

    // 读入陨石雨预报
    cin >> k;
    for(int i = 1; i <= k; i++){
        cin >> q[i].l >> q[i].r >> q[i].a;
    }

    // 整体二分：范围是 1 到 k+1 (k+1 代表 NIE 情况)
    solve(1, k + 1, nations);

    // 输出结果
    for(int i = 1; i <= n; i++){
        if(ans[i] <= k) cout << ans[i] << "\n";
        else cout << "NIE\n";
    }

    return 0;
}


// 1. for (; idx <= m; ...) 的语法
// 在 C++ 中，for 循环的标准格式是 for (初始化; 条件; 更新)。
// 这里的第一个分号前面是空的，表示**“不需要在循环开始时初始化变量”**。
// 因为 idx 是通过函数参数直接传入的，已经有初始值了，所以不需要重新定义。这是一种简洁的写法。
// 2. 二进制的应用
// 是的，这确实在利用二进制特性。
// idx & -idx 是计算机组成原理中的 Lowbit 运算。它能提取出一个整数在二进制下“最低位的 1”。
// 例如：
// 6 的二进制是 (110) 
// −6 的补码是 (...010)
// 两者相与得到 (10)=2
// 树状数组正是利用这种二进制长度来决定管理哪些区间的和。


// 1. 什么是树状数组 (Binary Indexed Tree)？
// 它是一个节省空间且更新极快的求和工具。
// 用途：解决“动态修改数组，同时又要快速查询区间和”的问题。
// 为什么用它：
// 直接用数组：修改 O(1)，求和 O(n) —— 太慢。
// 用前缀和数组：求和 O(1)，修改 O(n) —— 太慢。
// 树状数组：修改 O(logn)，求和 O(logn) —— 完美平衡。
// 2. 基本操作
// add(idx, val) (点更新)：将第 idx 个位置加上 val，并向上更新受影响的二进制节点。
// query(idx) (前缀和查询)：计算从 1 到 idx 的所有数值之和。

