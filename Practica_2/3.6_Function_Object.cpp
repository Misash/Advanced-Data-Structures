//
// Created by Misash on 2/09/2022.
//

#include <vector>
#include <iostream>
using namespace std;

class CMyComplexDataStructure
{
    vector<float> m_container;
public:
    void Insert(float fVal) { m_container.push_back(fVal); }
    template <typename objclass>
    void sumone(objclass funobj)
    {
        vector<float>::iterator iter = m_container.begin();
        for (; iter != m_container.end() ; iter++)
            funobj(*iter);
    }

    void print(){
        cout<<"\n";
        for(float & iter : m_container){
            cout<<iter<<" ";
        }
    }
};
template <typename objclass>
class funcobjclass
{
public:
    void operator ()(objclass& objinstance)
    {
        objinstance++;
    }
};

int main(int argc, char* argv[])
{
    CMyComplexDataStructure ds;
    ds.Insert(3.5);
    ds.Insert(4.5);
    ds.Insert(6.5);
    ds.Insert(3.9);
    ds.print();
    funcobjclass<float> x;
    ds.sumone(x);

    ds.print();




    return 0;
}
