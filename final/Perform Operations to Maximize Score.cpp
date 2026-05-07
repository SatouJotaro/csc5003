#include<bits/stdc++.h> // 包含几乎所有标准库
#define ll long long    // 定义长整型缩写，防止数值溢出（a_i, k均可达1e9）
#define N 200005        // 最大数组长度
#define endl "\n"       // 优化换行符，比 std::endl 快
#define fi first        // pair 的第一个元素 (a_i)
#define se second       // pair 的第二个元素 (b_i)
using namespace std;

const ll mod=1e9+7;
const ll inf=1e18;

ll n, m, p, ans, res, now;
pair<ll, ll> a[N]; // 存储 (数值, 是否可操作)
ll b[N];           // 辅助数组，用于二分判定

// 二分判定函数：判断能否在 m 次操作内，使剩余 n-1 个元素的中位数至少为 x
bool check(ll x) {
    ll cost = 0;   // 已经花费的操作次数
    ll cnt = 0;    // 当前大于等于 x 的元素个数
    // 我们考虑前 n-1 个元素（假设最大元素 a[n] 被选出来作为核心分数值）
    for(int i = n - 1; i >= 1; i--) {
        if(a[i].fi >= x) {
            cnt++; // 原本就大于等于 x，直接计数
        } else if(a[i].se == 1) { // 小于 x 但可以进行 +1 操作
            // 如果剩余步数足够将其提升到 x
            if(cost + (x - a[i].fi) <= m) {
                cost += (x - a[i].fi);
                cnt++;
            }
        }
        // 对于 n-1 个元素，中位数定义为第 floor(n/2) 个大
        // 只要大于等于 x 的数量超过一定比例，x 就是可行的
        if(cnt > (n - 1) / 2) return true; 
    }
    return cnt > (n - 1) / 2;
}

void sol() {
    cin >> n >> m; // n 为元素个数，m 为操作次数 k
    for(int i = 1; i <= n; i++) cin >> a[i].fi; // 读入 a_i
    for(int i = 1; i <= n; i++) cin >> a[i].se; // 读入 b_i
    
    sort(a + 1, a + n + 1); // 按 a[i].fi 从小到大排序，方便求中位数
    
    p = n / 2; // p 对应去掉一个元素后，中位数在排序数组中的大致位置
    res = 0;

    // --- 策略一：全堆在一个可变元素上 ---
    // 遍历每一个 b[i]=1 的位置，将其加满 k
    for(int i = 1; i <= p; i++) {
        if(a[i].se) {
            // 如果去掉的是较小的元素 i <= p，则中位数是原序列第 p+1 个
            res = max(a[i].fi + m + a[p + 1].fi, res);
        }
    }
    for(int i = p + 1; i <= n; i++) {
        if(a[i].se) {
            // 如果去掉的是较大的元素 i > p，则中位数是原序列第 p 个
            res = max(a[i].fi + m + a[p].fi, res);
        }
    }

    // --- 策略二：提升中位数 ---
    // 假设我们选最大的 a[n].fi 作为 a_i，用 m 去提升 a[1...n-1] 的中位数
    ll l = a[p].fi, r = a[p].fi + m; // 中位数的可能范围
    while(l < r) {
        ll mid = (l + r + 1) >> 1; // 二分中位数的值
        if(check(mid)) l = mid;    // 如果能达到 mid，尝试更大的值
        else r = mid - 1;
    }
    
    // 最终答案取两种策略的最大值
    // a[n].fi + l 是策略二的结果
    cout << max(res, a[n].fi + l) << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); // 彻底关闭同步流，加速输入输出
    ll ttt;
    cin >> ttt; // 多组测试数据
    while(ttt--) sol();
    return 0;
}