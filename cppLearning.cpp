/************************** Library Include ********************************/
#include <stdlib.h>
#include <iostream>

/************************** Module Include *********************************/
#include "user_algorithm.h"

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

class Student
{
public:
    Student();
    Student(string name);
    Student(const Student& stu);
    ~Student();
    void setName(string name);
    string getName(void);
private:
    string m_strName;
};

Student::Student()
{
    m_strName = "NULL";
    cout << "Student无参数构造初始化" << endl;
}

Student::Student(string name)
{
    m_strName = name;
    cout << "Student有参数构造初始化" << endl;
}

Student::Student(const Student& stu)
{
    cout << "Student拷贝构造初始化" << endl;
}

Student::~Student()
{
    cout << "Student析构函数" << endl;
}

void Student::setName(string name)
{
    m_strName = name;
    cout << "设置Student类名称" << endl;
}

string Student::getName(void)
{
    cout << "返回Student类名称" << endl;
    return m_strName;
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
 //   cout << CDynamicProgramming.FibNumCalculate(20) << endl;
 //   cout << CDynamicProgramming.coinChage(coins,20)<<endl;
    CBackTrace.permute(numbers);
    system("pause");
    return 0;
}