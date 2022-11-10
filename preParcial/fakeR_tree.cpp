//
// Created by misash on 13/10/22.
//


#include <iostream>
#include <bits/stdc++.h>

using namespace std;

//datos globales
const int N=2;
const int M =5;
const int m = M/2;

struct Node;

struct Intervals{
    int a , b;
};

struct Rectangle{
    vector<Intervals> box; //[(1,2)(3,5)]
    bool overlaps(Rectangle _box);
    int get_enlargement(Rectangle b);
    int get_area();
    void adjust(Rectangle b);
    void reset(){
        for (Intervals& interval : box) {
            interval.a = LONG_MAX;
            interval.b = LONG_MIN;
        }
    }
    }
};

struct SpatialObject {
    Rectangle box;
    string id;
    Node* child;
    void copy(SpatialObject entry);
};

struct Node{

    vector<SpatialObject> entries;
    int size=0;
    bool is_leaf();

    Node* insert(SpatialObject entry){
         entries[size++] = entry;
        return nullptr;
    }

};


struct RTree{

    Node* root;

    void search(Node* _root,Rectangle S,vector<Node*> &posible_Nodes){
        if(!_root->is_leaf()){
            for ( SpatialObject entry : _root->entries) {
                if(entry.box.overlaps(S)){
                    search(entry.child,S,posible_Nodes);
                }
            }
        }else{
            for (SpatialObject entry : _root->entries) {
                if(entry.box.overlaps(S)){
                    //añade los nodos cualificados
                   posible_Nodes.push_back(_root);
                }
            }
        }
    }

    void Insertion(SpatialObject E){
        //find position for neww record
        Node* leafNode = ChooseLeaf(root,E);
        //add record to leaf node
        if(leafNode->size <= M){
            leafNode->insert(E);
        }else{
            //overflow node
            leafNode->insert(E);
            QuadraticSplitNode(leafNode);
        }


    }

    Node* ChooseLeaf(Node* N,SpatialObject E){
        if(N->is_leaf()) return N;

        //calculate enlargement
        int min_area = N->entries[0].box.get_area();
        Rectangle F = N->entries[0].box;
        int min_enlargement = F.get_area() - min_area;
        Node * node= N->entries[0].child;
        int enlargement, area;

        for ( SpatialObject entry : N->entries) {
            area = entry.box.get_area();

            F = entry.box;
            enlargement = F.get_area() - area;

            if (enlargement < min_enlargement ||
                (enlargement == min_enlargement && area < min_area)) {
                min_enlargement = enlargement;
                min_area = area;
                node = entry.child;
                E.copy(entry);
            }
        }

        ChooseLeaf(node,E);
    }


    tuple<SpatialObject*,SpatialObject*> QuadraticSplitNode(Node *_root)
    {
        //retorna las dos etries que gastan mayor area

        tuple<SpatialObject*,SpatialObject*> nodes = pickSeed(_root );


        //añade la lista de entries restantes
        deque<SpatialObject> Entrieslist;
        for (SpatialObject entry : _root->entries) {
            if(entry.id != get<0>(nodes)->id && entry.id != get<1>(nodes)->id){
                Entrieslist.push_back(entry);
            }
        }

        //establecemos dos nuevos spactial objects para el root
        _root->entries.clear();
        _root->entries.push_back(*get<0>(nodes));
        _root->entries.push_back(*get<1>(nodes));

        //creamos dos nuevos nodos y agregamos los entries
        Node *node1 ,*node2;
        node1 = get<0>(nodes)->child ;
        node2 = get<1>(nodes)->child;


        //Distribuir entries
        //verificar su todos las entradas han sido asignadas
        while (!Entrieslist.empty()){
//            If all entnes have
//            been assigned, stop
//
//            If one group has
//            so few entries that all the rest must
//            be assigned to it m order for it to
//            have the muumum number m, assign
//            them and stop

            SpatialObject *e = PickNext(_root ,Entrieslist);

            //calculate enlargement
            int min_area1 = node1->entries[0].box.get_area();
            Rectangle F = node1->entries[0].box;
            int min_enlargement = F.get_area() - min_area1;
            Node * node= node1->entries[0].child;
            int enlargement, area;


            for(SpatialObject entry : node1->entries){
                area = entry.box.get_area();
                F = entry.box;
                enlargement = F.get_area() - area;
                if (enlargement < min_enlargement ||
                    (enlargement == min_enlargement && area < min_area1)) {
                    min_enlargement = enlargement;
                    min_area1 = area;
                    node = entry.child;
                }
            }

            //calculate enlargement
            int min_area2 = node1->entries[0].box.get_area();
            Rectangle F2 = node1->entries[0].box;
            int min_enlargement2 = F.get_area() - min_area2;
            Node * node2= node1->entries[0].child;
            int enlargement2, area2;

            for(SpatialObject entry : node1->entries){
                area = entry.box.get_area();
                F = entry.box;
                enlargement = F.get_area() - area;
                if (enlargement < min_enlargement ||
                    (enlargement == min_enlargement && area < min_area1)) {
                    min_enlargement = enlargement;
                    min_area1 = area;
                    node = entry.child;
                }
            }

            //adding entry with smaller enlargement and area
            if(min(min_enlargement,min_enlargement2) == min_enlargement){
                node1->entries.push_back(*e);

            }else{
                node2->entries.push_back(*e);
            }


        }

    }

