#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include "tcpclientsocket.h"
#include "tcpserver.h"
#include "datastructure.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void start(int port);   //开始监听
    void stop();
    void addClient(TcpClientSocket* c);     //添加客户端socket
    QList<TcpClientSocket*> getClients();
    void removeClient(TcpClientSocket* c);  //去除已断开连接的客户端socket
    void clientOnline(QString userName, TcpClientSocket* c);
    void clientOffline(QString userName);

    //对接收到的A~G各类信息的处理
    void A_solve_register(TcpClientSocket* c, UserInfo registerUser);
    void B_solve_login(TcpClientSocket* c, UserInfo loginUser);
    void C_solve_addFriend(TcpClientSocket* c, QString friendUserName);
    void D_solve_modifyPwd(TcpClientSocket* c, ONPassword old_new_password);
    void E_solve_getClientMsg(TcpClientSocket* c, Message message);
    void F_solve_sendMsgToTarget(TcpClientSocket* c, int status);
    void G_solve_userOffline(TcpClientSocket* c);

private:
    void load_MessageToSend(QString target, Message msg);    //存储未发送消息
    void send_MessageToSend(QString target);     //发送未发送消息


signals:

public slots:

private:
    TcpServer* _tcpServer;
    QList<TcpClientSocket*> _clients;   //客户端连接
    QMap<QString, TcpClientSocket*> _onlineClients;     //在线用户列表
    QMap<QString, QList<Message>> _msgToSend;   //待发送消息列表
};

#endif // SERVER_H
