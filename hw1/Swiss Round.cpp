#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

struct player{
    int id;
    int score;
    int strength;
};

bool cmp(const player& a, const player& b){
    if(a.score != b.score){
        return a.score > b.score;
    }
    return a.id < b.id;
}
int main(){
    int N, R, Q;
    cin >> N >> R >> Q;
    int n = 2 * N;
    vector<player> p(n);
    for(int i = 0; i < n; i++){
        p[i].id = i + 1;
        cin >> p[i].score;
    }
    for(int i = 0; i < n; i++){
        cin >> p[i].strength;
    }

    sort(p.begin(), p.end(), cmp);

    for(int round = 0; round < R; ++round){
        vector<player> winners;
        vector<player> losers;

        for(int i = 0; i < n; i += 2){
            if(p[i].strength > p[i+1].strength){
                p[i].score++;
                winners.push_back(p[i]);
                losers.push_back(p[i+1]);
            } else {
                p[i+1].score++;
                winners.push_back(p[i+1]);
                losers.push_back(p[i]);
            }
        }

        merge(winners.begin(), winners.end(), losers.begin(), losers.end(), p.begin(), cmp);
    }

    cout << p[Q-1].id << endl;
    return 0;
}