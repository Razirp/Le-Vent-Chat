#include "findfriend.h"
#include "ui_findfriend.h"
#include"common.h"
FindFriend::FindFriend(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::FindFriend)
{
    ui->setupUi(this);
    tcpclient * socket = common::getClientInstance();
    connect(socket,SIGNAL(dealmsg_c(message)),this,SLOT(display(message)));
    ui->toolButton->setShortcut(Qt::Key_Return);
    setAttribute(Qt::WA_DeleteOnClose);
}

FindFriend::~FindFriend()
{
    delete ui;
}

void FindFriend::on_toolButton_clicked()  //搜索按钮槽函数
{
    QString ID = ui->lineEdit->text();
    QString name;
    if(ID=="")
    {
        ui->label_2->setText("请输入ID！");
        ui->label_2->setStyleSheet("background-color: rgb(250, 0, 0);font-size:15px;color:blue");
    }
    if(ID==mID){
        ui->label_2->setText("无法添加自己为好友！");
        ui->label_2->setStyleSheet("background-color: rgb(250, 0, 0);font-size:15px;color:blue");
    }
    else{
        tcpclient * socket = common::getClientInstance();
        socket->sendmsg(socket->msgslip_c(ID));
    }
}
void FindFriend::display(message msg)
{
    if(msg.flag_c == 0){
        ui->label_2->setText("添加成功！");
        QString ID = msg.newfrd_c.id;
        QString name = msg.newfrd_c.name;
        emit setperson(ID,name);
    }
    else if(msg.flag_c == 1){
        ui->label_2->setText("此ID不存在！");
        ui->label_2->setStyleSheet("background-color: rgb(250, 0, 0);font-size:15px;color:blue");
    }
    else if(msg.flag_c==2){
        ui->label_2->setText("该好友已添加！");
        ui->label_2->setStyleSheet("background-color: rgb(250, 0, 0);font-size:15px;color:blue");
    }
}
void FindFriend::on_toolButton_4_clicked()
{
    this->close();
}

void FindFriend::on_toolButton_3_clicked()
{
    this->showMinimized();
}
