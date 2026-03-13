#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
    string S, P;
    cin >> S >> P;

    int n = S.length();
    int m = P.length();

    // 1. 计算 pi 数组 (前缀函数)
    // pi[i] 存的是 P[0...i-1] 这个前缀子串中，最长相等前后缀的长度
    // 假设 P="ABAB", pi[3] 就是看 "ABA"，真前缀"A" == 真后缀"A"，所以是 1
    vector<int> pi(m + 1, 0);

    // i: 当前正在计算前缀函数对应的子串长度，从 2 到 m
    // j: 当前已匹配的最长前后缀长度 (也可以理解为：下一个待比较的 P 的字符下标)
    for(int i = 2, j = 0; i <= m; i++){
        // 核心痛点：如果 P[j] != P[i-1]，说明匹配中断了
        // 我们要在 P 的已匹配部分中寻找一个更短的“备用”前缀
        // pi[j] 就是跳转到这个“备用”位置的入口
        while(j > 0 && P[j] != P[i - 1]) j = pi[j];

        // 如果字符匹配，说明当前最长前后缀长度又增加 1
        if(P[j] == P[i - 1]) j++;

        // 记录下来
        pi[i] = j;
    }

    // 2. 匹配过程 (在 S 中寻找 P)
    // i: 遍历 S 的指针
    // j: 遍历 P 的指针 (表示已经匹配了多长)
    for(int i = 0, j = 0; i < n; i++){
        // 如果当前字符 S[i] 和 P[j] 不相等
        // 同样使用 pi 数组进行回溯，找到一个更短的、依然合法的匹配位置
        // 这样就不需要把 i 回退了，这是 KMP 速度快的关键
        while(j > 0 && P[j] != S[i]) j = pi[j];

        // 如果匹配上了，P 的指针 j 前进
        if(P[j] == S[i]) j++;

        // 如果 j == m，说明整个 P 都匹配到了
        if(j == m){
            // i 是 S 的当前下标(0-based)，m 是长度
            // 输出格式要求起始位置(1-based)，所以是 (i - m + 1) + 1
            cout << i - m + 2 << "\n";

            // 为了寻找下一个可能的重叠匹配，将 j 重置为 pi[j]
            // 这相当于把 P 向后“滑动”了
            j = pi[j];
        }
    }

    for(int i = 1; i <= m; i++){
        cout << pi[i] << (i == m ? "" : " ");
    }
    cout << endl;
    return 0;
}