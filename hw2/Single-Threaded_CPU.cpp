#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // 存储 (enqueueTime, processingTime, 原始下标)
    vector<tuple<long long, long long, int>> tasks(n);
    for(int i = 0; i < n; i++){
        long long e, p;
        cin >> e >> p;
        tasks[i] = {e, p, i};
    }

    // 按 enqueueTime 排序
    sort(tasks.begin(), tasks.end());

    // 最小堆：(processingTime, 原始下标)
    // pair 的比较是字典序：先比 processingTime，相同再比 index → 完美满足题意
    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > pq;

    vector<int> result;
    long long currentTime = 0;
    int taskIdx = 0;  // 排序后的任务指针

    while((int)result.size() < n){
        // 将所有已可用的任务加入堆
        while(taskIdx < n && get<0>(tasks[taskIdx]) <= currentTime){
            pq.push({get<1>(tasks[taskIdx]), get<2>(tasks[taskIdx])});
            taskIdx++;
        }

        if(pq.empty()){
            // CPU 空闲且无可用任务，直接跳到下一个任务的入队时间
            currentTime = get<0>(tasks[taskIdx]);
        } else {
            // 选处理时间最短的任务（自动处理 tie）
            auto [procTime, idx] = pq.top();
            pq.pop();
            result.push_back(idx);
            currentTime += procTime;
        }
    }

    for(int i = 0; i < n; i++){
        if(i > 0) cout << " ";
        cout << result[i];
    }
    cout << "\n";
    return 0;
}