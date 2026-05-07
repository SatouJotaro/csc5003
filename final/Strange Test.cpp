// 首先，老师会给每个学生两个正整数 a 和 b（a<b）。
// 之后，学生可以任意次数地进行以下操作：

// a:=a+1（将 a 增加 1）；
// b:=b+1（将 b 增加 1）；
// a:=a∣b（将 a 替换为 a 和 b 的按位或运算结果）。
// 要想获得满分，学生需要告诉老师使 a 和 b 相等所需的最少操作次数。

// 讲义分析的"OR 最多用一次"是对的，这道题解同样基于此，但用了更直接的方式：

// OR 操作 a = a | b 的效果是：把 a 中所有为 0 但 b 中为 1 的位，全部设为 1。
// 用 OR 之后要让 a == b，只需要 a | b == b（即 a 是 b 的子集）后再让 a 和 b 相等。

// 两种策略
// 题解枚举的两种方案（取其最小）：

// 策略 1：先增加 a，直到 a | b == b，再 OR
// while (a | b != b) { a++; cnt++; }  // 增加 a 直到 a 是 b 的子集
// if (a != b) cnt++;                   // 做 OR（一步变成 b）

// 策略 2：先增加 b，直到 a | b == b，再 OR
// while (a | b != b) { b++; cnt++; }  // 增加 b 直到 a 是 b 的子集
// if (a != b) cnt++;                   // 做 OR（一步变成 b）

// 最终 ans = min(策略1, 策略2, b-a（不用OR）)

// 为什么只有这两种？
// OR 只用一次（讲义证明过），所以 OR 之前只能操作 a 或 b
// 操作 a 让 a | b == b → 策略 1
// 操作 b 让 a | b == b → 策略 2
// 不用 OR → 直接 b-a

#include<bits/stdc++.h>
using namespace std;

int main(){
    int T; cin >> T;
    while(T--){
        int a, b; cin >> a >> b;

        int ans = b - a; // 不用 OR

        // 策略1：增加 a 直到 a|b == b，再 OR
        int x = a, y = b, cnt = 0;
        while((x | y) != y) { x++; cnt++; }
        if(x != y) cnt++; // 用 OR 让 a = b
        ans = min(ans, cnt);

        // 策略2：增加 b 直到 a|b == b，再 OR
        x = a; y = b; cnt = 0;
        while((x | y) != y) { y++; cnt++; }
        if(x != y) cnt++;
        ans = min(ans, cnt);

        cout << ans << "\n";
    }
    return 0;
}