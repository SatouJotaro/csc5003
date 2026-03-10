#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main(){
    int n;
    if(!(cin >> n) || n == 0) return 0;

    vector<vector<int>> intervals;
    for(int i = 0; i < n; i++){
        int start, end;
        cin >> start >> end;
        intervals.push_back({start, end});
    }

    // 关键修正：使用 Lambda 表达式按区间结束时间（intervals[i][1]）升序排序
    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){
        return a[1] < b[1];
    });

    int last_end = intervals[0][1]; // 记录上一个保留区间的结束时间
    int count = 0; // 记录删除了多少个
    // 从第二个区间开始遍历 (下标1到n-1)
    for(int i = 1; i < n; i++){
        if(last_end <= intervals[i][0]){
            last_end = intervals[i][1];
        }
        else{
            count++;
        }
    }

    cout << count << endl;
    return 0;
}