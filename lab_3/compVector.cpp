//
// Created by Misash on 9/09/2022.
//

#include <cstdlib>
#include <bits/stdc++.h>
#include <time.h>
#include <chrono>

using namespace  std;

int dim ;


struct point{

    int* dimension;

    point(){
        dimension = new int[dim];
        for (int i = 0; i < dim; ++i) {
            dimension[i] = 1 + (rand() % 20);
        }
    }
};



int main(){

    srand(time(0));
    int n;

    chrono::duration<float,milli> duration;


    //1k
    dim = 1000;
    n = 100;
    point nums[n+1];
    auto start = chrono::system_clock::now();
    for (int i = 1; i < n+1; ++i) {
        int d;
        for (int j = 0; j < dim; ++j) {
            d += pow(nums[i].dimension[j] - nums[i].dimension[j],2);
        }
        d = sqrt(d);
    }
    auto end = chrono::system_clock::now();
    duration = end - start;
    cout<<"Tiempo de carga de la matriz con "<< n << " datos: " << duration.count() << " ms\n";


    //10k
    dim = 10000;
    n = 1000;
    point nums2[n+1];
    start = chrono::system_clock::now();
    for (int i = 1; i < n+1; ++i) {
        int d;
        for (int j = 0; j < dim; ++j) {
            d += pow(nums2[i].dimension[j] - nums2[i].dimension[j],2);
        }
        d = sqrt(d);
    }
    end = chrono::system_clock::now();
    duration = end - start;
    cout<<"Tiempo de carga de la matriz con "<< n << " datos: " << duration.count() << " ms\n";

    //50k
    dim = 50000;
    n = 10000;
    point nums3[n+1];
    start = chrono::system_clock::now();
    for (int i = 1; i < n+1; ++i) {
        int d;
        for (int j = 0; j < dim; ++j) {
            d += pow(nums3[i].dimension[j] - nums3[i].dimension[j],2);
        }
        d = sqrt(d);
    }
    end = chrono::system_clock::now();
    duration = end - start;
    cout<<"Tiempo de carga de la matriz con "<< n << " datos: " << duration.count() << " ms\n";



}