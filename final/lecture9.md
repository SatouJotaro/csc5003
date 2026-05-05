| 题目                 | DP类型       | 关键状态设计                |
| ------------------ | ---------- | --------------------- |
| Tallest Billboard  | 差值DP       | dp[差值] = 较矮侧最大高度      |
| Hats               | Bitmask DP | dp[帽子][人的mask] = 方案数  |
| Profitable Schemes | 计数背包       | dp[人数][利润(截断)] = 方案数  |
| Longest Path       | 树形DP       | DFS返回最长下行链，合并两子链      |
| Color in Graph     | DAG DP（拓扑） | dp[节点][颜色] = 最大出现次数   |
| Remove Boxes       | 三维区间DP     | dp[l][r][k]，k为右侧附带同色数 |

## 1. Tallest Billboard（最高广告牌）
问题：将若干根杆子分成三组（左支撑、右支撑、不用），使两组总高度相等，求最大高度。

核心技巧：差值DP

不直接追踪两侧高度（二维状态太笨重），而是只跟踪两侧的高度差 d。

dp[d] = 当两支撑差值为 d 时，较矮那侧的最大高度。

对每根杆子 x，三种转移：

不用：new_dp[d] = max(new_dp[d], dp[d])

加到较高侧：new_dp[d+x] = max(new_dp[d+x], dp[d])

加到较矮侧：new_dp[abs(d-x)] = max(..., dp[d] + min(d, x))

答案：dp[0]（差值为0时较矮侧的最大高度，即两侧等高）


## 2. Number of Ways to Wear Different Hats（帽子分配方案数）
问题：n 个人，每人有喜欢的帽子列表，每人分配一顶不同的喜欢的帽子，求方案数 mod 10^9 + 7

核心技巧：Bitmask DP（枚举帽子而非人）
因为人数少（最多10人），用 bitmask 表示哪些人已分配。

dp[h][mask] = 考虑帽子 1..h，且已分配人的集合为 mask 的方案数。

转移：

不用帽子 h：dp[h][mask] += dp[h-1][mask]

把帽子 h 给某个喜欢它的人 p：dp[h][mask] += dp[h-1][mask ^ (1<<p)]（前提是 p 在 mask 中且 p 喜欢帽子 h）

为什么枚举帽子而非人？ 帽子数量（最多40）远多于人数，bitmask 只能压缩小维度（人），所以以帽子为主循环更合适。

## 3. Profitable Schemes（盈利方案数）
问题：n 个团伙成员，k 种犯罪各需若干人、有若干利润，求成员数 ≤ n 且利润 ≥ minProfit 的子集方案数。

核心技巧：计数背包 DP（带利润下界的0/1背包）

dp[j][p] = 恰好用 j 个成员且利润至少为 p 的方案数。

关键：利润上限截断到 minProfit（超过 minProfit 的利润等价处理），避免状态爆炸。

转移（对每个犯罪，成员数 g，利润 pr）：

dp[j][min(p+pr, minProfit)]+=dp[j−g][p]

## 4. Longest Path With Different Adjacent Characters（树上最长交替路径）
问题：树的每个节点有字符，求相邻节点字符不同的最长路径长度。

核心技巧：树形DP（后序DFS）

对节点 u，dfs(u) 返回从 u 出发向下的最长合法链长度。

对每个子节点 v：若 s[v] != s[u]，则贡献为 dfs(v) + 1；否则贡献为 0（不能延伸）。

合并两条链：

取最大两个子贡献 best1、best2，过 u 的路径长 = 1 + best1 + best2

全局答案 ans = max(ans, 1 + best1 + best2)

每个节点返回 1 + best1（只能沿一侧向上延伸）

## 5. Largest Color Value in a Directed Graph（有向图最大颜色值）
问题：有向图每节点有颜色，路径的颜色值 = 该路径上出现最多的颜色次数，返回所有路径中最大的颜色值；若有环则返回 -1。

核心技巧：DAG DP（拓扑排序）

先检测环（若有环返回 -1）。

按拓扑序处理，维护 dp[u][c] = 以 u 结尾的路径中颜色 c 出现的最大次数。

转移（对边 u → v）：

dp[v][c]=max(dp[v][c], dp[u][c]+1[color[v]=c])