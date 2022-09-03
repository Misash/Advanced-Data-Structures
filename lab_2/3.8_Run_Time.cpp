//
// Created by Misash on 2/09/2022.
//

#include <iostream>
#include<vector>
#include "MyNS.h"

using namespace std;


long MyNS::factorial(int n)
{
// Some complex code goes here
}
// Constructor for class CTest
MyNS::CTest::CTest()
{
// Initialize something
}
void MyNS::CTest::Method1()
{
// You have to write your code here
}

template<typename t>struct CArray{
    vector<t> v;
    void insert(){}
};


template<typename t>void Insert_Elements(CArray<t> &a){
    a.insert();
}

class CVector
{
private:
    void **m_pVect; // Pointer to the buffer
    int m_nCount, // Control how many elements are actually used
    m_nMax, // Control the number of allocated elements
    m_nDelta, // To control the growing
    m_nElemSize; // Element size
// Pointer to the function to compare
    int (*m_lpfnCompare)(void *, void*);
    void Init(int delta); // Init our private variables, etc
    void Resize(); // Resize the vector when occurs an overflow
    void* DupBlock(void *pElem);

public:
    CVector( int (lpfnCompare)(void *, void*),
             int nElemSize, int delta = 10); // Constructor
    void Insert(void * elem); // Insert a new element
// More methods go here
};

CVector::CVector(int (*lpfnCompare)(void *, void*),
                 int nElemSize, int delta)
{ Init(delta);
    m_lpfnCompare = lpfnCompare;
    m_nElemSize = nElemSize;
}
void CVector::Insert(void *pElem)
{
    if( m_nCount == m_nMax ) // Verify the overflow
        Resize(); // Resize the vector before inserting elem
    m_pVect[m_nCount++] = DupBlock(pElem); // Insert the element at the end
}
void* CVector::DupBlock(void *pElem)
{
    void *p = new char[m_nElemSize];
    return memcpy(p, pElem, m_nElemSize);
}

int fnIntCompare( void *pVar1, void *pVar2 )
{
// < 0 if *(int *)pVar1 < *(int *)pVar2,
// > 0 if *(int *)pVar1 > *(int *)pVar2
// else 0
    return *(int *)pVar1 - *(int *)pVar2;
}



int main(){

    int option;
    enum{INT_TYPE_ENUM,DOUBLE_TYPE_ENUM};


    cin >> option;
    switch(option)
    {
        case INT_TYPE_ENUM:
        { CArray<int> a;
            Insert_Elements<int>(a);
            break;
        }
        case DOUBLE_TYPE_ENUM:
        { CArray<double> a;
            Insert_Elements<double>(a);
            break;
        }
    }

    const unsigned long max = 500 * 1000 * 1000;
    const unsigned long step = 100 * 1000 * 1000;
    unsigned long count;
    for(count = 0L ; count < max ; count++)
        if( count % step == 0L )
            printf("some text ...\n");


}









