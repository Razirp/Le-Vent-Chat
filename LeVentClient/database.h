#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include<tcpclient.h>
#include <QObject>
class database : public QObject
{
    Q_OBJECT

public:
    explicit database(QObject *parent = nullptr);

    //插入聊天记录 flag表示是不是id用户发送的消息，1是，0否
    void Insert_record(QString id,QString target_id,int flag,QString time,QString content);
    //查询聊天记录
    QStringList Select_record(QString id,QString friend_id);

signals:
    void remind(QString senderUserName);

public slots:
    void insert(message);
private:
    QSqlDatabase sql;
    //static database* db;
};

#endif // DATABASE_H
