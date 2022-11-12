//
// Created by misash on 10/11/22.
//


#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>


using namespace std;

struct Pixel{
    double x;
    double y;
};


static const inline double distance(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;

    return sqrt(dx * dx + dy * dy);
}

const inline int region_query(const std::vector<Pixel> &input, int p, std::vector<int> &output, double eps)
{
    for(int i = 0; i < input.size(); i++){

        if(distance(input[i].x, input[i].y, input[p].x, input[p].y) < eps){
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

int dbscan(const std::vector<Pixel> &input, std::vector<int> &labels, double eps, int min)
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

    return cluster - 1;
}




int main(){

    vector<Pixel> points(10);

    points[0].x = 20; points[0].y = 21;
    points[1].x = 20; points[1].y = 25;
    points[2].x = 28; points[2].y = 22;
    points[3].x = 30; points[3].y = 52;
    points[4].x = 26; points[4].y = 70;
    points[5].x = 30; points[5].y = 75;
    points[6].x = 0; points[6].y = 70;
    points[7].x = 70; points[7].y = 50;
    points[8].x = 67; points[8].y = 69;
    points[9].x = 80; points[9].y = 35;

    vector<int> labels;

    int num = dbscan(points, labels, 20.0, 3);

    cout<<"cluster size is "<<num<<endl;

    for(int i = 0; i < (int)points.size(); i++){
        std::cout<<"Pixel("<<points[i].x<<", "<<points[i].y<<"): "<<labels[i]<<std::endl;
    }

    return 0;

}