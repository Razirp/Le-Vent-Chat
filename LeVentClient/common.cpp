#include "common.h"
tcpclient* common:: client = nullptr;
database* common::db = nullptr;
common::common()
{

}

tcpclient* common::getClientInstance()
{
    if(client == nullptr)
        client = new tcpclient;
    return client;
}

database* common::getdbInstace()
{
    if(db == nullptr){
        db = new database;
    }
    return db;
}
