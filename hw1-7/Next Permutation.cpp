// 给定一个整数数组，输出它的下一个字典序排列；如果已经是最大排列（完全降序），则输出最小排列（升序）
// 输入：第一行整数 n，第二行 n 个整数
// 输出：一行，变换后的数组

// 最简解法：直接用 STL
// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n;
//     cin >> n;
//     vector<int> nums(n);
//     for (int i = 0; i < n; i++) cin >> nums[i];

//     next_permutation(nums.begin(), nums.end());
//     // 若已是最大排列，next_permutation 自动将其变为升序（最小排列）

//     for (int i = 0; i < n; i++) {
//         cout << nums[i];
//         if (i < n - 1) cout << " ";
//     }
//     cout << endl;
//     return 0;
// }

// 想象把所有排列像字典单词一样从小到大排成一列，字典序就是这个顺序
// 比较两个排列时，从左到右逐位比较，第一个不同的位置，数字小的排列更靠前
// [1,2,3] → [1,3,2] → [2,1,3] → [2,3,1] → [3,1,2] → [3,2,1]
//   第1小      第2小      第3小      第4小      第5小      第6小（最大）

// 手写算法：四步法
// 核心思路：尽量只改动靠右的位置，改动越靠右，增幅越小，才能保证是"下一个"而不是"跳过了好几个" 

// 以 [1,3,5,4,2] 为例演示：

// 第一步：从右往左找第一个"左邻 < 右邻"的位置 i（即不再递增的突破口）
// → 3 < 5，所以 i = 1，nums[i] = 3

// 第二步：从右往左找第一个比 nums[i] 大的位置 j
// → 4 > 3，所以 j = 3，nums[j] = 4

// 第三步：交换 nums[i] 和 nums[j]
// → [1,4,5,3,2]

// 第四步：将 i+1 之后的部分翻转（使其变为升序，最小化后缀）
// → [1,4,2,3,5] ✓

// 特殊情况：若第一步找不到这样的 i（整个数组降序），说明已是最大排列，直接翻转整个数组

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++) cin >> nums[i];

    // 第一步：从右往左找第一个 nums[i] < nums[i+1]
    int i = n - 2;
    while(i >= 0 && nums[i] >= nums[i+1]) i--;

    if(i >= 0){
        // 第二步：从右往左找第一个比 nums[i] 大的 j
        int j = n - 1;
        while(nums[j] <= nums[i]) j--;
        // 第三步：交换
        swap(nums[i], nums[j]);
    }
    // 第四步：翻转 i+1 之后的部分
    reverse(nums.begin() + i + 1, nums.end());


    for (int k = 0; k < n; k++) {
        cout << nums[k];
        if (k < n - 1) cout << " ";
    }
    cout << endl;

    return 0;
}