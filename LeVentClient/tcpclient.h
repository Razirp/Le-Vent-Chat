#ifndef TCP_H
#define TCP_H

#include <QObject>
#include<QTcpSocket>
#include<QVector>
#include"hint.h"
#include<QFile>

struct person{
    QString id;
    QString name;
};
//server返回消息处理后的结构体，作ui槽函数参数

struct message{
    int key;
    int flag_a=0; //注册反馈
    person client_b;  //登录反馈个人信息
    QVector <person> b_frind; //登录反馈好友信息
    int flag_b=0; //登陆反馈
    int flag_c=0;  //添加好友反馈
    person newfrd_c;
    int flag_d=0;  //修改密码反馈
    int flag_e=0;  //消息发送反馈
    QString sender_f=" ";  //消息发送者
    QString time_f=" "; //消息发送时间
    QString text_f=" ";  //消息发送文本
    int flag_g=0;   //注销反馈
    person newfrd_h;  //被添加好友反馈
};


 class tcpclient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit tcpclient(QObject *parent = nullptr);

 public:
    void setserverip(QString ip);
    void setserverport(QString port);
    void connecttoserver(QString ip,QString port);
    struct message getmessage();
    void updatemessage(message);
    //消息拼接部分
    QString msgslip_a(QString id,QString name,QString pwd);//注册
    QString msgslip_b(QString id,QString pwd);//登录
    QString msgslip_c(QString recver);//添加好友
    QString msgslip_d(QString oldpwd,QString newpwd);//修改密码
    QString msgslip_e(QString recver,QString qtime,QString text);//聊天消息
    QString msgslip_f();
    QString msgslip_g(QString id);//注销账户
    //发送消息
    void sendmsg(QString msg);
    void clearMessage();

 signals:
     void sendhint(QString);
signals:
    //处理信息完成信号
    void dealmsg(struct message);

    void recemsg(struct message);

    void dealmsg_a(message);//注册反馈信号
    void dealmsg_b(message);//登陆反馈信号
    void dealmsg_c(message);//加好友接收信号
    void dealmsg_d(message); //修改密码反馈信号
    void dealmsg_e(message);//发送信息反馈
    void dealmsg_f(message);//接受信息反馈
    void dealmsg_g(message);//退出登录
    void dealmsg_h(message);//被添加好友

public slots:
    //接受信息
    void recievemsg();
    //判断是否连接
    void isconnected();



private:

    QString server_ip;
    unsigned short server_port;
    qint16 blocksize;
    struct message mes;
    //Hint *hint; //

    bool flag = false;



};

#endif // TCP_H
