#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<algorithm>

using namespace std;

string findOrder(int k, vector<string>& words){
    unordered_map<char, int> in_degree;
    unordered_map<char, unordered_set<char>> adj;

    for(const string& w: words){
        for(char c : w) in_degree[c] = 0;
    }

    for(int i = 0; i < k - 1; ++i){
        string w1= words[i], w2 = words[i+1];
        int len = min(w1.size(), w2.size());
        bool found = false;
        for(int j = 0; j < len; ++j){
            if(w1[j] != w2[j]){
                if(adj[w1[j]].find(w2[j]) == adj[w1[j]].end()){
                    adj[w1[j]].insert(w2[j]);
                    in_degree[w2[j]]++;
                }
                found = true;
                break;
            }
        }
        if(!found && w1.size() > w2.size()) return "";
    }

    priority_queue<char, vector<char>, greater<char>> pq;
    for(auto const& [node, deg] : in_degree){
        if(deg == 0) pq.push(node);
    }

    string res = "";
    while(!pq.empty()){
        char u = pq.top(); pq.pop();
        res += u;
        for(char v : adj[u]){
            if(--in_degree[v] == 0) pq.push(v);
        }
    }

    return res.size() == in_degree.size() ? res : "";
}
int main(){
    int k;
    cin >> k;

    vector<string> words(k);
    for(int i = 0 ; i < k; i++) cin >> words[i];

    cout << findOrder(k, words) << endl;
    return 0;
}