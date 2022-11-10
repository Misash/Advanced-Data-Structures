//
// Created by misash on 11/4/22.
//

#include <bits/stdc++.h>
#include <random>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>
#include "tree.cpp"
using namespace std;

CBinTree<int> tree;
int xx,yy;
vector<int> range;

//int cont;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distrib(0, 10);

//vector<int> generadorPuntos(int dimensiones){
//    vector<int> punto;
//    for (int a = 0; a <= dimensiones; ++a){
////        int rand = distrib(gen);
//        punto.push_back(rand);
//    }
//    return punto;
//}
int generadorAleatorio(int max){
    uniform_int_distribution<> distrib1(0, max);
    int p= distrib1(gen);
    return p;
}
float distanciaEuclidiana(int dimensiones, vector<int> a, vector<int> b){
    int dist = 0;
    for (int i = 0; i < dimensiones; ++i){
        int t = a[i] - b[i];
        dist += (t * t);
    }
    return (sqrt(dist));
}
void print_punto(int dimensiones, vector<int> a){
    cout<<"{";
    for (int i = 0; i < dimensiones-1; ++i){
        cout<<a[i]<<",";
    }
    cout<<a[dimensiones-1]<<"}";
}
string to_Binary(int n){
    return bitset<4>(n).to_string();
}
unsigned long long to_long_long(string s){
    return bitset<64>(s).to_ullong();
}
void crear_Z_curve(vector<int> punto, vector<vector<int>> &ejes,int dimensiones){
    for (int i = 0; i < dimensiones; i++){
        if(find(ejes[i].begin(), ejes[i].end(), punto[i]) == ejes[i].end()){
            ejes[i].push_back(punto[i]);
        }
    }
}
unsigned long long reduccion(vector<string> punto_z, int dimensiones){
    string resultado;
    for(int i=0;i<4;i++){
        for(int j=dimensiones-1;j>=0;j--){
            resultado.push_back(punto_z[j].at(i));
        }
    }
//    cout<<" Punto en Z order --> "<< resultado<<endl;
    return to_long_long(resultado);
}
vector<unsigned long long> Z_order(vector<vector<int>>& puntos,vector<vector<int>>& ejes,int dimensiones){
    vector<unsigned long long> puntos_z;
    for (int i = 0; i < puntos.size(); i++){
        vector<int> p=puntos[i];
        print_punto(dimensiones,p); cout<<endl;
        vector<string> punto_z;
        for (int j = 0; j < dimensiones; j++){
            int k = 0;
            for (; k < ejes[j].size(); k++){
                if(ejes[j][k]==p[j]){break;}
            }
            cout<<"index eje : "<< k<< " ->";
            punto_z.push_back(to_Binary(k));

            //insercion
//            tree.Ins(k);

            cout<<" // binario eje "<< j<<" --> "<< punto_z[punto_z.size()-1]<<endl;
        }
        puntos_z.push_back(reduccion(punto_z,dimensiones));
        cout<<" Punto en Z order --> "<< puntos_z[puntos_z.size()-1]<<endl;
    }
    cout<<"\nPUNTOS Z EN Z ORDER:";
    for(auto zs: puntos_z){
        cout<<zs<<" ";
    }
    return puntos_z;
}

vector<pair<float,int>> knn_q(vector<vector<int>>& puntos,vector<int> punto, int dimensiones, int k){
    vector<pair<float,int>> vecinos;
    for(int i=0;i<puntos.size();i++){
        float dis=distanciaEuclidiana(dimensiones,puntos[i],punto);
        vecinos.push_back({dis,i});
    }
    sort(vecinos.begin(),vecinos.end());
    vecinos.erase(vecinos.begin());
    vecinos.erase(vecinos.begin()+k,vecinos.end());
    return vecinos;
}
vector<pair<float,int>> knn_q_z(vector<unsigned long long> puntos_z, int punto, int k){
    vector<pair<float,int>> vecinos;
    for(int i=0;i<puntos_z.size();i++){
        float dis=puntos_z[i]-punto;
        if(dis < 0) dis*=-1;
        vecinos.push_back({dis,i});
    }
    sort(vecinos.begin(),vecinos.end());
    vecinos.erase(vecinos.begin());
    vecinos.erase(vecinos.begin()+k,vecinos.end());
    return vecinos;
}

