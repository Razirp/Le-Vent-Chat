#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include <QScrollArea>
#include<QListWidget>
#include<QToolButton>
#include <QMenu>
#include<setting.h>
#include"common.h"

QString MainWindow::ID = "";

MainWindow::MainWindow(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    database* db = common::getdbInstace();
    connect(ui->toolButton_8,&QToolButton::clicked,this,&MainWindow::sendMysigal);
    tcpclient * socket = common::getClientInstance();
    connect(socket,SIGNAL(dealmsg_h(message)),this,SLOT(display(message)));
    connect(socket,SIGNAL(sendhint(QString)),this,SLOT(silogin(QString)));
    connect(db, SIGNAL(remind(QString)), this, SLOT(remindMessage(QString)));

    ui->toolButton_5->setToolTip("添加好友");
    ui->toolButton_6->setToolTip("修改密码");
    ui->toolButton_8->setToolTip("退出登录");
    ui->toolButton_3->setToolTip("最小化");
    ui->toolButton_4->setToolTip("关闭");
    setAttribute(Qt::WA_DeleteOnClose);
}
void MainWindow::sendMysigal(){
    emit mysignal();
}
MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::removeChatFormPtr(QString fID)
{
    openedForms.remove(fID);
}

void MainWindow::remindMessage(QString senderID)
{
    QString senderName = _friend_fID_Name[senderID];
    this->open(senderName, senderID);
}

void MainWindow::open(QString name,QString fID){
    if(openedForms.contains(fID))
    {
        openedForms[fID]->hide();
        openedForms[fID]->show();
        openedForms[fID]->raise();
        return;
    }
    ChatForm* charform=new ChatForm(nullptr,ID,fID,name);
    charform->mID=ui->label_2->text();
    connect(this,SIGNAL(closeall()),charform,SLOT(on_toolButton_4_clicked()));
    connect(charform, SIGNAL(chatFormClosed(QString)), this, SLOT(removeChatFormPtr(QString)));
    charform->show();
    openedForms.insert(fID, charform);
}

void MainWindow::display(message msg)
{
    addnew(msg.newfrd_h.id,msg.newfrd_h.name);
    _friend_fID_Name.insert(msg.newfrd_h.id, msg.newfrd_h.name);
}

void MainWindow::on_toolButton_5_clicked()  //打开查找好友界面
{
    findfriend =new FindFriend;
    connect(findfriend,SIGNAL(setperson(QString,QString)),this,SLOT(addnew(QString,QString)));
    connect(this,SIGNAL(closeall()),findfriend,SLOT(on_toolButton_4_clicked()));
    findfriend->mID=ui->label_2->text();
    findfriend->show();
}



void MainWindow::addnew(QString fID,QString name){
    QHBoxLayout *HpLayout=new QHBoxLayout();
    pBtn = new QToolButton();
    pBtn->setStyleSheet("border-style:none;font: 14pt YouYuan;"
                        "border-image:url(:/Image/people (2).png);");
    pBtn->setMinimumSize(QSize(60,60));   //width height
    pBtn->setMaximumSize(QSize(60,60));   //width height
    HpLayout->addWidget(pBtn);


    pBtn = new QToolButton();
    pBtn->setText(name+"["+fID+"]");   //设置好友姓名
    pBtn->setStyleSheet("QToolButton{border-style:none;font: 14pt YouYuan;}"
                        "QToolButton:hover{background-color:rgb(201, 218, 255);}");
    pBtn->setMinimumSize(QSize(200,60));   //width heig
    pBtn->setMaximumSize(QSize(200,60));   //width heig
    HpLayout->addWidget(pBtn);
    HpLayout->setAlignment(Qt::AlignLeft);
    VpLayout->addLayout(HpLayout);//把按钮添加到布局控件中
    connect(pBtn,&QToolButton::clicked,this,[=](){open(name,fID);});
}
QString MainWindow::getID(){
    return ID;
}
void MainWindow::recemsg(message msg){
    QString name=msg.client_b.name;
    ID=msg.client_b.id;

    ui->label->setText(name);
    ui->label_2->setText(ID);

    int friendNum = msg.b_frind.size();
    for(int i = 0; i < friendNum; ++i)
    {
        QString tempID = msg.b_frind.at(i).id;
        QString tempName = msg.b_frind.at(i).name;
        _friend_fID_Name.insert(tempID,tempName);
    }


    VpLayout = new QVBoxLayout();  //生成好友列表

        for(int i = 0; i < msg.b_frind.size(); i++)
        {
            QHBoxLayout *HpLayout=new QHBoxLayout();

            pBtn = new QToolButton();
            pBtn->setStyleSheet("border-style:none;font: 14pt YouYuan;"
                                "border-image:url(:/Image/people (2).png);");
            pBtn->setMinimumSize(QSize(60,60));   //width height
            pBtn->setMaximumSize(QSize(60,60));   //width height
            HpLayout->addWidget(pBtn);

            pBtn = new QToolButton();
            QString fID=msg.b_frind.at(i).id;
            name=msg.b_frind.at(i).name;
            pBtn->setText(name+"["+fID+"]");   //设置好友姓名
            pBtn->setStyleSheet("QToolButton{border-style:none;font: 14pt YouYuan;}"
                                "QToolButton:hover{background-color:rgb(201, 218, 255);}");
            pBtn->setMinimumSize(QSize(200,60));   //width heig
            pBtn->setMaximumSize(QSize(200,60));   //width heig
            HpLayout->addWidget(pBtn);
            HpLayout->setAlignment(Qt::AlignLeft);
            VpLayout->addLayout(HpLayout);//把按钮添加到布局控件中
            connect(pBtn,&QToolButton::clicked,this,[=](){open(name,fID);});
        }
       ui->scrollArea->widget()->setLayout(VpLayout);//把布局放置到QScrollArea的内部QWidget中
}


void MainWindow::on_toolButton_4_clicked()
{
    this->close();
    QApplication::exit(0);
}

void MainWindow::on_toolButton_3_clicked()
{
   this->showMinimized();
}

void MainWindow::on_toolButton_8_clicked()
{
    tcpclient* socket = common::getClientInstance();
    socket->sendmsg(socket->msgslip_g(ID));
    socket->clearMessage();
    emit closeall();
    this->close();
}

void MainWindow::silogin(QString s){
    if(s=="端口已断开") on_toolButton_8_clicked();
}

void MainWindow::on_toolButton_6_clicked()
{
    alterpw =new AlterPw;
    connect(this,SIGNAL(closeall()),alterpw,SLOT(on_toolButton_4_clicked()));
    alterpw->show();
}

void MainWindow::on_toolButton_clicked()
{
    //do nothing.
}
