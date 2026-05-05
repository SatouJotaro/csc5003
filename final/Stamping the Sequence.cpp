// 这道题本质上是 LeetCode 936 的判断版本（只判断 YES/NO，不需要输出操作序列）。用反向贪心即可

// 给定 stamp 和 target，初始字符串全是 ?，每次可以把 stamp 盖在某个位置（覆盖原字符），问能否在 10 * |target| 次操作内得到 target
// 输入：T 组测试，每组两行 stamp 和 target
// 输出：每组一行 YES 或 NO

// 核心思路：反向模拟（逆向贪心）
// 正向思维很难（不知道盖的顺序），但反向思考很直观：

// 把 target 逆向还原成全 ?：每次在 target 中找一个位置，使得 stamp 与该位置完全匹配（或 target 对应位置已经是 ?，视为通配），且至少有一个字符不是 ?（即本次消除有效）
// 找到后把那段替换成 ?
// 不断重复，直到全为 ?（YES）或无法继续（NO）

#include<bits/stdc++.h>
using namespace std;

bool canErase(const string& stamp, string& target, int i){
    int slen = stamp.size();
    bool hasReal = false;
    for(int j = 0; j < slen; j++){
        if(target[i+j] == '?') continue;
        if(target[i+j] != stamp[j]) return false;
        hasReal = true;
    }
    return hasReal;  // 至少一个有效字符被消除
}
int main(){
    int T; cin >> T;
    while(T--){
        string stamp, target;
        cin >> stamp >> target;
        int tlen = target.size(), slen = stamp.size();
        int maxMoves = 10 * tlen;
        int moves = 0;
        bool changed = true;
        while(changed){
            changed = false;
            for(int i = 0; i <= tlen - slen; i++){
                if(canErase(stamp, target, i)){
                    for(int j = 0; j < slen; j++){
                        target[i+j] = '?';
                    }
                    moves++;
                    changed = true;
                }
            }
        }
        bool allQ = true;
        for(char c : target) if(c!='?') {allQ = false; break;}
        cout << (allQ ? "YES" : "NO") << "\n";
    }
    return 0;
}

// changed 的作用与为何初始化为 true
// changed 是一个循环控制标志，表示"这一轮有没有发生任何消除"。


// 初始化为 true：为了让 while(changed) 第一次能进入循环。如果初始化 false，循环一次都不会执行。你可以把它理解为"假设第0轮有进展，先进去试试"。
// 每轮开始重置为 false：然后整轮扫描，如果发现有任何一次消除成功，就把 changed 设回 true，下一轮继续。
// 如果一整轮都没消除：changed 保持 false，循环退出，说明再也找不到可消除的位置了。

// 第1轮: 扫描全部位置 → 找到2处可消除 → changed=true → 继续第2轮
// 第2轮: 扫描全部位置 → 找到1处可消除 → changed=true → 继续第3轮
// 第3轮: 扫描全部位置 → 没找到 → changed=false → 退出循环

// i <= tlen - slen 的含义
// stamp 必须完整地盖在 target 上，不能越界。
// target 长度 = tlen，stamp 长度 = slen

// stamp 放在位置 i，会覆盖 target[i] 到 target[i + slen - 1]
// 最后一个合法起点：i + slen - 1 = tlen - 1，即 i = tlen - slen
// 所以 i 的范围是 0 ≤ i ≤ tlen - slen，用 <= 是因为右端点也是合法位置。

// 举例：target 长 5（ababc），stamp 长 3（abc），则 i 最大为 5-3=2，即位置 0、1、2 共3个起点。

// 三个 bool 的逻辑
// 反向操作的目标是：把 target 中能与 stamp 匹配的区域替换成 ?，模拟"撤销最后一次盖印"
// 正向：全? → 盖stamp → 得到target
// 反向：target → 消除stamp → 全?

// canErase 函数里有两个关键判断：
// | 情况                      | 含义                          | 处理                     |
// | ----------------------- | --------------------------- | ---------------------- |
// | target[i+j] == '?'      | 这个位置已经被之后的操作覆盖，不影响本次匹配，视为通配 | continue（跳过，不阻止匹配）     |
// | target[i+j] != stamp[j] | 这个位置字符对不上 stamp             | return false（不能消除）     |
// | 字符相等                    | 匹配成功                        | hasReal = true（记录有效消除） |

// hasReal 的作用：防止对一段"全是 ?"的区域进行无效消除
// 如果某个位置全是 ?，匹配永远成功，会导致 changed 永远为 true，陷入无限循环
// hasReal 确保至少有一个真实字符被消除，操作才有意义

// stamp = "abc", target = "ababc"

// 初始 target = "ababc"

// 第1轮扫描:
//   i=0: target[0..2]="aba" vs stamp="abc" → 'a'≠'c' → 不能消
//   i=1: target[1..3]="bab" vs stamp="abc" → 'b'≠'a' → 不能消
//   i=2: target[2..4]="abc" vs stamp="abc" → 全部匹配 → 消除！
//        target变为 "ab???"，changed=true

// 第2轮扫描:
//   i=0: target[0..2]="ab?" → '?'通配，a=a, b=b → hasReal=true → 能消！
//        target变为 "?????"，changed=true

// 第3轮扫描:
//   所有位置都是?，hasReal始终false → 没有消除 → changed=false → 退出

// 全为? → YES ✓

// allQ 的意思是 "all question marks"，即target 是否已经全部变成了 ?。
// 这就是整道题 YES/NO 的判断依据：
// 反向消除成功 → target 最终全是 ? → YES
// 消除到卡住，还剩下真实字符 → NO

// bool allQ = true;  // 先假设"全是?"

// for (char c : target)        // 遍历 target 每一个字符
//     if (c != '?') {          // 一旦发现有字符不是 ?
//         allQ = false;        // 说明还有真实字符没被消掉
//         break;               // 不用继续扫了，结论已经确定
//     }

// | 要验证的命题   | 初始值   | 遇到反例时         |
// | -------- | ----- | ------------- |
// | 所有元素满足条件 | true  | 设 false，break |
// | 存在元素满足条件 | false | 设 true，break  |

// allQ 属于第一类：验证所有字符都是 ?，所以初始设 true，找到一个不是 ? 的就推翻
// changed 也是第二类的典型：验证存在某次消除成功