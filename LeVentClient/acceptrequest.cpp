#include "acceptrequest.h"
#include "ui_acceptrequest.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include <QScrollArea>
#include<QPushButton>
#include<QDebug>
AcceptRequest::AcceptRequest(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::AcceptRequest)
{
    ui->setupUi(this);
    VpLayout = new QVBoxLayout();
    QHBoxLayout *HpLayout;
        for(int i = 0; i < 10; i++)
        {
            QPushButton *pBtn1 = new QPushButton();
            pBtn1->setText(QString("按钮%1").arg(i));
            pBtn1->setMinimumSize(QSize(60,30));   //width height
            VpLayout->addWidget(pBtn1);//把按钮添加到布局控件中

            HpLayout=new QHBoxLayout();

            QPushButton *pBtn2 = new QPushButton();
            pBtn2->setText(QString("按钮%1").arg(i));
            pBtn2->setMinimumSize(QSize(30,30));   //width height
            HpLayout->addWidget(pBtn2);

            connect(pBtn2, &QPushButton::clicked,this,[=](){accept(pBtn1,HpLayout);});

            QPushButton *pBtn3 = new QPushButton();
            pBtn3->setText(QString("按钮%1").arg(i));
            pBtn3->setMinimumSize(QSize(30,30));   //width height
            HpLayout->addWidget(pBtn3);

            connect(pBtn3, &QPushButton::clicked,this,[=](){refuse(pBtn1,HpLayout);});

            VpLayout->addLayout(HpLayout);


        }
       ui->scrollArea->widget()->setLayout(VpLayout);//把布局放置到QScrollArea的内部QWidget中
}

AcceptRequest::~AcceptRequest()
{
    delete ui;
}

void AcceptRequest::accept(QPushButton* button,QHBoxLayout* HpLayout){
    if(button!=NULL){VpLayout->removeWidget(button);delete button;}
    if(HpLayout!=NULL){
        QLayoutItem *child;
           while ((child = HpLayout->takeAt(0)) != nullptr)
           {
               ///setParent为NULL，防止删除之后界面不消失
               if(child->widget())
               {
                   child->widget()->setParent(nullptr);
               }
               delete child;
           }
        VpLayout->removeItem(HpLayout);delete HpLayout;}

}

void AcceptRequest::refuse(QPushButton* button,QHBoxLayout* HpLayout){
    if(button!=NULL){VpLayout->removeWidget(button);delete button;}
    if(HpLayout!=NULL){
        QLayoutItem *child;
           while ((child = HpLayout->takeAt(0)) != nullptr)
           {
               ///setParent为NULL，防止删除之后界面不消失
               if(child->widget())
               {
                   child->widget()->setParent(nullptr);
               }
               delete child;
           }
        VpLayout->removeItem(HpLayout);delete HpLayout;}
}


void AcceptRequest::on_toolButton_4_clicked()
{
    this->close();
}

void AcceptRequest::on_toolButton_3_clicked()
{
    this->lower();
}
