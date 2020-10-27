#include "user_algorithm.h"
using namespace std;

int DynamicProgramming::FibNumCalculate(int N)
{
    vector<int> dynamicProgrammingTable(N + 1, 0);
    // base case
    dynamicProgrammingTable[1] = dynamicProgrammingTable[2] = 1;
    for (int i = 3; i <= N; i++)
        dynamicProgrammingTable[i] = dynamicProgrammingTable[i - 1] + dynamicProgrammingTable[i - 2];
    return dynamicProgrammingTable[N];
}

/*
    给你 k 种面值的硬币，面值分别为 c1, c2 ... ck，每种硬币的数量无限，再给一个总金额 amount，问你最少需要几枚硬币凑出这个金额，如果不可能凑出，算法返回 - 1 。
*/
int DynamicProgramming::coinChage(vector<int>& coinsList, int amount)
{
    // 数组大小为 amount + 1，初始值为 amount + 1
    // 因为凑成 amount 金额的硬币数最多只可能等于 amount（全用 1 元面值的硬币），所以初始化为 amount + 1 就相当于初始化为正无穷，便于后续取最小值。
    vector<int> result(amount + 1, amount + 1);
    // base case
    result[0] = 0;
    if (amount == 0) {//0元0个硬币可解
        return 0;
    }
    if (amount < 0) {//金额小于0时无解
        return -1;
    }
    
    // 外层 for 循环在遍历所有状态的所有取值
    for (int i = 0; i < result.size(); i++) {
        for (int coin : coinsList) {
            if (i < coin) {//要求金额小于硬币面额时无解
                continue;
            }
            /*
            * 举例：
                面额：1,3,5,7
                金额：
                0:0
                1:1
                2:1,1
                3:3
                4:3,1
                5:5,
                6:5,1/3,3
                7:7
                8:7,1
                9:7,1,1/3,3,3/1,3,5
                10:7,3/5,5
                11:5,5,1
                ...

            */
            result[i] = min(result[i], result[i - coin] + 1);//初始值为无穷大，从无穷大和（金额-当前面额+1，即之前的结果+当前面额的硬币1枚）中比较，循环出最小的一种可能
        }
    }
    /* 无解时返回-1 */
    if (result[amount] == amount + 1) {
        return -1;
    }
    else {
        return result[amount];
    }
    
}


vector<vector<int>> result;

bool isContained(vector<int>& list, int element)
{
    return (find(list.begin(), list.end(), element) != list.end());
}

// 路径：记录在 track_list 中
// 选择列表：nums 中不存在于 track_list 的那些元素
// 结束条件：nums 中的元素全都在 track_list 中出现
void backtrack(vector<int> &nums, vector<int>& track_list)
{
    //触发结束条件
    if (track_list.size() == nums.size()) {
        result.push_back(track_list);
        return;
    }
    for (int i = 0; i < nums.size(); i++) {
        //排除已经包含的选择
        if (isContained(track_list, nums[i])) {
            continue;
        }
        //做选择
        track_list.push_back(nums[i]);
        // 进入下一层决策树
        backtrack(nums, track_list);
        // 取消选择
        track_list.pop_back();
    }
}

vector<vector<int>> BackTrace::permute(vector<int>& nums)
{
    vector<int> TrackList;//路径
    backtrack(nums, TrackList);
    return result;
}