int comparar_knn(vector<pair<float,int>> knn,vector<pair<float,int>>knn_z){
    int cont=0;
    for(int i=0; i< knn.size();i++){
        int it= knn[i].second;
        for(int j=0 ; j<knn_z.size();j++ ){
            int it_z=knn_z[j].second;
            if(it == it_z){
                cont++;
                break;
            }
        }
    }
    return cont;
}

int main(){

    int num_puntos = 7;
    int a,b;

    vector<int> v_dimenciones = {2,3,4};
    for (int j = 0; j < v_dimenciones.size(); j++){
        cout<<"Z Order para "<< v_dimenciones[j]<< " dimensiones."<<endl;
        vector<vector<int>> puntos;
        vector<unsigned long long> puntos_z;
        int dimensiones = v_dimenciones[j];
        vector<vector<int>> ejes(dimensiones);
        vector<int> p;
        for (int i = 0; i < num_puntos; i++){
//            vector<int> p=generadorPuntos(dimensiones);
            for(int j=0; j < num_puntos ; j++){
                vector<int> p= { i,j};
                puntos.push_back(p);
                crear_Z_curve(p,ejes,dimensiones);
            }

//            p.push_back(i);

        }

        for (int i = 0; i < dimensiones; i++){
            sort(ejes[i].begin(),ejes[i].end());
        }

        cout<<"Ejes :"<<endl;
        for (int i = 0; i < dimensiones; i++){
            print_punto(ejes[i].size(),ejes[i]);
            cout<<endl;
        }


        puntos_z=Z_order(puntos,ejes,dimensiones);

//        cout<<"\n z puntos: \n";
        vector<int> puntos_muestra;
//        for(auto zs:puntos_z){
//            tree.Ins(zs);
//        }
//        cout<<"\n";
//        cout<<"ingrese rango: "; cin>>a>>b;
//        cout<<"\nrange query: \n";
//        vector<int> nums;
//        tree.FindRange(a,b,nums);
//        for(int num: nums){
//            cout<<num<<" ";
//        }
//        cout<<"\n";

        for (int i = 0; i < 10 ;){
            int t=generadorAleatorio(num_puntos-1);
            //cout<<t<<endl;
            if(find(puntos_muestra.begin(), puntos_muestra.end(), t) == puntos_muestra.end()){
                puntos_muestra.push_back(t);
                i++;
            }
        }
        print_punto(puntos_muestra.size(),puntos_muestra);cout<<endl;

        cout<<"Mapeo :"<<endl;
        for (int i = 0; i < num_puntos ;i++){
            print_punto(dimensiones,puntos[i]);
            cout<<" --> "<<puntos_z[i]<<endl;
        }


        vector<int> knn_number = {5, 10};
        vector<float> promedios(4,0.0);
        for (int m = 0; m < 10 ;m++){
            vector<int> knn_comparacion;
            int it=puntos_muestra[m];
            vector<int> p=puntos[it];
            int p_z=puntos_z[it];
            //print_punto(dimensiones,p);
            //cout<<" --> "<<p_z<<endl;
            for (int k = 0; k <knn_number.size() ;k++){
                vector<pair<float,int>> knn = knn_q(puntos,p,dimensiones,knn_number[k]);
                vector<pair<float,int>> knn_z = knn_q_z(puntos_z,p_z,knn_number[k]);
                int comp=comparar_knn(knn,knn_z);
                knn_comparacion.push_back((comp*100)/knn_number[k]);
                //cout<< knn_number[k]<<" knn Comparacion "<< knn_comparacion[knn_comparacion.size()-1]<<" %"<<endl;
                promedios[k]+=float(knn_comparacion[knn_comparacion.size()-1]);
            }
        }

//        cout<<"\n puntos : \n";
//        cout<<puntos.size();

        //cout<<"Promedios :"<<endl;
        float general=0.0;
        for (int i = 0; i < knn_number.size() ;i++){
            promedios[i]/=10;
            //cout<< knn_number[i]<<" knn Comparacion = "<<promedios[i]<<" %"<<endl;
            general+=promedios[i];
        }
       // cout<<"General ->" <<general/4<<" %"<<endl;
    }
    return 0;
}


