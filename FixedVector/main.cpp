//
// Created by misash on 26/08/22.
//
#include <iostream>

using namespace std;



template <typename T>
class DynamicVector{
public:

    DynamicVector(T size){
        m_size = size;
        m_v=new T[m_size];
        m_nelem=0;//size
    }

    ~DynamicVector(){
        delete[] m_v;
    }

    int size(){
        return m_nelem;
    }

    void resize(){
        T* p=new T[2*m_size];
        for( int i = 0; i < m_size ; i ++){
            p[i]=m_v[i];
        }
        delete[] m_v;
        m_v=p;
        m_size= 2*m_size;
    }

    void push_back(int x){
        if(m_nelem == m_size)
            resize();
        m_v[m_nelem++]=x;
    }


    void print(){
        cout<<"\n";
        for (int i = 0; i <m_nelem; ++i)
            cout<<m_v[i]<<" ";
    }

private:
    T* m_v;
    int m_size;
    int m_nelem;

};



int main() {


  cout<<"\nDynamic Vector\n";
  
    DynamicVector<int> v(3);

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(5);
    

    v.print();
    // cout<<"\nsize vector: "<<v.size();

    return 0;
}

