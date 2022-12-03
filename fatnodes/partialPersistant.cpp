//
// Created by misash on 12/2/22.
//


#include <bits/stdc++.h>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>


using namespace  std;



std::string toString(const time_t &t) {
    std::ostringstream oss;
    oss << t;
    return oss.str();
}


time_t fromString( const std::string& s ) {
    std::istringstream stream( s );
    time_t t;
    stream >> t;
    return t;
}


struct FatNodes{

    string file;
    time_t tiempo;
    map<time_t,string> git;

    void getTime(){
        tiempo = time(NULL);
    }

    void save(string file) {
        getTime();
        std::ifstream src(file, std::ios::binary);
        string newFile =  toString(reinterpret_cast<const time_t>(time)) + "__" + file;
        std::ofstream dst(newFile, std::ios::binary);
        dst << src.rdbuf();
        git[tiempo] = newFile;

        string command = "./script";
        command = command + " "  + newFile;
        system(command.c_str());
    }
    
    void list(){
        for(auto it=git.begin(); it!=git.end(); ++it){
            cout << it->first << " => " << it->second << '\n';
        }
    }

    void back(string version){
        for(auto it=git.begin(); it!=git.end(); ++it){
            cout << it->first << " => " << it->second << '\n';
            if(toString(it->first)  == version){
                string command = "./script2";
                command = command + " "  + git[fromString(version)];
                system(command.c_str());
            }
        }
    }



};



int main(int argc, char** argv) {


    FatNodes git;
    string comando ,value;

    comando = argv[1];
    value = argv[2];

    cout<<"\n"<<comando<<" "<<value;

    if(comando == "save"){
        git.save(value);
    }
    if(comando == "list"){
        git.list();
    }
    if(comando == "back") {
        git.back(value);
    }

}