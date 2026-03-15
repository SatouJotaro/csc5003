#include<bits/stdc++.h>
using namespace std;

struct player{
    int id;
    int score;
    int strength;
};

bool cmp(const player& a, const player& b){ // 比较容器里的player的比较法则
    if(a.score != b.score){
        return a.score > b.score;
    }
    return a.id < b.id;
}

int main(){
    int N, R, Q;
    cin >> N >> R >> Q;
    int n = 2 * N; // 2 * N!
    vector<player> p(n); // 创建一个能存放 n 个 player 的容器
    for(int i = 0; i < n; i++){
        p[i].id = i + 1; // i + 1!!
        cin >> p[i].score;
    }
    for(int i = 0; i < n; i++){
        cin >> p[i].strength;
    }

    sort(p.begin(), p.end(), cmp);

    for(int round = 0; round < R; ++round){
        vector<player> winners;
        vector<player> losers;

        for(int i = 0; i < n; i += 2){ // 这里i代表的是选手
            if(p[i].strength > p[i+1].strength){
                p[i].score++; // 给人家加分啊
                winners.push_back(p[i]);
                losers.push_back(p[i+1]);
            }
            else{
                p[i+1].score++;
                winners.push_back(p[i+1]);
                losers.push_back(p[i]);
            }
        }

        merge(winners.begin(), winners.end(), losers.begin(), losers.end(), p.begin(), cmp); // 重排规则需要自己加上
    }
    cout << p[Q-1].id << endl; // 要输出的是选手id
    return 0;
}