#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<unordered_map> // 用来记录每个状态已经走了多少步，同时起到去重作用
using namespace std;

int main(){
    string start; cin >> start;
    string target = "123804765";

    if(start == target) {cout << 0 << endl; return 0;}

    queue<string> q;
    unordered_map<string, int> dist; // 记录状态到起点的距离，也作为"访问过"的标记

    q.push(start);
    dist[start] = 0;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while(!q.empty()){
        string current = q.front(); q.pop();

        int distance = dist[current];

        // 1. 找到 '0' 在字符串中的位置
        int pos = current.find('0');
        int x = pos / 3; // 行
        int y = pos % 3; // 列

        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx >= 0 && nx < 3 && ny >= 0 && ny < 3){
                string next = current;
                swap(next[pos], next[nx * 3 + ny]);

                if(dist.find(next) == dist.end()){
                    dist[next] = distance + 1;
                    if(next == target){
                        cout << dist[next] << endl;
                        return 0;
                    }
                    q.push(next);
                }
            }
        }
    }
    return 0;
}