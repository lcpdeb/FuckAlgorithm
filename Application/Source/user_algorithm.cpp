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
    ���� k ����ֵ��Ӳ�ң���ֵ�ֱ�Ϊ c1, c2 ... ck��ÿ��Ӳ�ҵ��������ޣ��ٸ�һ���ܽ�� amount������������Ҫ��öӲ�Ҵճ��������������ܴճ����㷨���� - 1 ��
*/
int DynamicProgramming::coinChage(vector<int>& coinsList, int amount)
{
    // �����СΪ amount + 1����ʼֵΪ amount + 1
    // ��Ϊ�ճ� amount ����Ӳ�������ֻ���ܵ��� amount��ȫ�� 1 Ԫ��ֵ��Ӳ�ң������Գ�ʼ��Ϊ amount + 1 ���൱�ڳ�ʼ��Ϊ��������ں���ȡ��Сֵ��
    vector<int> result(amount + 1, amount + 1);
    // base case
    result[0] = 0;
    if (amount == 0) {//0Ԫ0��Ӳ�ҿɽ�
        return 0;
    }
    if (amount < 0) {//���С��0ʱ�޽�
        return -1;
    }
    
    // ��� for ѭ���ڱ�������״̬������ȡֵ
    for (int i = 0; i < result.size(); i++) {
        for (int coin : coinsList) {
            if (i < coin) {//Ҫ����С��Ӳ�����ʱ�޽�
                continue;
            }
            /*
            * ������
                ��1,3,5,7
                ��
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
            result[i] = min(result[i], result[i - coin] + 1);//��ʼֵΪ����󣬴������ͣ����-��ǰ���+1����֮ǰ�Ľ��+��ǰ����Ӳ��1ö���бȽϣ�ѭ������С��һ�ֿ���
        }
    }
    /* �޽�ʱ����-1 */
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

// ·������¼�� track_list ��
// ѡ���б�nums �в������� track_list ����ЩԪ��
// ����������nums �е�Ԫ��ȫ���� track_list �г���
void backtrack(vector<int> &nums, vector<int>& track_list, vector<vector<int>>& result)
{
    //�����������������е������Ѿ����Ž�track list��
    if (track_list.size() == nums.size()) {
        //����ǰ·���������
        result.push_back(track_list);
        return;
    }
    //�������п��ܵ�ѡ��
    for (int i = 0; i < nums.size(); i++) {
        //�ų��������Ѿ�ѡ����ľ��߽ڵ�
        if (isContained(track_list, nums[i])) {
            continue;
        }
        //��ѡ�񣬼��뵱ǰ���߽ڵ�
        track_list.push_back(nums[i]);
        // ������һ�������
        backtrack(nums, track_list, result);
        // �ӻ����г���˵���Ѿ���ǰ�����ѱ�������������һ��ѡ�񣬷�����һ�����߽ڵ�
        track_list.pop_back();
    }
}

vector<vector<int>> BackTrace::permute(vector<int>& nums)
{
    vector<vector<int>> result;
    vector<int> TrackList;//·��
    backtrack(nums, TrackList, result);
    return result;
}

/********************************************************************************************************************************************************/
vector<vector<string>> mapResult;

bool isValid(int iCol, int iRow, vector<string>& current_board)
{
    int n = current_board.size() - 1;
    /* ��ǰ�����Ϸ���Q */
    for (int i = 0; i < iRow; i++) {
        if (current_board[i][iCol] == 'Q') {
            return false;
        }
    }
    /* ��ǰ�������Ϸ���Q */
    for (int j = 0; j < min(iRow, iCol); j++) {
        if (current_board[iRow - j - 1][iCol - j - 1] == 'Q') {
            return false;
        }
    }
    /* ��ǰ�������Ϸ���Q */
    for (int k = 0; k < min(iRow, n - iCol); k++) {
        if (current_board[iRow - k - 1][iCol + k + 1] == 'Q') {
            return false;
        }
    }
    return true;
}

void BackTraceNQueen(int row, vector<string>& board)
{
    //������������
    if (row == board.size()) {//����С���ڵ�ǰ����
        mapResult.push_back(board);//��������
        return;
    }
    int totalColumnNumber = board[row].size();//�õ���ǰ����е�������
    for (int column = 0 ; column < totalColumnNumber; column++) {
        /* ��鵱ǰ�����Ƿ�������ϺϷ� */
        if (!isValid(column, row, board)) {
            continue;
        }
        /* �Ϸ������뵱ǰ��� */
        board[row][column] = 'Q';
        /* ������һ�� */
        BackTraceNQueen(row + 1, board);
        /* ����������ѡ�񣬷����ϼ��ڵ� */
        board[row][column] = '.';
    }
}

vector<vector<string>> BackTrace::NQueen(int n)
{
    //��ʼ�����̣�n x n �� .
    vector<string> Board(n, string(n,'.'));
    BackTraceNQueen(0, Board);
    return mapResult;
}

/********************************************************************************************************************************************************/
int BFS::minDepth(TreeNode* root)
{
    /* ��ָ�� */
    if (root == nullptr) {
        return 0;
    }

    /* ����que���е�ÿһ��Ԫ����TreeNode* ��int��ԵĶ��� */
    queue<pair<TreeNode*, int> > treeQueue;
    /* �ӵ����ڵ��������Ϊroot�������һ�㣬�������Ϊ1 */
    treeQueue.emplace(root, 1);

    while (!treeQueue.empty()) {
        TreeNode* currentTreeNode = treeQueue.front().first;//��ȡ�����е�һ��Ԫ��ע�����
        int treeDepth = treeQueue.front().second;//��ȡ�����е�һ��Ԫ��ע������
        treeQueue.pop();//pop����һ��Ԫ��
        /* �жϵ�ǰ��������������������������Ϊ�ռ������յ� */
        if (currentTreeNode->left == nullptr && currentTreeNode->right == nullptr) {
            return treeDepth;
        }
        /* ���������������������ǿ��������У����+1 */
        if (currentTreeNode->left != nullptr) {
            treeQueue.emplace(currentTreeNode->left, treeDepth + 1);
        }
        if (currentTreeNode->right != nullptr) {
            treeQueue.emplace(currentTreeNode->right, treeDepth + 1);
        }
    }

    return 0;
}


/* ����iλ�����ϲ�1λ */
string plusOne(string s, int i)
{
    /* i �� [0,3] */
    if (s[i] == '9') {
        s[i] = '0';
    }
    else {
        s[i]++;
    }
    return s;
}

/* ����iλ�����²�1λ */
string minusOne(string s, int i)
{
    /* i �� [0,3] */
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

    /* ����㿪ʼ */
    int step = 0;
    openList.push(currentCipher);
    closeList.insert(currentCipher);

    while (!openList.empty()) {
        int listSize = openList.size();
        for (int i = 0; i < listSize; i++) {
            /* ȡ�õ�һ��Ԫ�� */
            currentCipher = openList.front();
            openList.pop();

            /* ����Ƿ��Ѿ���dead ends�� */
            if (deadSet.count(currentCipher)) {
                continue;
            }
            /* ����Ƿ����Ŀ������ */
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