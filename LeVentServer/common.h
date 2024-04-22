#ifndef COMMON_H
#define COMMON_H
#include "server.h"
#include "database.h"

class Common
{
public:
    Common();
    static Server* getServerInstance();     //单例设计方法
    static DataBase* getDataBaseInstance();
private:
    static Server* _server;
    static DataBase* _database;
};

#endif // COMMON_H
