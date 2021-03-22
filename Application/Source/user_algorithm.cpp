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

/********************************************************************************************************************************************************/

bool isContained(vector<int>& list, int element)
{
    return (find(list.begin(), list.end(), element) != list.end());
}

// 路径：记录在 track_list 中
// 选择列表：nums 中不存在于 track_list 的那些元素
// 结束条件：nums 中的元素全都在 track_list 中出现
void backtrack(vector<int> &nums, vector<int>& track_list, vector<vector<int>>& result)
{
    //触发结束条件，所有的数都已经被放进track list中
    if (track_list.size() == nums.size()) {
        //将当前路径放至结果
        result.push_back(track_list);
        return;
    }
    //遍历所有可能的选择
    for (int i = 0; i < nums.size(); i++) {
        //排除包含的已经选择过的决策节点
        if (isContained(track_list, nums[i])) {
            continue;
        }
        //做选择，加入当前决策节点
        track_list.push_back(nums[i]);
        // 进入下一层决策树
        backtrack(nums, track_list, result);
        // 从回溯中出来说明已经当前决策已被包含，撤销上一次选择，返回上一个决策节点
        track_list.pop_back();
    }
}

vector<vector<int>> BackTrace::permute(vector<int>& nums)
{
    vector<vector<int>> result;
    vector<int> TrackList;//路径
    backtrack(nums, TrackList, result);
    return result;
}

/********************************************************************************************************************************************************/
vector<vector<string>> mapResult;

bool isValid(int iCol, int iRow, vector<string>& current_board)
{
    int n = current_board.size() - 1;
    /* 当前坐标上方有Q */
    for (int i = 0; i < iRow; i++) {
        if (current_board[i][iCol] == 'Q') {
            return false;
        }
    }
    /* 当前坐标左上方有Q */
    for (int j = 0; j < min(iRow, iCol); j++) {
        if (current_board[iRow - j - 1][iCol - j - 1] == 'Q') {
            return false;
        }
    }
    /* 当前坐标右上方有Q */
    for (int k = 0; k < min(iRow, n - iCol); k++) {
        if (current_board[iRow - k - 1][iCol + k + 1] == 'Q') {
            return false;
        }
    }
    return true;
}

void BackTraceNQueen(int row, vector<string>& board)
{
    //触发结束条件
    if (row == board.size()) {//面板大小等于当前行数
        mapResult.push_back(board);//计入结果中
        return;
    }
    int totalColumnNumber = board[row].size();//得到当前面板行的总列数
    for (int column = 0 ; column < totalColumnNumber; column++) {
        /* 检查当前行列是否在面板上合法 */
        if (!isValid(column, row, board)) {
            continue;
        }
        /* 合法则填入当前面板 */
        board[row][column] = 'Q';
        /* 进入下一行 */
        BackTraceNQueen(row + 1, board);
        /* 撤销已做的选择，返回上级节点 */
        board[row][column] = '.';
    }
}

vector<vector<string>> BackTrace::NQueen(int n)
{
    //初始化棋盘，n x n 个 .
    vector<string> Board(n, string(n,'.'));
    BackTraceNQueen(0, Board);
    return mapResult;
}

/********************************************************************************************************************************************************/
int BFS::minDepth(TreeNode* root)
{
    /* 空指针 */
    if (root == nullptr) {
        return 0;
    }

    /* 声明que队列的每一个元素是TreeNode* 和int配对的队列 */
    queue<pair<TreeNode*, int> > treeQueue;
    /* 从当根节点出发，因为root本身就是一层，所以深度为1 */
    treeQueue.emplace(root, 1);

    while (!treeQueue.empty()) {
        TreeNode* currentTreeNode = treeQueue.front().first;//获取队列中第一个元素注册的树
        int treeDepth = treeQueue.front().second;//获取队列中第一个元素注册的深度
        treeQueue.pop();//pop出第一个元素
        /* 判断当前二叉树的左子树和右子树，都为空即到达终点 */
        if (currentTreeNode->left == nullptr && currentTreeNode->right == nullptr) {
            return treeDepth;
        }
        /* 遍历左子树和右子树，非空则放入队列，深度+1 */
        if (currentTreeNode->left != nullptr) {
            treeQueue.emplace(currentTreeNode->left, treeDepth + 1);
        }
        if (currentTreeNode->right != nullptr) {
            treeQueue.emplace(currentTreeNode->right, treeDepth + 1);
        }
    }

    return 0;
}


/* 将第i位密码上拨1位 */
string plusOne(string s, int i)
{
    /* i ∈ [0,3] */
    if (s[i] == '9') {
        s[i] = '0';
    }
    else {
        s[i]++;
    }
    return s;
}

/* 将第i位密码下拨1位 */
string minusOne(string s, int i)
{
    /* i ∈ [0,3] */
    if (s[i] == '0') {
        s[i] = '9';
    }
    else {
        s[i]--;
    }
    return s;
}

int BFS::openLock(vector<string>& deadends, string target)
{
    unordered_set<string> deadSet(deadends.begin(), deadends.end());
    unordered_set<string> closeList(deadends.begin(), deadends.end());
    queue<string> openList;
    string currentCipher = "0000";

    /* 从起点开始 */
    int step = 0;
    openList.push(currentCipher);
    closeList.insert(currentCipher);

    while (!openList.empty()) {
        int listSize = openList.size();
        for (int i = 0; i < listSize; i++) {
            /* 取得第一个元素 */
            currentCipher = openList.front();
            openList.pop();

            /* 检查是否已经在dead ends中 */
            if (deadSet.count(currentCipher)) {
                continue;
            }
            /* 检查是否就是目标密码 */
            if (currentCipher == target) {
                return step;
            }

            for (int j = 0; j < 4; j++) {
                string up = plusOne(currentCipher, j);
                if (!closeList.count(up)) {
                    openList.push(up);
                    closeList.insert(up);
                }
                string down = minusOne(currentCipher, j);
                if (!closeList.count(down)) {
                    openList.push(down);
                    closeList.insert(down);
                }
            }
        }
        step++;
    }
    return -1;
}