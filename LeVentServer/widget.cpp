#include "widget.h"
#include "ui_widget.h"
#include "server.h"
#include "common.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::showClientMsg(QString msg)
{
    ui->clientInfoLE->setText(msg);
}

void Widget::on_startPB_clicked()
{
    //实例化Server对象
    Server* server = Common::getServerInstance();
    int tcpPort = ui->portLE->text().toInt();   //得到端口号
    server->start(tcpPort);
    qDebug() << tcpPort;    //Debug
    //更改“启动”和“关闭”按钮的可用性
    ui->startPB->setEnabled(false);
    ui->closePB->setEnabled(true);
}

void Widget::on_closePB_clicked()
{
    //得到Server对象
    Server* server = Common::getServerInstance();
    server->stop();
    ui->startPB->setEnabled(true);
    ui->closePB->setEnabled(false);
}

void Widget::on_getCSPB_clicked()
{
    Server* server = Common::getServerInstance();
    int clientSocketNum = server->getClients().size();
    ui->clientSocketLE->setText(QString::number(clientSocketNum));
}

void Widget::on_sendPB_clicked()
{
    Server* s = Common::getServerInstance();
    QList<TcpClientSocket*> clients = s->getClients();
    int socketNum = ui->socketNumLE->text().toInt();
    QString msg = ui->sendLE->text();
    clients.at(socketNum)->sendMessage(msg);
}
