
#include "CSkipList.h"

template<class K>
void initialize(void *node,int size){
    memset(node, 0, sizeof(Node<K>*)*(size + 1));
}


template<class K>
Node<K>::Node(K key, int level)
{

    this->key = key;
    forward = new Node*[level+1];
    initialize<K>(forward,level);

};


template<class K>
SkipList<K>::SkipList(int maxLevel, float p)
{
    this->maxlevel = maxLevel;
    this->p = p;
    level = 0;

    // create header node and initialize key to -1
    header = new node(-1, maxLevel);
};

template<class K>
float SkipList<K>::random(){
    return  (float)rand()/RAND_MAX;
}

template<class K>
int SkipList<K>::randomLevel()
{
    int lvl = 0;
    while(random() < p )
    {
        lvl++;
    }
    return min(lvl,maxlevel);
};


template<class K>
Node<K>* SkipList<K>::createNode(K key, int level)
{
    node *n = new node(key,level);
    return n;
};


template<class K>
void SkipList<K>::insertElement(K key)
{
    node *current = header;


    node *update[maxlevel + 1];
    initialize<K>(update,maxlevel);


    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] != NULL && current->forward[i]->key < key)
            current = current->forward[i];

        update[i] = current;
    }


    current = current->forward[0];


    if (current == NULL || current->key != key)
    {
        int rlevel = randomLevel();

        if(rlevel > level)
        {
            for(int i=level+1;i<rlevel+1;i++)
                update[i] = header;

            level = rlevel;
        }

        node* n = createNode(key, rlevel);

        for(int i=0;i<=rlevel;i++)
        {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
//        cout<<"Inserted key "<<key<<"\n";
    }
};

template<class K>
void SkipList<K>::deleteElement(K key)
{
    node *current = header;


    node *update[maxlevel + 1];
    initialize<K>(update,maxlevel);


    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] != NULL && current->forward[i]->key < key)
            current = current->forward[i];

        update[i] = current;
    }

    current = current->forward[0];


    if(current != NULL and current->key == key)
    {

        for(int i=0;i<=level;i++)
        {

            if(update[i]->forward[i] != current)
                break;

            update[i]->forward[i] = current->forward[i];
        }

        while(level>0 &&
              header->forward[level] == 0)
            level--;
        cout<<"Deleted key "<<key<<"\n";
    }
};


template<class K>
Node<K>* SkipList<K>::searchElement(K key)
{
    node *current = header;


    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] &&
              current->forward[i]->key < key)
            current = current->forward[i];

    }

    current = current->forward[0];

    if(current && current->key == key){
        cout<<"Found key: "<<key<<" \n";
        return current;
    }

    cout<<"Not Found key: "<<key<<"\n";
    return 0;
};

template<class K>
void SkipList<K>::displayList()
{
    cout<<"\n ______S K I P _ L I S T______ "<<"\n\n";
    for(int i=0;i<=level;i++)
    {
        node *node = header->forward[i];
        cout<<"Level "<<i<<": ";
        while(node != NULL)
        {
            cout<<node->key<<" ";
            node = node->forward[i];
        }
        cout<<"\n";
    }
    cout<<"___________________________ "<<"\n\n";
};

