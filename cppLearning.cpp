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
    cout << "Student�޲��������ʼ��" << endl;
}

Student::Student(string name)
{
    m_strName = name;
    cout << "Student�в��������ʼ��" << endl;
}

Student::Student(const Student& stu)
{
    cout << "Student���������ʼ��" << endl;
}

Student::~Student()
{
    cout << "Student��������" << endl;
}

void Student::setName(string name)
{
    m_strName = name;
    cout << "����Student������" << endl;
}

string Student::getName(void)
{
    cout << "����Student������" << endl;
    return m_strName;
}



int main()
{
    //// ͨ��new��ʽʵ��������*stu
    //Student* stu = new Student();
    //// ���Ķ�������ݳ�ԱΪ��Ľ������
    //stu->setName("Ľ����");
    //// ��ӡ��������ݳ�Ա
    //cout << stu->getName() << endl;
    //delete stu;
    //stu = NULL;
 //   cout << CDynamicProgramming.FibNumCalculate(20) << endl;
 //   cout << CDynamicProgramming.coinChage(coins,20)<<endl;
    CBackTrace.permute(numbers);
    system("pause");
    return 0;
}