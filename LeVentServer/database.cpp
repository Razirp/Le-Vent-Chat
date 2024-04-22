#include "database.h"

DataBase* DataBase::db = nullptr;

DataBase::DataBase()
{
    sqldb = QSqlDatabase::addDatabase("QSQLITE");

    sqldb.setDatabaseName("mydb");
    sqldb.setUserName("root");
    sqldb.setPassword("123321");
    if(sqldb.open()){
        qDebug() << "sql open";
    }

    QSqlQuery query(sqldb);
    query.exec("create table user(id text,nickname text,pwd text)");
    query.exec("create table user_friends(id text,friend_id text)");
}

bool DataBase::User_Check(QString userName)
{
    QSqlQuery query;
    query.prepare("select * from user where id = :id");
    query.bindValue(":id",userName);
    query.exec();
    while(query.next()){
        return true;
    }
    return false;
}

bool DataBase::User_Insert(UserInfo userInfo)
{
    QSqlQuery query;
    query.prepare("insert into user(id, nickname, pwd) values (:id, :nickname, :pwd)");
    query.bindValue(":id",userInfo.userName);
    query.bindValue(":nickname",userInfo.nickname);
    query.bindValue(":pwd",userInfo.password);
    query.exec();
    return true;
}

QString DataBase::User_Query_Password(QString userName)
{
    QSqlQuery query;
    QString pwd;
    query.prepare("select pwd from user where id = :id");
    query.bindValue(":id",userName);
    query.exec();
    while(query.next()){
        pwd = query.value("pwd").toString();
    }
    return pwd;
}

UserInfo DataBase::User_Query_Information(QString userName)
{
    UserInfo user;
    user.userName = userName;
    QSqlQuery query;
    query.prepare("select * from user where id = :id");
    query.bindValue(":id",userName);
    query.exec();
    while(query.next()){
        user.nickname = query.value("nickname").toString();
        user.password = query.value("pwd").toString();
    }
    return user;
}

QList<UserInfo> DataBase::User_Query_Friend(QString userName)
{
    QList<UserInfo> qlist;
    QSqlQuery query;
    query.prepare("select * from user_friends where id = :id");
    query.bindValue(":id",userName);
    query.exec();
    while(query.next()){
        UserInfo user = User_Query_Information(query.value("friend_id").toString());
        qlist.append(user);
    }
    return qlist;
}

bool DataBase::ChangePassword(QString userName, QString password)
{
    QSqlQuery query;
    query.prepare("update user set pwd = :pwd where id = :id");
    query.bindValue(":pwd",password);
    query.bindValue(":id",userName);
    query.exec();
    return true;
}

bool DataBase::Friend_Insert(QString userName, QString friend_id)
{
    QSqlQuery query;
    query.prepare("select * from user_friends where id = :id and friend_id = :friend_id");
    query.bindValue(":id",userName);
    query.bindValue(":friend_id",friend_id);
    query.exec();
    while(query.next()){
        return false;   //如果已是好友，返回false
    }

    query.prepare("insert into user_friends(id,friend_id) values (:id,:friend_id)");
    query.bindValue(":id",userName);
    query.bindValue(":friend_id",friend_id);
    query.exec();
    query.prepare("insert into user_friends(id,friend_id) values (:id,:friend_id)");
    query.bindValue(":id",friend_id);
    query.bindValue(":friend_id",userName);
    query.exec();
    return true;
}

bool DataBase::Friend_Delete(QString userName, QString friend_id)
{
    QSqlQuery query;
    query.prepare("delete from user_friends where id = :id and friend_id = :friend_id");
    query.bindValue(":id",userName);
    query.bindValue(":friend_id",friend_id);
    query.exec();
    query.prepare("delete from user_friends where id = :id and friend_id = :friend_id");
    query.bindValue(":id",friend_id);
    query.bindValue(":friend_id",userName);
    query.exec();
    return true;
}
