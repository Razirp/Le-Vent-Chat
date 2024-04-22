#include "alterpw.h"
#include "ui_alterpw.h"
#include<common.h>
AlterPw::AlterPw(QWidget *parent) :
   BaseWidget(parent),
    ui(new Ui::AlterPw)
{
    ui->setupUi(this);
    tcpclient * socket = common::getClientInstance();
    connect(socket,SIGNAL(dealmsg_d(message)),this,SLOT(display(message)));
    ui->toolButton->setShortcut(Qt::Key_Return);
    setAttribute(Qt::WA_DeleteOnClose);
}

AlterPw::~AlterPw()
{
    delete ui;
}

void AlterPw::on_toolButton_3_clicked()
{
    this->showMinimized();
}

void AlterPw::on_toolButton_4_clicked()
{
    this->close();
}

void AlterPw::on_toolButton_clicked()
{
    QString jpw=ui->lineEdit->text();
    QString xpw=ui->lineEdit_2->text();
    QString qxpw=ui->lineEdit_3->text();
    if(xpw!=qxpw){
        Hint *hint = new Hint;
        hint->show();
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("新密码不一致");
    }
    else if(jpw == xpw)
    {
        Hint *hint = new Hint;
        hint->show();
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("新旧密码相同");
    }
    else{
        tcpclient * socket = common::getClientInstance();
        socket->sendmsg(socket->msgslip_d(jpw,xpw));
    }
}

void AlterPw::display(message msg){
    if(msg.flag_d==0){
        Hint *hint = new Hint;
        hint->show();
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("修改成功");
        this->close();
    }
    else{
        Hint *hint = new Hint;
        hint->show();
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("原密码错误");
    }
}
