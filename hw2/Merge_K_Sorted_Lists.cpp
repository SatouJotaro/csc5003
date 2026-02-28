#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

// 定义节点结构体
struct Node
{
    int value; // 当前元素的值
    int list_idx; // 元素来自哪个列表（0 ~ k - 1）
    int element_idx; // 元素在列表中的索引（为了找下一个元素）

    // 重载 < 运算符 (必须是为了让 std::priority_queue 知道如何比较)
    // 默认的 priority_queue 是 Max Heap。
    // 为了实现 Min Heap，我们需要让 A < B 意味着 B 优先级更高（值更大）。
    // 但对于 Min Heap，我们希望值小（A < B）的优先级更高。
    // 因此，我们定义：如果 A.value > B.value，则 A 具有较低的优先级（即 A < B 为 false）。
    // 更直观的做法是：我们直接定义 > 运算符或者使用 greater<> 模板参数。
    
    // 采用更标准的 C++ 做法：使用 std::greater<>
    // 这里我们不重载 <，而是直接在声明时使用 greater。
};

// 定义比较结构体，用于构建最小堆（如果不用 std::greater，则需要这个来强制定义 Min-Heap）
struct CompareNode
{
    // 重载 operator()，使得这个结构体可以像函数一样被调用
    bool operator()(const Node& a, const Node& b){ 
        // 返回 true 表示 a 的优先级低于 b (a 应该被排在 b 后面)
        // 对于 Min Heap (最小堆)：我们希望值小的元素优先级高。
        // 所以，如果 a 的值大于 b 的值 (a.value > b.value)，则 a 优先级低，返回 true。
        return a.value > b.value;
    }
};

void solve(){
    int k;
    if(!(cin >> k)) return; // 如果 cin 失败（例如，文件结束符 EOF），则直接退出函数
    if(k == 0){
        cout << 0 << endl;
        return;
    }

    // 存储 K 个输入列表
    vector<vector<int>> lists(k);
    int total_elements = 0;
    // 读取输入
    for(int i = 0; i < k; ++i){
        int len;
        cin >> len;
        lists[i].resize(len);
        total_elements += len;
        for(int j = 0; j < len; ++j){
            cin >> lists[i][j];
        }
    }
    if(total_elements == 0){
        cout << 0 << endl;
        return;
    }

    // 初始化最小堆
    // 声明一个最小堆：存储 Node，使用 CompareNode (基于值进行比较)
    // 模板参数: <Node 类型, 存储容器, 比较器> 
    priority_queue<Node, vector<Node>, CompareNode> min_heap;

    // 将每个列表的第一个元素加入堆中
    for(int i = 0; i < k; ++i){
        if(!lists[i].empty()){
            min_heap.push({
                lists[i][0], // value
                i,           // list_idx
                0            // element_idx
            });
        }
    }

    // 迭代合并
    vector<int> result;
    result.reserve(total_elements); // 预分配空间，提高效率

    while(!min_heap.empty()){
        // 取出全局最小值
        Node current = min_heap.top();
        min_heap.pop();

        result.push_back(current.value); // 记录结果

        // 检查并加入该列表的下一个元素
        int next_element_idx = current.element_idx + 1;
        int current_list_idx = current.list_idx;

        if(next_element_idx < (int)lists[current_list_idx].size()){
            // if 还有下一个元素，加入堆
            min_heap.push({
                lists[current_list_idx][next_element_idx],
                current_list_idx,
                next_element_idx
            }); 
        }
    }

    // 输出结果
    cout << result.size() << endl;
    if(result.size() > 0){
        for(size_t i = 0; i < result.size(); ++i){
            cout << result[i] << (i == result.size() - 1 ? "" : " ");
        }
        cout << endl;
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    solve();
    return 0;
}
