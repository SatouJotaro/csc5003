#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

string findOrder(int k, vector<string>& words) {
    unordered_map<char, int> in_degree;             // 记录每个字符的入度（有多少字符在它前面）
    unordered_map<char, unordered_set<char>> adj;   // 邻接表，记录字符之间的前后关系
    
    // 初始化：确保所有出现的字符都在表中
    for (const string& w : words) {
        for (char c : w) in_degree[c] = 0;          // 即使没有任何边，也要把所有字符加入映射，初始化入度为0
    }

    // 建立图
    for (int i = 0; i < k - 1; ++i) {
        string w1 = words[i], w2 = words[i+1];
        int len = min(w1.size(), w2.size());
        bool found = false;
        for (int j = 0; j < len; ++j) {
            // 找到第一个不同的字符
            if (w1[j] != w2[j]) {
                if (adj[w1[j]].find(w2[j]) == adj[w1[j]].end()) {   // 防止重复添加边
                    adj[w1[j]].insert(w2[j]);                       // 建立从 w1[j] 指向 w2[j] 的边
                    in_degree[w2[j]]++;                             // 入度增加
                }
                found = true;
                break; // 找到第一个不同之处后，后面的字符就不再提供约束了，直接跳出
            }
        }
        // 特殊情况：如果 w1 是 w2 的前缀，且 w1 更长，这是非法排序(如: "abc", "ab")
        // 特殊情况：如果是前缀关系但顺序反了
        if (!found && w1.size() > w2.size()) return "";
    }

    // 优先队列保证最小值优先
    // 题目要求“字典序最小”，因此我们需要使用小根堆（优先队列），而不是一般的队列。
    priority_queue<char, vector<char>, greater<char>> pq; // greater<char> 确保每次取出的都是当前入度为0的字符中字典序最小的一个
    for (auto const& [node, deg] : in_degree) {
        if (deg == 0) pq.push(node); // 将所有入度为0的字符入队
    }

    string res = "";
    while (!pq.empty()) {
        char u = pq.top(); pq.pop(); // 取出当前最小的字符
        res += u;
        for (char v : adj[u]) {                     // 检查所有指向的邻居
            if (--in_degree[v] == 0) pq.push(v);    // 若邻居入度变为0，加入队列
        }
    }

    // 如果结果长度小于总的字符数，说明存在环（因为如果存在环，环内的字符永远无法入队）
    return res.size() == in_degree.size() ? res : "";
}

int main() {
    int k;
    cin >> k;
    vector<string> words(k);
    for (int i = 0; i < k; ++i) cin >> words[i];
    
    cout << findOrder(k, words) << endl;
    return 0;
}