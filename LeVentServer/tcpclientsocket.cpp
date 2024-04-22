#include "tcpclientsocket.h"
#include "common.h"
#include "codesolver.h"
#include <QHostAddress>
#include <QDataStream>

TcpClientSocket::TcpClientSocket(QObject* parent):QTcpSocket (parent),_blockSize(0), _userName("")
{
    //有可读消息后，需要用receiveMessage()处理
    connect(this, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    connect(this, SIGNAL(disconnected()),this,SLOT(dealDisconnect()));
}

void TcpClientSocket::sendMessage(QString msg)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);  //只写
    out.setVersion(QDataStream::Qt_5_12);

    //预存2字节，消息存储结束后，设置实际的消息大小
    out << (quint16)0 << msg;
    //存储消息的大小到预留位置
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof (quint16));
    //发送信息
    write(block);
}

void TcpClientSocket::receiveMessage()
{
    QDataStream in(this);
    if(_blockSize == 0);
    {
        if(bytesAvailable() < (int)sizeof (quint16))
        {   //还未接收完毕比特流大小信息，退出等待下次信息一起获取
            return;
        }
        else
        {   //已接受完毕比特流大小信息，则获得比特流大小信息
            in >> _blockSize;
        }
    }
    //取得剩余消息的大小，若不满足[消息size]的要求，则退出等待下次信息一起读取
    int initBytes = bytesAvailable();
    if(initBytes < _blockSize)
    {
        return;
    }
    //完整接收信息后：
    QString msg;
    in >> msg;      //读取信息
    qDebug() << msg;
    //进行解析()    //to be coded.
    qDebug() << msg[0].toLatin1();
    Server* server = Common::getServerInstance();
    switch (msg[0].toLatin1()) {
    case 'A':
    {
        UserInfo registerInfo = CodeSolver::A_decode_register(msg);
        server->A_solve_register(this, registerInfo);
        break;
    }
    case 'B':
    {
        UserInfo loginUserInfo = CodeSolver::B_decode_login(msg);
        server->B_solve_login(this, loginUserInfo);
        break;
    }
    case 'C':
    {
        QString targetUserName = CodeSolver::C_decode_addFriend(msg);
        server->C_solve_addFriend(this, targetUserName);
        break;
    }
    case 'D':
    {
        ONPassword onPwd = CodeSolver::D_decode_modifyPwd(msg);
        server->D_solve_modifyPwd(this, onPwd);
        break;
    }
    case 'E':
    {
        Message msgToSend = CodeSolver::E_decode_getClientMsg(msg, this->_userName);
        server->E_solve_getClientMsg(this, msgToSend);
        break;
    }
    case 'F':
    {
        int sendStatus = CodeSolver::F_decode_sendMsgToTarget(msg);
        server->F_solve_sendMsgToTarget(this, sendStatus);
        break;
    }
    case 'G':
    {
        server->G_solve_userOffline(this);
        break;
    }
    default:
        break;
    }

    emit dealMessage(msg);  //用于在服务器UI上显示，在正式版中可去除。
    //初始化[信息size]，判断是否还要信息需要接收
    _blockSize = 0;
    if(bytesAvailable() > 0)
    {
        this->receiveMessage();
    }

}

void TcpClientSocket::dealDisconnect()
{
    Server* server = Common::getServerInstance();
    if(_userName != "")
    {   //如果在线则下线
        server->clientOffline(_userName);
    }
    server->removeClient(this);     //从连接列表中删除
    this->deleteLater();
}

void TcpClientSocket::setUserName(QString userName)
{
    this->_userName = userName;
}

QString TcpClientSocket::getUserName()
{
    return this->_userName;
}
