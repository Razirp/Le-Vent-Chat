#include "server.h"
#include "common.h"
#include "codesolver.h"
#include <QTcpServer>
#include <QMessageBox>
#include <QDebug>

Server::Server(QObject *parent) : QObject(parent), _tcpServer(new TcpServer)
{
}

void Server::start(int port)
{
    if(false == _tcpServer->listen(QHostAddress::Any, port))    //开始监听，如果失败则进入if语句
    {   //错误弹窗
        QMessageBox::warning(nullptr, "Error report", "Start-listen error!");
        qDebug() << _tcpServer->errorString();
    }
}

void Server::stop()
{
    _clients.clear();
    _tcpServer->close();
}

void Server::addClient(TcpClientSocket *c)
{
    _clients.append(c);
}

QList<TcpClientSocket*> Server::getClients()
{
    return _clients;
}

void Server::removeClient(TcpClientSocket *c)
{
    _clients.removeOne(c);
}

void Server::clientOnline(QString userName, TcpClientSocket *c)
{
    if(_onlineClients.contains(userName))
    {   //如果已存在于在线列表中，则将其顶替
        TcpClientSocket* temp = _onlineClients[userName];
        temp->setUserName("");  //先将其视为下线
        temp->abort();  //立即断开其连接
        _onlineClients[userName] = c;   //用新连接顶替
    }
    else
    {
        _onlineClients.insert(userName, c);
    }
}

void Server::clientOffline(QString userName)
{
    _onlineClients.remove(userName);
}

void Server::load_MessageToSend(QString target, Message msg)
{
    if(_msgToSend.contains(target))
    {   //如果存在已载入的信息，则继续载入
        _msgToSend[target].append(msg);
    }
    else
    {   //否则新加一个key
        QList<Message> tempList;
        tempList.append(msg);
        _msgToSend.insert(target, tempList);
    }
}

void Server::send_MessageToSend(QString target)
{
    if(!_msgToSend.contains(target))
    {   //如果没有需投递的消息则return
        return;
    }
    //取得target对应在线socket
    TcpClientSocket* c = _onlineClients[target];
    QString msg;    //向客户端发送的消息的编码
    foreach(Message message, _msgToSend[target])
    {   //对每个消息都进行编码发送
        msg = CodeSolver::F_encode_sendMsgToTarget(message);
        c->sendMessage(msg);
    }
    _msgToSend.remove(target);  //从未发消息记录中清除
}

void Server::A_solve_register(TcpClientSocket* c, UserInfo registerUser)
{
    DataBase* database = Common::getDataBaseInstance();
    QString msg;    //待发送信息
    if(database->User_Check(registerUser.userName))
    {   //用户名重复，返回1
        msg = CodeSolver::A_encode_register(1);
    }
    else
    {   //用户名不重复，注册成功，返回0
        database->User_Insert(registerUser);    //插入
        msg = CodeSolver::A_encode_register(0);
    }
    c->sendMessage(msg);    //发送A#回信
}

void Server::B_solve_login(TcpClientSocket *c, UserInfo loginUser)
{
    DataBase* database = Common::getDataBaseInstance();
    QString msg;    //
    if(!database->User_Check(loginUser.userName))
    {   //如果用户名不存在
        msg = CodeSolver::B_encode_login(1);
        c->sendMessage(msg);    //发送B#回信
    }
    else
    {   //用户名存在，查询对应的密码
        QString selectedPwd = database->User_Query_Password(loginUser.userName);
        if(loginUser.password != selectedPwd)
        {   //密码不正确
            msg = CodeSolver::B_encode_login(2);
            c->sendMessage(msg);    //发送B#回信
        }
        else
        {   //密码正确，返回个人信息与好友信息，并将对应socket加入在线列表
            //向数据库查询
            qDebug() << "0";
            UserInfo userInfo = database->User_Query_Information(loginUser.userName);
            qDebug() << "1";
            QList<UserInfo> friendsInfo = database->User_Query_Friend(loginUser.userName);
            qDebug() << "2";
            msg = CodeSolver::B_encode_login(0, userInfo, friendsInfo); //编码
            qDebug() << "3";
            c->setUserName(loginUser.userName);     //设置socket用户名
            qDebug() << "4";
            clientOnline(loginUser.userName, c);    //将其加入在线列表
            qDebug() << "5";
            c->sendMessage(msg);    //发送B#回信
            //投递该用户离线阶段未收消息
            qDebug() << "7";
            send_MessageToSend(loginUser.userName);
            qDebug() << "8";
        }
    }
}

