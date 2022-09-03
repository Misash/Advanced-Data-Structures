//
// Created by Misash on 2/09/2022.
//

#include <vector>
#include <iostream>
using namespace std;


template <typename T> struct NODE
{
    T m_data;
    struct NODE<T> *m_pNext;
    inline static long id = 0; // Node id
    NODE()
            : m_data(0), m_pNext(NULL) {}

};


template <typename T> class CLinkedList
{
private:
    NODE<T> *m_pRoot;
public:

};



template <typename T> class CLinkedList2
{
private:
    struct NODE
    {
        T m_data;
        struct NODE * m_pNext;

    };
    NODE* m_pRoot;
public:
};



// implementing a Binary Tree
template <typename T>
class CBinaryTree
{
private:
    struct NODE
    {
        T m_data;
        struct NODE * m_pLeft, m_pRight;
// Some methods go here
    };
    NODE* m_pRoot;
public:
};



