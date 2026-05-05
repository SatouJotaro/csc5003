#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n; cin >> n;
    vector<int> nums(n); // 一维数组排列
    for(int i = 0; i < n; i++) cin >> nums[i];

    // 1. 从右向左找第一个下降点 i，使 nums[i] < nums[i+1]
    int i = n - 2;
    while(i >= 0 && nums[i] >= nums[i+1]){
        i--;
    }

    // 2. 如果找到了这个点
    if(i >= 0){
        // 从最右边开始，找第一个比 nums[i] 大的数 nums[j]
        int j = n - 1;
        while(nums[j] <= nums[i]){
            j--;
        }
        swap(nums[i], nums[j]);
    }

    // 3. 将 i 以后的部分进行反转 (因为它们目前是降序的)
    // 这一步逻辑：如果没找到下降点(i=-1)，则 i+1 就是 0，即反转整个数组
    int left = i + 1;
    int right = n - 1;
    while(left < right){
        swap(nums[left], nums[right]);
        left++;
        right--;
    }

    for(int k = 0; k < n; k++){
        cout << nums[k];
    }
    cout << endl;
    
    return 0;
}