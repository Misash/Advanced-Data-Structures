#include <iostream>

using namespace std;

struct FixedVector{
  int  gVec[100];
  int gnCount=0;

  void Insert(int elem){
    if(gnCount < 100) gVec[gnCount++] = elem;
  }

  void Print(){
    cout<<"\n";
    for(int i=0;i<gnCount;i++) cout<<gVec[i]<<" ";
  }
  
};


int main(){

  cout<<"\nFixed Vector\n";

  FixedVector vec;

  vec.Insert(2);
  vec.Insert(4);
  vec.Insert(3);

  vec.Print();
  
}



