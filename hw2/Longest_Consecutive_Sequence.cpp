#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    if(!(cin >> n)) return 0;
    
    vector<long long> a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];

    unordered_set<long long> st;
    st.reserve(n * 2);
    for(auto v : a) st.insert(v);

    // 写法2：直接一边读一边放进 set
    /***
    unordered_set<long long> st;
    for (int i = 0; i < n; ++i) {
        long long x; 
        cin >> x;
        st.insert(x);
    }
    */
    int longest = 0;
    for(const auto &x : st){
        if(st.find(x-1) == st.end()){
            int cnt = 0;
            long long cur = x;
            while(st.find(cur) != st.end()){
                ++cnt;
                ++cur;
            }
            longest = max(longest, cnt);
        }
    }

    cout << longest << "\n";
    return 0;
}