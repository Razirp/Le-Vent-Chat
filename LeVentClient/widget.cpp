#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>
#include "form.h"
#include <QMessageBox>
#include<mainwindow.h>
#include<hint.h>
#include"common.h"

Widget::Widget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->toolButton->setShortcut(Qt::Key_Return);

    tcpclient * socket = common::getClientInstance();
    connect(socket,SIGNAL(dealmsg_b(message)),this,SLOT(display(message)));

}



Widget::~Widget()
{
    delete ui;
}

void Widget::on_toolButton_2_clicked()
{
    if(ClientChs::getflag()==false){
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        hint->show();
        emit sendhint("未连接端口");
        connect(hint, SIGNAL(openClientChs()), this, SLOT(on_toolButton_5_clicked()));
        return;
    }
    SignMene = new Form;
    SignMene->show();
}


void Widget::on_toolButton_clicked()//登录按钮槽函数
{
    if(ClientChs::getflag()==false){
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        hint->show();
        emit sendhint("未连接端口");
        connect(hint, SIGNAL(openClientChs()), this, SLOT(on_toolButton_5_clicked()));
        return;
    }
    QString id = ui->lineEdit_3->text();
    QString pwd = ui->lineEdit_2->text();
    if(id == "" || pwd == "")
    {
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("请完整填写信息");
        hint->show();
        return;
    }
    else if(id.contains('/'))    //改
    {
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("账户不允许包含'/'");
        hint->show();
        return;
    }
    else if(pwd.contains('/'))
    {
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("密码不允许包含'/'");
        hint->show();
        return;
    }
    tcpclient * socket = common::getClientInstance();
    socket->sendmsg(socket->msgslip_b(id,pwd));


}
void Widget:: display(message mes){
    if(mes.flag_b==1){
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        hint->show();
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("用户名不存在");
    }
    else if(mes.flag_b == 2){
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        hint->show();
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("密码有误");
    }else{
        mainwindow = new MainWindow;
        mainwindow->show();
        connect(mainwindow,&MainWindow::mysignal,this,&Widget::show);
        connect(this,SIGNAL(sendtomain(message)),mainwindow,SLOT(recemsg(message)));
        tcpclient* socket = common::getClientInstance();
        emit sendtomain(socket->getmessage());
        this->close();

    }
}

void Widget::on_toolButton_4_clicked()
{
    this->close();
    QApplication::exit(0);
}

void Widget::on_toolButton_3_clicked()
{
    this->showMinimized();
}

void Widget::on_toolButton_5_clicked()
{
    if(ClientChs::getflag() == true)
    {
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("端口已连接");
        hint->show();
        return;
    }
    clientchs = new ClientChs;
    clientchs->show();
}
