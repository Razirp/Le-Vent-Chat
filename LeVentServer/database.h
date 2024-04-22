#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "datastructure.h"

class DataBase
{
public:
    DataBase();
    bool User_Check(QString userName);//检查用户是否存在
    bool User_Insert(UserInfo userInfo);//插入用户信息
    QString User_Query_Password(QString userName);//查询用户密码
    UserInfo User_Query_Information(QString userName);//查询用户信息
    QList<UserInfo> User_Query_Friend(QString userName);//查询用户好友信息;
    bool ChangePassword(QString userName,QString password);//修改密码
    bool Friend_Insert(QString userName,QString friend_id);//插入好友   //检查是否两次    //如果已是好友，返回false
    bool Friend_Delete(QString userName,QString friend_id);//删除好友
private:
    QSqlDatabase sqldb;
    static DataBase* db;
};

#endif // DATABASE_H
