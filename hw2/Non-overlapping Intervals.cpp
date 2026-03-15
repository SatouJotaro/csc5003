#include<bits/stdc++.h>
using namespace std;

// bool cmp(const pair<int, int>& a, const pair<int, int>& b){
//     return a.second < b.second;
// }
int main(){
    int n; cin >> n;
    vector<pair<int, int>> interval;
    for(int i = 0; i < n; i++){
        int start, end;
        cin >> start >> end;
        interval.push_back({start, end});
    }

    // [] (空捕获)： 表示该 Lambda 函数不访问外部作用域中的任何局部变量。它只使用传入的参数（在这个例子中是 a 和 b）。
    // [&] (引用捕获)： 表示在该函数内部，你可以使用当前作用域内的所有外部局部变量，并且是通过“引用”的方式（修改这些变量会影响外部）。
    // [=] (值捕获)： 表示在该函数内部，你可以使用当前作用域内的所有外部局部变量，但它是通过“拷贝”的方式（修改内部的变量不会影响外部）。
    sort(interval.begin(), interval.end(), [](const pair<int, int>& a, const pair<int, int>& b){
        return a.second < b.second;
    });

    int count = 0; // 记录移除的数量
    int end = interval[0].second; // 记录当前选中的最后一个区间的结束点

    for(int i = 1; i < n; i++){
        // 比较逻辑：如果不重叠
        if(interval[i].first >= end){
            // 没有重叠，更新 end，意味着我们“选中”了这个区间
            end = interval[i].second;
        }
        // 有重叠！因为我们按结束时间排过序了，
        // 现在的 interval[i] 肯定比我们之前选的区间结束得晚，
        // 所以保留旧的、丢弃新的（移除数+1）显然更优。
        else count++;
    }

    cout << count << endl;
    return 0;
}