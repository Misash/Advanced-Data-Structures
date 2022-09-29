//
// Created by misash on 29/09/22.
//

#include <iostream>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;



struct Node{
    //childrens:
    // 0 1
    // 2 3
    Node* children[4];
    int x ,y,dim;
    int val;
    Node(int x ,int y, int dim) : x(x) , y(y) ,dim(dim) {}

};

class QuadTree{
public:
    Node* root;
    deque<deque<int>> grid;
    int n, size , depth;

    QuadTree(deque<deque<int>> grid){
        this->grid = grid;
        this->n = grid.size();
        root = new Node(0,0,n);
        size = depth = 0;
        buildTreePyramid(root);
    }

    bool isLeaf(Node* node){
        int sum =0;
        for (int i = node->x; i <node->x+node->dim  ; ++i) {
            for (int j = node->y; j < node->y + node->dim ; ++j) {
                sum += grid[i][j];
            }
        }
        return (grid[node->x][node->y] * pow(node->dim,2) == sum );
    }

    void split(Node* node){
        if(!node->dim) return;
        depth++;
        node->children[0] = new Node(node->x,node->y,node->dim/2);
        node->children[1] = new Node(node->x,node->y + node->dim/2  ,node->dim/2);
        node->children[2] = new Node(node->x + node->dim/2 ,node->y,node->dim/2);
        node->children[3] = new Node(node->x + node->dim/2 ,node->y + node->dim/2 ,node->dim/2);
    }

    void buildTreePyramid(Node* node){
        size ++;
        if(isLeaf(node)) return;

        cout<<"\n---------------------------------\n";

//        for (int i = node->x; i < node->x+node->dim ; ++i) {
//            for (int j = node->y; j < node->y + node->dim; ++j) {
//                cout<<grid[i][j]<<" ";
//            }
//            cout<<"\n";
//        }


        split(node);

        if(node->children[0]){
            for (int i = 0; i < 4 ; ++i) {
                buildTreePyramid(node->children[i]);
            }
        }


    }

    void InOrderTrack(Node* data , vector<vector<Node*>> &v ,  int i, int &j)
    {
        if ( !data ) return;
        InOrderTrack(data->children[0],v,i+1,j);
        InOrderTrack(data->children[1],v,i+1,j);
        v[i][j++] = data;
        InOrderTrack(data->children[2],v,i+1,j);
        InOrderTrack(data->children[3],v,i+1,j);
    }


    void Print() {
        int height = depth + 1, j = 0;
        vector<vector<Node*>> vec(height, vector<Node*>(size, nullptr));

        InOrderTrack(root, vec, 0, j);

        cout << "\n\n";
        for (int i = 0; i < height; ++i) {
            for (j = 0; j < size; ++j){
                if( vec[i][j]){
                    PrintNode(vec[i][j]);
                    cout<<"\n";
                }
            }
            cout << "\n-------------------\n";
        }
    }

    void PrintNode(Node* node){
        for (int i = node->x; i < node->x+node->dim ; ++i) {
            for (int j = node->y; j < node->y + node->dim; ++j) {
                cout<<grid[i][j]<<" ";
            }
            cout<<"\n";
        }
    }

};






int main(){

    deque<deque<int>> grid= {{1,1,1,1,0,0,0,0},
                            {1,1,1,1,0,0,0,0},
                            {1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1},
                            {1,1,1,1,0,0,0,0},
                            {1,1,1,1,0,0,0,0},
                            {1,1,1,1,0,0,0,0},
                            {1,1,1,1,0,0,0,0}};



    QuadTree qt(grid);
    cout<<"\nsize "<<qt.size;
    cout<<"\ndepht "<<qt.depth;
    qt.Print();


}

