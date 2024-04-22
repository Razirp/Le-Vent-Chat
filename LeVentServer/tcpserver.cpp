#include "tcpserver.h"
#include "widget.h"
#include "tcpclientsocket.h"
#include "common.h"
#include <QDebug>
extern Widget* mw;

TcpServer::TcpServer(QObject* parent):QTcpServer (parent)
{
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    TcpClientSocket* tcpClientSocket = new TcpClientSocket(this);
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    Server* s = Common::getServerInstance();
    s->addClient(tcpClientSocket);

    connect(tcpClientSocket, SIGNAL(dealMessage(QString)),
            mw, SLOT(showClientMsg(QString)));

    //connect?
}
