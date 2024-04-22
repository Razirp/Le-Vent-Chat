#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QTcpServer>


class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject* parent = nullptr);

signals:

public slots:

protected:
    virtual void incomingConnection(qintptr socketDescriptor);  //重写incomingConnection()

};

#endif // TCPSERVER_H
