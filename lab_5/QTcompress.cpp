
#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "bitmap.cpp"


using namespace std;


struct Node{
    //childrens:
    // 0 1
    // 2 3
    Node* children[4] = {0,0,0,0};
    int x ,y,dim;
    Node(int x ,int y, int dim) : x(x) , y(y) ,dim(dim) {}

};

template<class T>
class QuadTree{
public:
    Node* root;
    vector<vector<T>> grid;
    int n, size , depth;
    int umbral;

    QuadTree(vector<vector<T>> grid){
        this->grid = grid;
        this->n = grid.size();
        root = new Node(0,0,n);
        size = depth = 0;
        buildTreePyramid(root);
    }

    QuadTree(string filename, int umbral){
        this->umbral = umbral;
        Bitmap image;
        image.open(filename + ".bmp");
        if(!image.isImage()) return;

        grid = image.pixels;
        this->n = grid.size();
        root = new Node(0,0,n);
        size = depth = 0;

        buildTreePyramid(root);
        drawLimits(root);
        image.fromPixelMatrix(grid);
        image.save(filename+"Output.bmp");
    }


    bool isLeaf(Node* node){

        const int height = node->dim;
        const int width = node->dim;

        float mean[3] = {0,0,0};
        for (int i = node->x; i < node->x+height; i++)
        {
            for (int j = node->y; j < node->y + width; j++)
            {
                mean[0] += grid[i][j].red;
                mean[1] += grid[i][j].green;
                mean[2] += grid[i][j].blue;
            }
        }

        mean[0]  /= (height * width);
        mean[1]  /= (height * width);
        mean[2]  /= (height * width);

        int standard_deviation[3]={0,0,0};
        for (int i = node->x; i < node->x + height; i++)
        {
            for (int j = node->y; j < node->y + width; j++)
            {
                standard_deviation[0] += pow(mean[0] - grid[i][j].red,2) ;
                standard_deviation[1] += pow(mean[1] - grid[i][j].green,2) ;
                standard_deviation[2] += pow(mean[2] - grid[i][j].blue,2) ;
            }
        }
        standard_deviation[0] /= (height * width);
        standard_deviation[1] /= (height * width);
        standard_deviation[2] /= (height * width);

        for(int k=0;k<3;k++) {
            standard_deviation[k] = sqrt(standard_deviation[k]);
//            std::cout<<standard_deviation[k]<<endl;
            if(standard_deviation[k] > umbral) {
                return 0;
            }
        }

        return 1;
    }

    void split(Node* node){
        if(node->dim <= 0) return;
        depth++;
        node->children[0] = new Node(node->x,node->y,node->dim/2);
        node->children[1] = new Node(node->x,node->y + node->dim/2  ,node->dim/2);
        node->children[2] = new Node(node->x + node->dim/2 ,node->y,node->dim/2);
        node->children[3] = new Node(node->x + node->dim/2 ,node->y + node->dim/2 ,node->dim/2);
    }

    void buildTreePyramid(Node* node){
        size ++;
        if(isLeaf(node)) return;

        split(node);

        if(node->children[0]){
            for (int i = 0; i < 4 ; ++i) {
                buildTreePyramid(node->children[i]);
            }
        }

    }

    void drawLimits(Node* data )
    {
        if ( !data ) return;
        drawLimits(data->children[0]);
        drawLimits(data->children[1]);
        for (int i = data->x; i < data->x+data->dim ; ++i) {
            grid[i][data->y] = Pixel(0,255,213);
            grid[i][data->y+data->dim -1] =Pixel(0,255,213);
        }
        for (int j = data->y; j < data->y + data->dim; ++j) {
            grid[data->x][j] = Pixel(0,255,213);
            grid[data->x + data->dim - 1][j] = Pixel(0,255,213);
        }
        drawLimits(data->children[2]);
        drawLimits(data->children[3]);
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
        int d =  n;
        for (int i = 0; i < height; ++i) {
            for (j = 0; j < size; ++j){
                Node *node = vec[i][j];
                if( node){
                    PrintNode(node);
                }
            }
            cout << "\n-------------------\n";
        }
    }

    void PrintNode(Node* node){
        cout<<"\n";
        for (int i = node->x; i < node->x+node->dim ; ++i) {
            for (int j = node->y; j < node->y + node->dim; ++j) {
                cout<<grid[i][j] <<"";
            }
            cout<<"\n";
        }
    }


};




int main(){

    QuadTree<Pixel> qt("input",0.1);


}

