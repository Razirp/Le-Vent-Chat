#include "tcpclient.h"
#include<QArrayData>
#include<QHostAddress>
#include<QDataStream>
#include<QChar>
#include<QDebug>
#include <QFileDialog>
#include<QMessageBox>
#include"hint.h"

tcpclient::tcpclient(QObject *parent) : QTcpSocket(parent),blocksize(0)
{

    connect(this,SIGNAL(readyRead()),this,SLOT(recievemsg()));
    connect(this,SIGNAL(connected()),this,SLOT(isconnected()));
    connect(this,&QTcpSocket::disconnected,this,[=](){
        Hint *hint = new Hint;
        hint = new Hint;
        hint->show();
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("端口已断开");
    });
    qDebug() << "tcpclient debug";


}
//连接服务器
void tcpclient::connecttoserver(QString ip,QString port)
{
    qDebug() << "connectToServer";
    setserverip(ip);
    setserverport(port);
    this->connectToHost(QHostAddress(server_ip) ,server_port);
}

//检验是否处于连接状态
void tcpclient::isconnected()
{
     qDebug()<< "connected to server"+ QString::number(server_port);

     //QMessageBox::information(NULL,"提示信息","已成功连接至"+server_ip+":"+QString::number( server_port));
}

void tcpclient::setserverip(QString ip)
{
    server_ip=ip;
}
void tcpclient::setserverport(QString port)
{
    server_port=port.toUShort();
}

//获取消息结构体
message tcpclient::getmessage()
{
    return this->mes;
}

void tcpclient::updatemessage(message mess)
{
    mes = mess;
}
//消息拼接
//注册
QString tcpclient::msgslip_a(QString id, QString name,QString pwd)
{
    QString amsg("A#");
    amsg+="/a"+id+"/b"+name+"/c"+pwd;
    return amsg;
}
//登录
QString tcpclient::msgslip_b(QString id,  QString pwd)
{
    QString bmsg("B#");
    bmsg+="/a"+id+"/b"+pwd;
    return bmsg;
}
//添加好友
QString tcpclient::msgslip_c(QString recver)
{
    QString cmsg("C#/a");
    cmsg+=recver;
    return  cmsg;
}
//修改密码
QString tcpclient::msgslip_d(QString oldpwd, QString newpwd)
{
    QString dmsg("D#");
    dmsg+="/a"+oldpwd+"/b"+newpwd;
    return dmsg;
}
//聊天
QString tcpclient::msgslip_e(QString recver, QString qtime,QString text)
{
    QString emsg("E#");
    emsg+="/a"+recver+"/b"+qtime+"/c"+text;
    return emsg;
}
//注销用户
QString tcpclient::msgslip_g(QString id)
{
    QString gmsg("G#");
    gmsg +=id;
    return gmsg;
}
//发送信息
void tcpclient::sendmsg(QString msg)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    out << (qint16)0;
    out << msg;
    //存储大小
    out.device()->seek(0);
    out << (qint16)(block.size() - sizeof(qint16));


    write(block);

    int temp=(qint16)(block.size() - sizeof(qint16));
    qDebug()<<"send a message" << temp;
}

