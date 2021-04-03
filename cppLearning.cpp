/************************** Library Include ********************************/
#include <stdlib.h>
#include <iostream>

/************************** Module Include *********************************/
#include "user_algorithm.h"
#include "queue.h"

/************************** Namespace Declaration **************************/
using namespace std;

namespace A
{
    uint16_t x = 1;
    void function(void) {
        cout << "A" << endl;
    }
}

namespace B
{
    uint16_t x = 2;
    void function(void) {
        cout << "B" << endl;
    }
    void function2(void) {
        cout << "2B" << endl;

    }
}

/************************** Private Variables ****************************/
int numarray[4] = { 2,7,11,15 };
int targetNum = 9;

extern int* twoSum(int* nums, int numsSize, int target, int* returnSize);

/************************** Private Declarations ************************/
DynamicProgramming CDynamicProgramming;
vector<int> coins = { 1,3,5,7 };

BackTrace CBackTrace;
vector<int> numbers = { 1,2,3 };

BFS CBFS;
vector<string> deadCipher = { "8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888" };



class TEST_ERROR
{
public:
    string a ="error";
    int b = 3;
};

TEST_ERROR test_error;

void test(void) {
    throw string("nmsl");
}

int main()
{
    //// 通过new方式实例化对象*stu
    //Student* stu = new Student();
    //// 更改对象的数据成员为“慕课网”
    //stu->setName("慕课网");
    //// 打印对象的数据成员
    //cout << stu->getName() << endl;
    //delete stu;
    //stu = NULL;

    //cout << CDynamicProgramming.FibNumCalculate(20) << endl;
    //cout << CDynamicProgramming.coinChage(coins,20)<<endl;

    //CBackTrace.permute(numbers);
    //CBackTrace.NQueen(1);

    //BFS::TreeNode tree9(9);
    //BFS::TreeNode tree15(15);
    //BFS::TreeNode tree7(7);
    //BFS::TreeNode tree20(20, &tree15, &tree7);
    //BFS::TreeNode tree3(3, &tree9, &tree20);
    //int result = CBFS.minDepth(&tree3);
    //int t = CBFS.openLock(deadCipher, "8888");


    //try {
    //    cout << test_error.a << endl;
    //    test();
    //}
    //catch (string *s) {
    //    cout << s  << endl;
    //}
    //catch (...) {
    //    cout << "unknown error" << endl;
    //}
    //system("pause");
    typedef string testType;
    testType temp = "";
    Queue<testType>* p = new Queue<testType>(6);
    p->TraverseQueue();
    p->DeQueue(temp);

    p->EnQueue("a");
    p->EnQueue("b");
    p->EnQueue("cdd");
    p->EnQueue("d");
    p->EnQueue("e");
    p->TraverseQueue();

    p->EnQueue("f");
    p->DeQueue(temp);
    p->TraverseQueue();

    p->EnQueue("g");
    p->TraverseQueue();

    p->DeQueue(temp);
    p->DeQueue(temp);
    p->DeQueue(temp);
    p->EnQueue("h");
    p->EnQueue("i");
    p->EnQueue("j");
    p->EnQueue("k");
    p->TraverseQueue();

    return 0;
}