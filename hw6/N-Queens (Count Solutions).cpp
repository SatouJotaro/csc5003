// 如果你想完全规避偏移量逻辑（即不加 n），我们可以换一种思路：
// 不再直接使用对角线性质的数学公式，而是回溯时通过“检查已放置皇后的位置”来判断安全性。 
// 这种写法不需要额外的对角线标记数组，只需要一个记录每一行皇后的列位置的数组即可。
// 逻辑非常直观：每放一个皇后，就检查它是否会和之前已经放好的皇后冲突


#include <iostream>
#include <vector>
#include <cmath> // 为了使用 abs()

using namespace std;

// 检查在第 row 行放置在 col 列是否与前面的皇后冲突
bool isSafe(int row, int col, const vector<int>& queenCol) {
    for (int prevRow = 0; prevRow < row; ++prevRow) {
        int prevCol = queenCol[prevRow];
        
        // 1. 同一列冲突
        // 2. 对角线冲突：行差的绝对值等于列差的绝对值
        if (col == prevCol || abs(row - prevRow) == abs(col - prevCol)) {
            return false;
        }
    }
    return true;
}

void backtrack(int row, int n, int &count, vector<int>& queenCol) {
    if (row == n) {
        count++;
        return;
    }

    for (int col = 0; col < n; ++col) {
        if (isSafe(row, col, queenCol)) {
            // 记录当前行皇后放在哪一列
            queenCol[row] = col;
            
            backtrack(row + 1, n, count, queenCol);
            
            // 不需要显式清除，覆盖即可（回溯核心就在这里）
        }
    }
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    int count = 0;
    // queenCol[i] 表示第 i 行的皇后所在的列
    vector<int> queenCol(n); 

    backtrack(0, n, count, queenCol);

    cout << count << endl;

    return 0;
}