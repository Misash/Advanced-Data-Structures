
//
// Created by misash on 10/11/22.
//


#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include "../lab_5/bitmap.cpp"

using namespace std;



static const inline double distance(double x1, double y1 ,double z1, double x2, double y2,double z2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dz = z2 - z1;

    return sqrt(dx * dx + dy * dy + dz+dz);
}

const inline int region_query(const std::vector<Pixel> &input, int p, std::vector<int> &output, double eps)
{
    for(int i = 0; i < input.size(); i++){

        if(distance(input[i].red, input[i].green,input[i].blue , input[p].red, input[p].green, input[p].blue) < eps){
            output.push_back(i);
        }
    }

    return output.size();
}

bool expand_cluster(const std::vector<Pixel> &input, int p, std::vector<int> &output, int cluster, double eps, int min)
{
    std::vector<int> seeds;

    if(region_query(input, p, seeds, eps) < min){

        //this point is noise
        output[p] = -1;
        return false;

    }else{

        //set cluster id
        for(int i = 0; i < seeds.size(); i++){
            output[seeds[i]] = cluster;
        }

        //delete paint from seeds
        seeds.erase(std::remove(seeds.begin(), seeds.end(), p), seeds.end());

        //seed -> empty
        while(seeds.size() > 0){

            int cp = seeds.front();
            std::vector<int> result;

            if(region_query(input, cp, result, eps) >= min){

                for(int i = 0; i < result.size(); i++){

                    int rp = result[i];

                    //this paint is noise or unmarked point
                    if(output[rp] < 1){

                        //unmarked point
                        if(!output[rp]){
                            seeds.push_back(rp);
                        }

                        //set cluster id
                        output[rp] = cluster;
                    }
                }
            }

            //delete point from seeds
            seeds.erase(std::remove(seeds.begin(), seeds.end(), cp), seeds.end());
        }
    }

    return true;
}



int dbscan(vector<Pixel>& salida ,const std::vector<Pixel> &input, std::vector<int> &labels, double eps, int min)
{
    int size = input.size();
    int cluster = 1;

    std::vector<int> state(size);

    for(int i = 0; i < size; i++){

        //set a cluster group
        if(!state[i]){

            if(expand_cluster(input, i, state, cluster, eps, min)){
                cluster++;
            }
        }
    }

    labels = state;



    int r = 0,g=255,b=240;
    salida.resize(input.size());
    for (int i = 0; i < input.size(); ++i) {
        if (labels[i] == -1){
            labels[i] = 255;
        }
        salida[i] = Pixel((labels[i]+0)%254,(labels[i]*30)%254,(labels[i]*50)%254);
    }

    return cluster - 1;
}







template<class T>
void Matrix2Vector(vector<vector<T>> &m , vector<T> &v){
    for (auto vec : m) {
        for (auto elem : vec) {
            v.push_back(elem);
        }
    }
}

template<class T>
void vector2Matrix(vector<T>& v, vector<vector<T>>& m){

    int x = 0;
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m[0].size(); ++j) {
            m[i][j] = v[x++];
        }
    }
}




int main(){


    Bitmap image;
    image.open("xd.bmp");
    if(!image.isImage()) return 0;

    //get the matrix of pixels
    vector<vector<Pixel>>grid = image.pixels;
    int f = grid.size(), c = grid[0].size();
    cout<<"\nfila: "<<grid.size();
    cout<<"\ncol: "<<grid[0].size();

    vector<Pixel> grid1d;
    Matrix2Vector(grid,grid1d);


    vector<int> labels;
    int num = 0;
    vector<Pixel> salida;
    num = dbscan(salida,grid1d, labels,5.0,5);

    cout<<"\nCLUSTERS: "<<num<<endl;


    vector<vector<Pixel>> grid2(f,vector<Pixel>(c));
    vector2Matrix(salida,grid2);


    image.fromPixelMatrix(grid2);
    image.save("dbscan.bmp");


    return 0;

}