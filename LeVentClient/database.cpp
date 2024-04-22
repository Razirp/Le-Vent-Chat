#include "database.h"
#include<common.h>
#include<mainwindow.h>
database::database(QObject *parent) : QObject(parent)
{
    sql = QSqlDatabase::addDatabase("QSQLITE");

    sql.setDatabaseName("mydb");
    sql.setUserName("root");
    sql.setPassword("123321");
    if(sql.open()){
        qDebug() << "mydb open";
    }

    QSqlQuery query(sql);
    query.exec("create table record(id text,target_id text,flag int,time text,content text)");

    tcpclient * socket = common::getClientInstance();
    connect(socket,SIGNAL(dealmsg_f(message)),this,SLOT(insert(message)));
}



void database::Insert_record(QString id, QString target_id, int flag, QString time, QString content)
{
    QSqlQuery query;
    query.prepare("insert into record(id,target_id,flag,time,content) values (:id,:target_id,:flag,:time,:content)");
    query.bindValue(":id",id);
    query.bindValue(":target_id",target_id);
    query.bindValue(":flag",flag);
    query.bindValue(":time",time);
    query.bindValue(":content",content);
    query.exec();
}

QStringList database::Select_record(QString id, QString friend_id)
{
    QStringList qlist;
    QString str;
    QSqlQuery query;
    query.prepare("select * from record where id = :id and target_id = :target_id");
    query.bindValue(":id",id);
    query.bindValue(":target_id",friend_id);
    query.exec();
    while(query.next()){
        str = query.value("flag").toString()+"/a"+query.value("time").toString()+"/b"+query.value("content").toString();
        qDebug() << str;
        qlist.append(str);
    }
    return qlist;
}

void database::insert(message msg){
    database *db=common::getdbInstace();
    db->Insert_record(msg.client_b.id,msg.sender_f,0,msg.time_f,msg.text_f);
    emit remind(msg.sender_f);
}
