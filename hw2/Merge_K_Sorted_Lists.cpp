#include<bits/stdc++.h>
using namespace std;

int main(){
    int m; cin >> m;
    // vector 模板只接受一个参数（表示存储的类型）。
    // 你想要存储一组区间，应该使用 vector<pair<int, int>>
    vector<pair<int, int>> interval; 
    for(int i = 0; i < m; i++){
        int start, end;
        // 你不能将 push_back 的结果作为 cin 的操作对象。
        // 正确的做法应当是先用变量读取 start 和 end，然后再将它们存入 vector。
        cin >> start >> end;
        interval.push_back({start, end});
    }

    sort(interval.begin(), interval.end());

    vector<pair<int, int>> result;
    // 1. 把第一个区间放进去作为起始
    result.push_back(interval[0]); 
    // 后果：越界访问（Segmentation Fault） 
        // 在你的循环中：result[i].second。当 i=0 时，result 是空的，没有任何元素。
        // 你试图访问 result[0]，这相当于访问了一块未分配的内存，程序会直接报错/崩溃。
    // 逻辑空缺：合并区间的核心思想是保留一个“当前的合并序列末尾”，你需要一个初始元素作为比较基准。
        // 如果没有这一步，循环内部的逻辑就失去了参照物。
    
    for(int i = 1; i < m; i++){ // 第一个区间已经放了 就要从第二个开始遍历
        // 你应该始终使用 result.back() 来获取刚才放入 result 的那个区间（即当前最新的合并后区间）。
        // 你要比较的目标是 interval[i] (当前正在遍历的) 和 result.back() (已经合并好的最后一个)。
        // 你在循环体内却同时混用了 i 和 i+1，这在逻辑上会跳过数据，导致合并漏掉很多项。

        if(interval[i].first <= result.back().second){
            result.back().second = max(result.back().second, interval[i].second);
        }
        else{
            result.push_back(interval[i]);
        }
    }

    // 不加 endl 的后果：输出格式错误。评测机通常是根据“字符流”来对比答案的，多一个空格、少一个换行，或者把两个数字粘在一起，都会导致题目判错。
    cout << result.size() << endl;
    for(int i = 0; i < result.size(); i++){
        // 题目要求输出 start 和 end 中间用空格隔开，你现在的写法会把它们连在一起，比如 1 5 会输出 15。
        cout << result[i].first << " " << result[i].second << endl;
    }
    
    return 0;
}