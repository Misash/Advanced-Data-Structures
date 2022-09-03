//
// Created by Misash on 2/09/2022.
//

#ifndef EDA_MYNS_H
#define EDA_MYNS_H


// File MyNS.h
namespace MyNS
{
    int gnCount; // Global counter
// Some small function implemented inline
    double Addition(double a, double b) // Global function
    { return a+b; }
// Some prototypes
    long factorial(int n); // Global function
    class CTest
    {
    public:
        CTest();
        void Method1();
    };

};



#endif //EDA_MYNS_H
