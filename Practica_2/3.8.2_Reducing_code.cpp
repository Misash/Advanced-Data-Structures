//
// Created by Misash on 2/09/2022.
//

#include <iostream>


using namespace std;

float Addition(float a, float b){
    return a +b;
}

float Subtraction(float a, float b){
    return a - b;
}

float Multiplication(float a, float b){
    return a * b;
}

float Division(float a, float b){
    return a / b;
}



void code1(float a,float b , int opt){

    cout<<"\nCode 1\n";


    switch( opt )
    {
        case 0: cout<<Addition(a, b); break;
        case 1: cout<<Subtraction(a, b); break;
        case 2: cout<<Multiplication(a, b); break;
        case 3: cout<<Division(a, b); break;
            // more cases operations go here
    }


}


void code2(float a , float b , int opt){

    cout<<"\nCode 2\n";

    typedef float (*lpfnOperation)(float, float);

    lpfnOperation vpf[4] = {&::Addition, &::Subtraction,
                            &::Multiplication, &::Division};
    float c = (*vpf[opt])(a, b);
    cout<<c;
}


int main(){

    /*
     * Se inserrta dos numeros y la opcion
     * 0 : suma
     * 1 : resta
     * 2: multiplicacion
     * 3: division
     */
    float a, b, c; int opt;
    cin >> a >> b>>opt;
    code1(a,b,opt);
    code2(a,b,opt);

}


