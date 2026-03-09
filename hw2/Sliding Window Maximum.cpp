#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    deque<int> dq; // 存储索引，值按递减顺序
    vector<int> result;
    
    for (int i = 0; i < n; i++) {
        // 维护队列递减：移除队列尾部小于当前值的索引
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }
        // 添加当前索引到队列尾部
        dq.push_back(i);
        
        // 移除不在当前窗口内的索引（头部索引小于 i - k + 1）
        if (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // 当窗口形成时（i >= k - 1），将当前窗口最大值加入结果
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    int m = n - k + 1;
    cout << m << endl;
    for (int i = 0; i < m; i++) {
        cout << result[i];
        if (i < m - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}