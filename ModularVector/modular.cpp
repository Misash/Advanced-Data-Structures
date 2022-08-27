//
// Created by misash on 26/08/22.
//
#include <iostream>

using namespace std;


struct Vec{

    int* m_v;
    int m_size;
    int m_nelem;

};

void init(Vec *v,int size){
    v->m_size = size;
    v->m_v=new int[v->m_size];
    v->m_nelem=0;//size
}


int size(Vec *v){
    return v->m_nelem;
}

void resize(Vec *v){
    int* p=new int[2*v->m_size];
    for( int i = 0; i < v->m_size ; i ++){
        p[i]=v->m_v[i];
    }
    delete[] v->m_v;
    v->m_v=p;
    v->m_size= 2*v->m_size;
}

void push_back(Vec *v ,int x){
    if(v->m_nelem == v->m_size)
        resize(v);
    v->m_v[v->m_nelem++]=x;
}


void print(Vec *v){
    cout<<"\n";
    for (int i = 0; i <v->m_nelem; ++i)
        cout<<v->m_v[i]<<" ";
}



int main() {


  cout<<"\nDynamic Vector\n";
  
    Vec v;

    init(&v,3);

    push_back(&v,1);
    push_back(&v,2);
    push_back(&v,3);
    push_back(&v,5);
  
    print(&v);
    // cout<<"\nsize vector: "<<v.size();

    return 0;
}



