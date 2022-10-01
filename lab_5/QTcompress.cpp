
#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <type_traits>

using namespace std;

typedef struct bmpFileHeader
{
    /* 2 bytes de identificación */
    uint32_t size;        /* Tamaño del archivo */
    uint16_t resv1;       /* Reservado */
    uint16_t resv2;       /* Reservado */
    uint32_t offset;      /* Offset hasta hasta los datos de imagen */
} bmpFileHeader;

typedef struct bmpInfoHeader
{
    uint32_t headersize;      /* Tamaño de la cabecera */
    uint32_t width;       /* Ancho */
    uint32_t height;      /* Alto */
    uint16_t planes;          /* Planos de color (Siempre 1) */
    uint16_t bpp;             /* bits por pixel */
    uint32_t compress;        /* compresión */
    uint32_t imgsize;     /* tamaño de los datos de imagen */
    uint32_t bpmx;        /* Resolución X en bits por metro */
    uint32_t bpmy;        /* Resolución Y en bits por metro */
    uint32_t colors;      /* colors used en la paleta */
    uint32_t imxtcolors;      /* Colores importantes. 0 si son todos */
} bmpInfoHeader;

unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader)
{

    FILE *f;
    bmpFileHeader header;     /* cabecera */
    unsigned char *imgdata;   /* datos de imagen */
    uint16_t type;        /* 2 bytes identificativos */

    f=fopen (filename, "r");
    if (!f)
        return NULL;        /* Si no podemos leer, no hay imagen*/

    /* Leemos los dos primeros bytes */
    fread(&type, sizeof(uint16_t), 1, f);
    if (type !=0x4D42)        /* Comprobamos el formato */
    {
        fclose(f);
        return NULL;
    }

    /* Leemos la cabecera de fichero completa */
    fread(&header, sizeof(bmpFileHeader), 1, f);

    /* Leemos la cabecera de información completa */
    fread(bInfoHeader, sizeof(bmpInfoHeader), 1, f);

    /* Reservamos memoria para la imagen, ¿cuánta?
       Tanto como indique imgsize */
    imgdata=(unsigned char*)malloc(bInfoHeader->imgsize);

    /* Nos situamos en el sitio donde empiezan los datos de imagen,
     nos lo indica el offset de la cabecera de fichero*/
    fseek(f, header.offset, SEEK_SET);

    /* Leemos los datos de imagen, tantos bytes como imgsize */
    fread(imgdata, bInfoHeader->imgsize,1, f);


    /* Cerramos */
    fclose(f);

    /* Devolvemos la imagen */
    return imgdata;
}

void imgToMatrix(bmpInfoHeader *info,unsigned char *img,deque<deque<char>> &matrix){

    int x, y;
    static const int reduccionX=1, reduccionY=1;
    static const int umbral=90;
    static unsigned char colores[9]="obgfrRGB";
    int r,g,b;

    matrix = deque<deque<char> >(info->width, deque<char>(info->height));

    for (y=info->height; y>0; y-=reduccionY)
    {
        for (x=0; x<info->width; x+=reduccionX)
        {
            b=(img[3*(x+y*info->width)]>umbral);
            g=(img[3*(x+y*info->width)+1]>umbral);
            r=(img[3*(x+y*info->width)+2]>umbral);

            matrix[info->height-y][x] = colores[b+g*2+r*4];
        }
    }
}


struct Node{
    //childrens:
    // 0 1
    // 2 3
    Node* children[4];
    int x ,y,dim;
    Node(int x ,int y, int dim) : x(x) , y(y) ,dim(dim) {}

};

template<class T>
class QuadTree{
public:
    Node* root;
    deque<deque<T>> grid;
    int n, size , depth;

    QuadTree(deque<deque<T>> grid){
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
                sum += grid[i][j] ;
            }
        }
        return (grid[node->x][node->y]  * pow(node->dim,2) == sum );
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

//        cout<<"\n---------------------------------\n";
//
//        for (int i = node->x; i < node->x+node->dim ; ++i) {
//            for (int j = node->y; j < node->y + node->dim; ++j) {
//                cout<<grid[i][j]<<"";
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



    bmpInfoHeader info;
    unsigned char *img;

    img=LoadBMP("cat2.bmp", &info);
//    DisplayInfo(&info);
//    TextDisplay(&info, img);
    deque<deque<char>> matrix;
    imgToMatrix(&info,img,matrix);

//    for (int i = 0; i < matrix.size(); ++i) {
//        for (int j = 0; j < matrix[0].size(); ++j) {
//            cout<<matrix[i][j]<<"";
//        }
//        cout<<"\n";
//    }

//    deque<deque<char>> grid= {  {'v','v','v','v','0','0','0','0'},
//                                {'v','v','v','v','0','0','0','0'},
//                                {'v','v','v','v','v','v','v','v'},
//                                {'v','v','v','v','v','v','v','v'},
//                                {'v','v','v','v','0','0','0','0'},
//                                {'v','v','v','v','0','0','0','0'},
//                                {'v','v','v','v','0','0','0','0'},
//                                {'v','v','v','v','0','0','0','0'}};

    QuadTree<char> qt(matrix);
    qt.Print();


}

