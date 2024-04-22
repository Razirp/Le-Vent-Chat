#ifndef COMMON_H
#define COMMON_H
#include"tcpclient.h"
#include"database.h"

class common
{
public:
    common();
    static tcpclient* getClientInstance();
    static database* getdbInstace();

private:
    static tcpclient* client;
    static database* db;
};


#endif // COMMON_H
