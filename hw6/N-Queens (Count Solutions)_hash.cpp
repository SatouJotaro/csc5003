#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>

using namespace std;

void backtrack(int row, int n, int &count,
                unordered_set<int>& cols,
                unordered_set<int>& diag1,
                unordered_set<int>& diag2){
    if(row == n){
        count++;
        return;
    }

    for(int col = 0; col < n; col++){
        int d1 = row - col;
        int d2 = row + col;

        // 检查：如果哈希表中不存在对应的key，说明该位置安全
        if(cols.find(col) == cols.end() && 
            diag1.find(d1) == diag1.end() &&
            diag2.find(d2) == diag2.end()){
            
            // 放置皇后：将当前列和对角线信息加入哈希表
            cols.insert(col);
            diag1.insert(d1);
            diag2.insert(d2);

            // 递归进入下一行
            backtrack(row + 1, n, count, cols, diag1, diag2);

            // 回溯：撤销选择（从哈希表中移除刚才加入的数据）
            cols.erase(col);
            diag1.erase(d1);
            diag2.erase(d2);
        }
    }
}

int main(){
    int n; cin >> n;
    int count = 0;

    // 动态初始化 vector：
    // col 需要 n 个位置
    // diag1 和 diag2 最多需要 2*n 个位置
    unordered_set<int> cols;
    unordered_set<int> diag1;
    unordered_set<int> diag2;

    backtrack(0, n, count, cols, diag1, diag2);
    cout << count << endl;
    return 0;
}