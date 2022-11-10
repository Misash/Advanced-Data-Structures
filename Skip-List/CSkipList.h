
#ifndef EDA_CSKIPLIST_H
#define EDA_CSKIPLIST_H

#include <bits/stdc++.h>
using namespace std;


template<class K>
struct Node
{

    K key;
    Node **forward;
    Node(K,int);
};


template<class K>
class SkipList
{

    typedef  Node<K> node;

    int maxlevel;
    float p;
    int level;
    node *header;

public:

    SkipList(int, float); //constructor de clase

    int randomLevel(); //

    node* createNode(K, int);

    void insertElement(K); //insertar elemento

    void deleteElement(K); //

    node* searchElement(K); //

    void displayList(); //

private:

    float random();
};



#endif //EDA_CSKIPLIST_H
