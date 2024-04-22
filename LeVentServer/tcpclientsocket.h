#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H
#include <QTcpSocket>

class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpClientSocket(QObject * parent = nullptr);
    void setUserName(QString userName);     //设置用户名
    QString getUserName();  //获取用户名
    void sendMessage(QString msg);  //发送信息

signals:
    void dealMessage(QString msg);      //处理完信息的信号  //用于在服务器UI上显示
public slots:
    void receiveMessage();
    void dealDisconnect();      //disconnect处理
private:
    quint16 _blockSize;  //数据块大小
    QString _userName;
};

#endif // TCPCLIENTSOCKET_H
