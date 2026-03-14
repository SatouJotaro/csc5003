#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

int R, C; 
string word;
vector<string> board;
vector<vector<bool>> visited;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool dfs(int x, int y, int index){
    // 1. 递归终止条件：单词找齐了
    if(index == word.length()) return true;

    // 2. 越界检查、字母匹配检查、重复访问检查
    if(x < 0 || x >= R || y < 0 || y >= C || visited[x][y] || board[x][y] != word[index]){
        return false;
    }

    // 3. 进入分支前标记为已访问
    visited[x][y] = true;

    // 4. 枚举上下左右四个方向
    for(int i = 0; i < 4; i++){
        if(dfs(x + dx[i], y + dy[i], index + 1)){
            return true; // 只要有一条路通，就一直返回 true
        }
    }

    // 5. 回溯：退出分支时取消标记（给其他路径尝试的机会）
    visited[x][y] = false;

    return false;
}

int main(){
    cin >> R >> C;
    board.resize(R);
    visited.resize(R, vector<bool>(C, false));
    for(int i = 0; i < R; i++){
            cin >> board[i];
    }
    cin >> word;

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(dfs(i, j, 0)) cout << "YES" << endl;
        }
    }
    cout << "NO" << endl;
    return 0;
}