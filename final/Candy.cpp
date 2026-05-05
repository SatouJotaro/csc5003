// 给 n 个孩子按评分分糖果：每人至少 1 颗，评分严格高于相邻孩子的必须拿到更多糖果，输出最少总糖果数

// 最简做法：贪心双向遍历
// 这是讲义里讲的标准解法 ，逻辑清晰，代码量极小，时间复杂度 O(n)：

// 初始化每人 1 颗糖

// 从左到右：若 ratings[i] > ratings[i-1]，则 candy[i] = candy[i-1] + 1

// 从右到左：若 ratings[i] > ratings[i+1]，则 candy[i] = max(candy[i], candy[i+1] + 1)

// 求总和

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> r(n), candy(n, 1);
    for (int i = 0; i < n; i++) cin >> r[i];

    // 左→右
    for (int i = 1; i < n; i++)
        if (r[i] > r[i-1]) candy[i] = candy[i-1] + 1;

    // 右→左
    for (int i = n-2; i >= 0; i--)
        if (r[i] > r[i+1]) candy[i] = max(candy[i], candy[i+1] + 1);

    cout << accumulate(candy.begin(), candy.end(), 0) << endl;
    return 0;
}

// accumulate 是 C++ STL <numeric> 头文件中的一个函数，用于对容器中的元素求累加和
// #include <numeric>
// accumulate(first, last, init);
// 三个参数分别是 ：
// first：容器起始迭代器
// last：容器结束迭代器（不包含）
// init：累加初始值，返回类型与它相同