//接受信息
void tcpclient::recievemsg()
{
    QDataStream in(this);
    qDebug()<<"message from server";

    //取得[消息size]
    if (blocksize == 0)
    {
        if (bytesAvailable() < (int)sizeof(quint16))
        {
            return ;
        }

        in >> blocksize;

    }

    //取得剩余消息的大小，若不满足 [消息size] 的要求，则退出等待下次信息一起读取

    int initBytes = bytesAvailable();
    if (initBytes < blocksize)
    {

        return ;
    }


    //解析
    QString msg;
    in >> msg;

    qDebug()<<msg;

    char kkey = msg.at(0).unicode();
    int key=kkey-65;
    mes.key=key;
    switch (key) {

    case 0:
        //A#0
       {mes.flag_a=(int)msg.at(2).unicode()-48;
        emit dealmsg_a(mes);
        qDebug() << "dealmsg_a";
        break;}
    case 1:
        //B#0
       {mes.flag_b=(int)msg.at(2).unicode()-48;
        if(mes.flag_b == 0)
        {
            int index1 = msg.indexOf("/a");
            int index2 = msg.indexOf("/b");
            int index3 = msg.indexOf("$");
            QString id = msg.mid(index1+2,index2-index1-2);
            QString name = msg.mid(index2+2,index3-index2-2);
            qDebug()<<index1<<"   "<<index2<<"  "<<index3;
            mes.client_b.id=id;
            mes.client_b.name=name;
            while(index3!=msg.length()-1)
            {
                index1 = msg.indexOf("/a",index3);
                index2 = msg.indexOf("/b",index3);
                index3 = msg.indexOf("$",index3+1);
                qDebug()<<index1<<"   "<<index2<<"  "<<index3;
                QString id = msg.mid(index1+2,index2-index1-2);
                QString name = msg.mid(index2+2,index3-index2-2);
                person frd{id,name};
                mes.b_frind.push_back(frd);
            }
        }
        emit dealmsg_b(mes);
        break;}
    case 2:
        //C#0
        mes.flag_c=(int)msg.at(2).unicode()-48;
        if(mes.flag_c==0)
        {
            int index1 = msg.indexOf("/a");
            int index2 = msg.indexOf("/b");
            QString id = msg.mid(index1+2,index2-index1-2);
            mes.newfrd_c.id=id;
            mes.newfrd_c.name=msg.mid(index2+2,msg.length()-index2-2);
        }
        emit dealmsg_c(mes);
        break;
    case 3:
        //D#0
        mes.flag_d=(int)msg.at(2).unicode()-48;
        emit dealmsg_d(mes);
        break;
    case 4:
        //e发送消息到server
        mes.flag_e=(int)msg.at(2).unicode()-48;
        emit dealmsg_e(mes);
        break;
    case 5:
       {int index1=msg.indexOf("/a");
        int index2=msg.indexOf("/b");
        int index3=msg.indexOf("/c");
        //"F#/a..../b...../c......"
        QString sender = msg.mid(index1+2,index2-index1-2);
        mes.sender_f = sender;
        mes.time_f = msg.mid(index2+2,index3-index2-2);
        mes.text_f = msg.mid(index3+2,msg.length()-index3-2);
        emit dealmsg_f(mes);
        break;}
    case 6:
        //G#0
        mes.flag_g=(int)msg.at(2).unicode()-48;
        emit dealmsg_g(mes);
        break;
    case 7:
        //H#/a../b..
        {
         int index1 = msg.indexOf("/a");
         int index2 = msg.indexOf("/b");
         QString id = msg.mid(index1+2,index2-index1-2);
         mes.newfrd_h.id=id;
         mes.newfrd_h.name=msg.mid(index2+2,msg.length()-index2-2);
         emit dealmsg_h(mes);
         break;
        }
    default:
        break;
    }

    //读取完毕后，通知
    emit dealmsg(mes);

    //有可能一次发送多个信息，所有初始化 [信息size]，判断是否还有信息需要发送

    blocksize = 0;
    if (bytesAvailable()>0)
    {
        this->recievemsg();
    }
}

void tcpclient::clearMessage()
{
    mes.key = 0;
    mes.flag_a = 0;
    mes.flag_b = 0;
    mes.flag_c = 0;
    mes.flag_d = 0;
    mes.flag_e = 0;
    mes.flag_g = 0;
    mes.text_f = "";
    mes.time_f = "";
    mes.b_frind.clear();
    mes.client_b.id = "";
    mes.client_b.name = "";
    mes.newfrd_c.id = "";
    mes.newfrd_c.name = "";
    mes.newfrd_h.id = "";
    mes.newfrd_h.name = "";
    mes.sender_f = "";
}

