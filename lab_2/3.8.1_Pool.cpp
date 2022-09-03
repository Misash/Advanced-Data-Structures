//
// Created by Misash on 2/09/2022.
//


struct POOL
{
    long (*lpfnOpen)(char *pszDBName);
    void (*lpfnInsertNewRecord)(long DBID);
    void (*lpfnDeleteRecord)(long DBID);
    void (*lpfnMoveNext)(long DBID);
    void (*lpfnMovePrev)(long DBID);
    void (*lpfnClose)(long DBID);
// More operations go here
};


long ABC_Open(char *pszDBName) {  }
long ABC_InserNewRegistry(long DBID ) { }
long ABC_DeleteRegistry(long DBID) { }
long ABC_MoveNext(long DBID) { }
long ABC_MovePrev(long DBID) { }
long ABC_Close(long DBID) { }




int main(){

    POOL ABCPool = {&ABC_Open, reinterpret_cast<void (*)(long)>(&ABC_InserNewRegistry),
                    reinterpret_cast<void (*)(long)>(&ABC_DeleteRegistry),
                    reinterpret_cast<void (*)(long)>(&ABC_MoveNext),
                    reinterpret_cast<void (*)(long)>(&ABC_MovePrev),
                    reinterpret_cast<void (*)(long)>(&ABC_Close)};


}







