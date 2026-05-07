// 题目含义：寻找数组中每个元素右侧第一个比它大的值，并计算两者的索引间距。 
// 输入输出：输入天数 n 及每日气温，输出对应天数需要等待多少天才能遇到更高的气温（若无更高气温则输出 0）。

// 处理“右侧第一个更大值”问题的标准最优解是单调栈。

// 维护一个栈：栈内存储气温的下标。
// 保持单调递减：栈中的气温对应的数值从栈底到栈顶必须是递减的。
// 触发计算：遍历每一天，如果当前气温比“栈顶那天的气温”高，说明找到了栈顶那天的“下一个高温日”。
//     计算间距：结果 = 当前日期 - 栈顶日期。
//     弹出栈顶。
//     继续对比新的栈顶，直到栈为空或当前气温不再更高。
// 入栈：将当前日期下标压入栈中。

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    int n;
    if(!(cin >> n)) return 0;

    vector<int> T(n), ans(n, 0);
    for(int i = 0; i < n; ++i) cin >> T[i];

    stack<int> st; // 存储下标
    for(int i = 0; i < n; ++i){
        // 当 当前温度 > 栈顶下标对应的温度 时，说明找到了栈顶的“下一个更高温”
        while(!st.empty() && T[i] > T[st.top()]){
            int prev_index = st.top();
            ans[prev_index] = i - prev_index; // 计算日期差
            st.pop();
        }
        st.push(i);  // 当前日期入栈，等待寻找它的更高温
    }

    for(int i = 0; i < n; ++i){
        cout << ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;
    return 0;
}