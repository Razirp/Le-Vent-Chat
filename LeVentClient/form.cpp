#include "form.h"
#include "ui_form.h"
#include<QDebug>
#include<QMessageBox>
#include <hint.h>
#include"common.h"

Form::Form(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    tcpclient * socket = common::getClientInstance();
    connect(socket,SIGNAL(dealmsg_a(message)),this,SLOT(display(message)));
    ui->toolButton->setShortcut(Qt::Key_Return);
    setAttribute(Qt::WA_DeleteOnClose);
}

Form::~Form()
{
    delete ui;
}


void Form::on_toolButton_4_clicked()
{
    this->close();
}

void Form::on_toolButton_3_clicked()
{
    this->showMinimized();
}

void Form::on_toolButton_clicked()
{
    QString id=ui->lineEdit->text();
    QString pw=ui->lineEdit_2->text();
    QString repw=ui->lineEdit_3->text();
    QString name=ui->lineEdit_4->text();

    if(id == "" || pw == "" || name == "")
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
    else if(pw.contains('/'))
    {
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("密码不允许包含'/'");
        hint->show();
        return;
    }
    else if(name.contains('/'))
    {
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("昵称不允许包含'/'");
        hint->show();
        return;
    }
    else if(pw!=repw)
    {
        Hint *hint = new Hint;
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        hint->show();
        emit sendhint("密码不一致");     //
    }
    else {
        tcpclient * socket = common::getClientInstance();
        socket->sendmsg(socket->msgslip_a(id,name,pw));
    }


}

void Form::display(message mes){

    if(!mes.flag_a){
        Hint *hint = new Hint;
        hint->show();
        connect(this,SIGNAL(sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("注册成功");
        qDebug() << "注册成功";
        this->close();
    }
    else{
        Hint *hint = new Hint;
        hint->show();
        connect(this,SIGNAL( sendhint(QString)),hint,SLOT(settext(QString)));
        emit sendhint("注册失败");
    }
}

void Form::on_lineEdit_editingFinished()
{

}
