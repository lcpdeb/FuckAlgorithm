#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
using namespace std;

class DynamicProgramming
{
public:
    int FibNumCalculate(int N);
    int coinChage(vector<int>& coinsList, int amount);

};

class BackTrace
{
public:
    vector<vector<int>> permute(vector<int>& nums);
    vector<vector<string>> NQueen(int n);
};

class BFS
{
public:
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    };
    int minDepth(TreeNode* root);
    int openLock(vector<string>& deadends, string target);
};