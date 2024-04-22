#include "clientchs.h"
#include "ui_clientchs.h"
#include <hint.h>
#include "common.h"

bool ClientChs:: flag=false;
ClientChs::ClientChs(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::ClientChs)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->lineEdit->setText("82.156.190.217");
    ui->lineEdit_2->setText("9999");
    ui->toolButton->setShortcut(Qt::Key_Return);
}

ClientChs::~ClientChs()
{
    delete ui;
}
bool ClientChs::getflag(){
    return flag;
}

void ClientChs::on_toolButton_clicked()
{ //选择端口按钮槽函数
    tcpclient * socket = common::getClientInstance();

    QString IP = ui->lineEdit->text();
    QString Port = ui->lineEdit_2->text();

    socket->connecttoserver(IP,Port);
    if(flag==false){
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("端口连接失败");
        hint->show();
    }
    else
    {
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("端口已连接");
        hint->show();
    }

    connect(socket,&QTcpSocket::connected,this,[=](){
        flag = true;
        emit sendhint("端口连接成功");
        this->close();
    });



}

void ClientChs::on_toolButton_3_clicked()
{
    this->showMinimized();
}

void ClientChs::on_toolButton_4_clicked()
{
    this->close();
}