    SpatialObject* PickNext(Node* _root,deque<SpatialObject> EntriesList){
        //determine cost of puttins each entry in each group
        int max = 0;
        SpatialObject* nextEntry;
        auto it = EntriesList.begin();
        for ( SpatialObject entry : EntriesList) {
            //calculate d,=
            //the area mcrease requu-ed m the
            //covermg rectangle of Group 1 to
            //include EI Calculate d2 slrmlarly
            //for Group 2
            int d1 = _root->entries[0].box.get_enlargement(entry.box);
            int d2 = _root->entries[1].box.get_enlargement(entry.box);
            if(abs(d1-d2) > max){
                  nextEntry = &entry;
                  it++;
            }
        }
        //choose entry with the maximum diference
        EntriesList.erase(it);
        return nextEntry;

    }



    tuple<SpatialObject*,SpatialObject*> pickSeed(Node * _root){
        int max_area = 0;
        int r,a;
        SpatialObject *s,*t;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < M+1; ++j) {
                //compose a rectangle including s and t rectangles
                Rectangle* r = RectangleIncluding(&_root->entries[i].box,&_root->entries[j].box);
                //calculate inefficency of group entries togeteher
                int current_area = r->get_area() - _root->entries[i].box.get_area() - _root->entries[j].box.get_area();
                if(current_area > max_area){
                    max_area = current_area;
                    s = &_root->entries[i];
                    t = &_root->entries[j];
                }
            }
        }
        return {s,t};
    }


    Rectangle* RectangleIncluding(Rectangle* a,Rectangle* b){
        Rectangle r;

        for (Intervals inter : a->box) {
            r.box.push_back(inter);
        }

        for (Intervals inter : b->box) {
            r.box.push_back(inter);
        }

        return &r;
    }


    Node* adjust_tree(Node * parent, Node* left , Node * right , SpatialObject* entry){


        entry->box.reset();

        for (SpatialObject current_entry : left->entries) {
            entry->box.adjust(current_entry.box);
        }
        if (!right) {
            return nullptr;
        }
        SpatialObject new_entry;
        new_entry.box.reset();
        for (SpatialObject &current_entry : right->entries ) {
            new_entry.box.adjust(current_entry.box);
        }
        new_entry.child = right;
        return parent->insert(new_entry);

    }


    void Delete(SpatialObject E){

        //find node sontainig record
        vector<SpatialObject>::iterator it;
        Node* leaf = FindLeaf(root,E,it);

        if(!leaf){
            cout<<"\n El registro , no existe";
            return;
        }

        //remove E from leaf
        leaf->entries.erase(it);

        //propagate changes
        condenseTree()

    }


    Node* FindLeaf(Node* _root,SpatialObject E,vector<SpatialObject>::iterator &it){
        //search subtrees
        if(!root) return nullptr;

        //Search leaf node for record
        if(_root->is_leaf()){
            vector<SpatialObject>::iterator iter = _root->entries.begin();
            for (SpatialObject entry : _root->entries) {
                //match
                if(entry.id == E.id && entry.child == E.child){
                    it = iter;
                    return _root;
                }
            }
        }

        if(!_root->is_leaf()){
            //check each entry f in root to determine F overlpas  Ei
            for (SpatialObject entry : _root->entries) {
                if(E.box.overlaps(entry.box)){
                    if(FindLeaf(entry.child, E,it))
                        return entry.child;
                }
            }
        }
        return nullptr;
    }

    Node* parentNode(Node * _root){

    }

    vector<SpatialObject>::iterator Entry_correspond(Node* _root){

    }

    bool findNode(Node* _root){

    }

    void condenseTree(Node* leaf){

        Node* N = leaf;
        vector<Node*> orphans;
        while ( N != root){
            Node* Parent = parentNode(N);
            auto parentEntry_ptr = Entry_correspond(N);
            //eliminate under-full node
            if(N->entries.size() < m){
                Parent->entries.erase(parentEntry_ptr);
                orphans.push_back(N);
            }

            //adjust covering rectangle
//            If N has
//            not been elunmated, adJust EN I to
//            tightly contam all entnes m N
            if(findNode(N)){
                for (SpatialObject entry : N->entries) {
                    entry.box.adjust();
                }
            }
            //move up to one level
            N = Parent;
        }

        //reinsert orphaned entries
        for (Node* n : orphans) {
            for (SpatialObject entry : n->entries) {
                Insertion(entry);
            }
        }

    }


};