#include <stdlib.h>
#include <iostream>
using namespace std;

int* twoSum(int* nums, int numsSize, int target, int* returnSize) 
{

    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                int* answer = (int*)malloc(2 * sizeof(int));
                //answer[0] = nums[i];
                //answer[1] = nums[j];
                *returnSize = 2;
                return answer;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}


