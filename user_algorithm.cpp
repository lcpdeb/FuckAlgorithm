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


vector<vector<int>> result;

bool isContained(vector<int>& list, int element)
{
    return (find(list.begin(), list.end(), element) != list.end());
}

// ·������¼�� track_list ��
// ѡ���б�nums �в������� track_list ����ЩԪ��
// ����������nums �е�Ԫ��ȫ���� track_list �г���
void backtrack(vector<int> &nums, vector<int>& track_list)
{
    //������������
    if (track_list.size() == nums.size()) {
        result.push_back(track_list);
        return;
    }
    for (int i = 0; i < nums.size(); i++) {
        //�ų��Ѿ�������ѡ��
        if (isContained(track_list, nums[i])) {
            continue;
        }
        //��ѡ��
        track_list.push_back(nums[i]);
        // ������һ�������
        backtrack(nums, track_list);
        // ȡ��ѡ��
        track_list.pop_back();
    }
}

vector<vector<int>> BackTrace::permute(vector<int>& nums)
{
    vector<int> TrackList;//·��
    backtrack(nums, TrackList);
    return result;
}


