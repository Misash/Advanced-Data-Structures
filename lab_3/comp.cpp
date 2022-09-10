//
// Created by Misash on 9/09/2022.
//

#include <cstdlib>
#include <bits/stdc++.h>
#include <time.h>
#include <chrono>

using namespace  std;

struct point{
    int x,y,z;

    point(){
        x = 1 + (rand() % 20);
        y = 1 + (rand() % 20);
        z = 1 + (rand() % 20);
    }
};







int main(){

    srand(time(0));


    point nums[50001];
    chrono::duration<float,milli> duration;
    int n;

    //1k
    auto start = chrono::system_clock::now();
//        cout<<"\n"<<nums[i].x<<" "<<nums[i].y<<" "<<nums[i].z;
    n = 1000;
    for (int i = 1; i < n+1; ++i) {
        int d = sqrt(pow(nums[0].x-nums[i].x,2) +  pow(nums[0].y-nums[i].y,2) + pow(nums[0].z-nums[i].z,2));
    }
    auto end = chrono::system_clock::now();
    duration = end - start;
    cout<<"Tiempo de carga de la matriz con "<< n << " datos: " << duration.count() << " ms\n";


    //10k
    start = chrono::system_clock::now();
    n = 10000;
    for (int i = 1; i < n+1; ++i) {
        int d = sqrt(pow(nums[0].x-nums[i].x,2) +  pow(nums[0].y-nums[i].y,2) + pow(nums[0].z-nums[i].z,2));
    }
    end = chrono::system_clock::now();
    duration = end - start;
    cout<<"Tiempo de carga de la matriz con "<< n << " datos: " << duration.count() << " ms\n";



    //50k
    start = chrono::system_clock::now();
    n = 50000;
    for (int i = 1; i < n+1; ++i) {
        int d = sqrt(pow(nums[0].x-nums[i].x,2) +  pow(nums[0].y-nums[i].y,2) + pow(nums[0].z-nums[i].z,2));
    }
    end = chrono::system_clock::now();
    duration = end - start;
    cout<<"Tiempo de carga de la matriz con "<< n << " datos: " << duration.count() << " ms\n";



}