void Server::C_solve_addFriend(TcpClientSocket *c, QString friendUserName)
{
    DataBase* database = Common::getDataBaseInstance();
    QString msg;    //
    if(database->User_Check(friendUserName))
    {   //如果目标用户存在且不重复，返回其信息，更新服务器好友列表，若目标用户在线，则更新其客户端信息
        UserInfo newFriendInfo = database->User_Query_Information(friendUserName);
        //更新好友列表，记录是否是重复好友
        bool repeatFriend = !database->Friend_Insert(c->getUserName(), friendUserName);
        if(repeatFriend)
        {   //如果是重复好友，返回C#2
            msg = CodeSolver::C_encode_addFriend(2);
            c->sendMessage(msg);
        }
        else
        {   //否则插入成功，返回C#0和新好友信息
            msg = CodeSolver::C_encode_addFriend(0, newFriendInfo);
            c->sendMessage(msg);
            if(_onlineClients.contains(friendUserName))
            {   //如果目标用户在线，向其客户端发送新好友信息
                UserInfo friendAdderInfo = database->User_Query_Information(c->getUserName());
                QString friendUpdateMsg = CodeSolver::H_encode_newFriendIn(friendAdderInfo);
                _onlineClients[friendUserName]->sendMessage(friendUpdateMsg);
            }
        }
    }
    else
    {   //不存在，返回C#1
        msg = CodeSolver::C_encode_addFriend(1);
        c->sendMessage(msg);
    }
}

void Server::D_solve_modifyPwd(TcpClientSocket *c, ONPassword old_new_password)
{
    DataBase* database = Common::getDataBaseInstance();
    QString msg;
    if(database->User_Query_Password(c->getUserName()) == old_new_password.oldPassword)
    {   //原密码输入正确，允许修改密码，回复D#0
        database->ChangePassword(c->getUserName(), old_new_password.newPassword);
        msg = CodeSolver::D_encode_modifyPwd(0);
        c->sendMessage(msg);
    }
    else
    {   //原密码输入不正确，不允许修改密码，回复D#1
        msg = CodeSolver::D_encode_modifyPwd(1);
        c->sendMessage(msg);
    }
}

void Server::E_solve_getClientMsg(TcpClientSocket *c, Message message)
{   //收到客户端发来的发送消息请求
    QString msg;
    message.senderUserName = c->getUserName();  //补充发送者信息
    if(_onlineClients.contains(message.targetUserName))
    {   //如果目标在线，回复E#0，并向目标编码并投递信息
        msg = CodeSolver::E_encode_getClientMsg(0);
        c->sendMessage(msg);    //向发送者回复消息
        //向目标编码并投递信息
        QString msgToTarget = CodeSolver::F_encode_sendMsgToTarget(message);
        qDebug() << "msgToTarget = " << msgToTarget;
        _onlineClients[message.targetUserName]->sendMessage(msgToTarget);
    }
    else
    {   //目标不在线，回复E#1，将信息载入待发送列表
        msg = CodeSolver::E_encode_getClientMsg(1);
        c->sendMessage(msg);
        load_MessageToSend(message.targetUserName, message);
    }
}

void Server::F_solve_sendMsgToTarget(TcpClientSocket *c, int status)
{
    //do nothing :)
}

void Server::G_solve_userOffline(TcpClientSocket *c)
{   //注销c的用户在线状态，但不断开c的连接
    QString msg;
    _onlineClients.remove(c->getUserName());   //将其从在线列表中删除
    c->setUserName("");     //将c的用户名置为空
    msg = CodeSolver::G_encode_userOffline(0);
    c->sendMessage(msg);    //返回G#0表示成功
}


