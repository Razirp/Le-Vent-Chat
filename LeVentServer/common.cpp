#include "common.h"

Server* Common::_server = nullptr;
DataBase* Common::_database = nullptr;

Common::Common()
{

}

Server* Common::getServerInstance()
{
    if(_server == nullptr)
    {
        _server = new Server;
    }
    return _server;
}

DataBase* Common::getDataBaseInstance()
{
    if(_database == nullptr)
    {
        _database = new DataBase;
    }
    return _database;
}
