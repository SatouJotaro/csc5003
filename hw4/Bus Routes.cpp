#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    if(!(cin >> n)) return 0;
    
    vector<vector<int>> routes(n);
    unordered_map<int, vector<int>> stop2routes;
    stop2routes.reserve(200000);
    int maxStop = 0;

    for(int i = 0; i < n; ++i){
        int k; cin >> k;
        routes[i].reserve(k);
        for(int j = 0; j < k; ++j){
            int stop; cin >> stop;
            routes[i].push_back(stop);
            stop2routes[stop].push_back(i);
            if(stop > maxStop) maxStop = stop;
        }
    }

    int source, target;
    cin >> source >> target;

    if(source == target){
        cout << 0 << "\n";
        return 0;
    }

    if(stop2routes.find(source) == stop2routes.end()){
        cout << -1 << "\n";
        return 0;
    }

    vector<char> routeHasTarget(n, 0);
    for(int i = 0; i < n; ++i){
        for(int s : routes[i]){
            if( s == target ){
                routeHasTarget[i] = 1;
                break;
            }
        }
    }
    vector<char> visited_route(n, 0);
    vector<char> visited_stop(maxStop + 1, 0);

    queue<pair<int, int>> q;

    for(int r : stop2routes[source]){
        visited_route[r] = 1;
        q.emplace(r, 1);
    }

    int answer = -1;
    while(!q.empty()){
        auto [r, dist] = q.front(); q.pop();

        if(routeHasTarget[r]){
            answer = dist;
            break;
        }

        for(int s : routes[r]){
            if(visited_stop[s]) continue;
            visited_stop[s] = 1;

            for(int nr : stop2routes[s]){
                if(!visited_route[nr]){
                    visited_route[nr] = 1;
                    q.emplace(nr, dist + 1);
                }
            }
        }
    }

    cout << answer << "\n";
    return 0;
}