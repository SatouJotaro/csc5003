// 给 n 个气球，戳破第 i 个气球得 左邻 × nums[i] × 右邻 的金币（边界当1），戳破后左右相邻重新接上，求戳完所有气球能得到的最大金币数
// 不想"先戳哪个"，而是想**"区间内最后戳哪个"** 。

// 在两端加虚拟气球 1，令 arr = [1, nums..., 1]，定义 dp[l][r] = 戳完开区间 (l, r) 内所有气球的最大金币。枚举最后一个被戳的气球 k：
// dp[l][r]= max(dp[l][k]+dp[k][r]+arr[l]×arr[k]×arr[r])
// l<k<r
// 因为 k 最后被戳时，左邻一定是 l，右邻一定是 r，邻居不会变

#include<bits/stdc++.h>
using namespace std;

int n;
int arr[305];      // 加了两端虚拟气球的数组
int dp[305][305];  // dp[l][r]: 开区间(l,r)内所有气球最大金币

int solve(int l, int r){
    if( r - l < 2 ) return 0;  // 区间内没有气球
    if(dp[l][r] != -1) return dp[l][r];  // 记忆化

    dp[l][r] = 0;
    // 枚举最后被戳的气球k
    for(int k = l + 1; k < r; k++){  
        int coins = arr[l] * arr[k] * arr[r]
                    + solve(l, k) 
                    + solve(k, r);
        dp[l][r] = max(dp[l][r] , coins);
    }
    return dp[l][r];
}

int main(){
    cin >> n;
    arr[0] = 1;   // 左虚拟气球
    for(int i = 1; i <= n; i++) cin >> arr[i];
    arr[n+1] = 1; // 右虚拟气球

    // memset(dp, -1, sizeof(dp))，用 -1 表示未算过，比迭代写法更不容易出错
    memset(dp, -1, sizeof(dp));

    cout << solve(0, n + 1) << endl;
    return 0;
}

// memset = memory set，中文意思是"设置内存" 。它是一个批量初始化函数，能快速把一整块数组的每个字节都设成某个值
// memset(数组名, 填充值, 字节大小);

// memset(dp, -1, sizeof(dp));
// // 把 dp 数组的每一个字节都填成 -1
// // sizeof(dp) 自动算出数组占多少字节，不用手动算

// 为什么 -1 可以用 memset 填？因为 -1 的二进制是全1（0xFF），每个字节都是 0xFF，4个字节组合成 int 还是 -1，完全正确
// ⚠️ 注意：memset(dp, 1, sizeof(dp)) 不会把每个 int 填成 1，而是填成 0x01010101 = 16843009，因为它是按字节填的！只有 0 和 -1 是安全的



// if (dp[l][r] != -1) return dp[l][r];  // 记忆化
// 如果 dp[l][r] 不是 -1，说明这个子问题之前已经算过了，直接返回已有答案，不用重复计算
// 为什么叫"记忆化"：就像你做过一道数学题，下次再遇到同样的题直接看答案，不重新算。计算机把"做过的题的答案"记在 dp 表里，下次查表即可
// 没有记忆化的话，同样的 solve(l, r) 会被重复调用无数次，时间复杂度爆炸



// dp[l][r] = max(dp[l][r], coins) 是什么意思
// 这是在 for 循环里对 k 取最大值的写法。代码结构是这样的：
// dp[l][r] = 0;                         // 先初始化为0（最差情况）
// for (int k = l + 1; k < r; k++) {     // 枚举每个可能的"最后气球"
//     int coins = arr[l]*arr[k]*arr[r] + solve(l,k) + solve(k,r);
//     dp[l][r] = max(dp[l][r], coins);  // 每次循环保留最大的
// }
// 不是怕乘出来比0小（气球值都 ≥ 0，不会是负数），而是：
// 每次循环算出一个候选值 coins，始终保留历史最大值
// 等 for 循环跑完，dp[l][r] 就是所有 k 中最好的方案

// solve(l, k) 里 dp[l][r] 会不会被改变？
// 不会！ 原因如下：

// solve(l, k) 计算的是区间 (l, k) 的结果，它只会修改 dp[l][k]。
// solve(k, r) 计算的是区间 (k, r) 的结果，它只会修改 dp[k][r]。

// dp[l][r] 只在 solve(l, r) 函数内部被修改，而 solve(l, k) 和 solve(k, r) 是更小的区间，永远不会去碰 dp[l][r]

// solve(0, 5) 正在计算 dp[0][5]
//   └── 调用 solve(0, 3) → 只修改 dp[0][3]，完全不碰 dp[0][5]
//   └── 调用 solve(3, 5) → 只修改 dp[3][5]，完全不碰 dp[0][5]
// 所以 dp[l][r] 在整个 for 循环过程中是安全的，只被当前 solve(l, r) 自己累积更新