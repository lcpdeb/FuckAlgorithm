#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
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

};