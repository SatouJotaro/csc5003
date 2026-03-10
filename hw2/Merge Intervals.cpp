#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    int n;
    cin >> n;
    if(n == 0) return 0;
    vector<vector<int>> intervals; 
    for(int i = 0; i < n; i++){
        int start, end;
        cin >> start >> end;
        intervals.push_back({start, end});
    }
    
    // 默认按第一个元素排序
    sort(intervals.begin(),intervals.end()); 

    vector<vector<int>> result;
    // 1. 把第一个区间放进去作为起始
    result.push_back(intervals[0]); 
    // 2. 从第二个开始遍历
    for(int i = 1; i < n; i++){ 
         // 如果当前区间的起点 <= 结果集中最后一个区间的终点，说明有重叠
        if(intervals[i][0] <= result.back()[1]){ 
            // 合并：更新结果集中最后一个区间的终点为两者的较大值
            result.back()[1] = max(intervals[i][1], result.back()[1]);
        }
        else{
            // 没有重叠，直接放入新区间
            result.push_back(intervals[i]);
        }
    }

    cout << result.size() << endl;
    for(int i = 0; i < result.size(); i++){
        cout << result[i][0] << " " << result[i][1] << endl; // 加个空格！
    }
    return 0;
}