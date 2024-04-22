#include "chatform.h"
#include "ui_chatform.h"
#include<QTextEdit>
#include<QString>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include <QScrollArea>
#include<QPushButton>
#include<QToolButton>
#include<QDebug>
#include<QLabel>
#include<QScrollBar>
#include<time.h>
#include<windows.h>
#include<QThread>
#include<common.h>
#include<QTime>
#include<QDebug>

ChatForm::ChatForm(QWidget *parent,QString MID,QString FID,QString name) :
    BaseWidget(parent),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    tcpclient * socket = common::getClientInstance();
    connect(socket,SIGNAL(dealmsg_f(message)),this,SLOT(display(message)));

    db=common::getdbInstace();


    VpLayout = new QVBoxLayout();
    VpLayout->setSpacing(20);
    QStringList qlist;
    ui->toolButton_2->setText(name+"["+FID+"]");
    mID=MID;fID=FID;
    qlist = db->Select_record(mID,fID);
    int num = qlist.size();
    for(int i=0;i<num;i++){
        if(qlist.at(i).startsWith("1")){
            int x1 = qlist.at(i).indexOf("/a");
            int x2 = qlist.at(i).indexOf("/b");
            QString text_time = qlist.at(i).mid(x1+2,x2-x1-2);
            QString textstring = qlist.at(i).mid(x2+2,qlist.at(i).length()-x2-2);
            QHBoxLayout *HpLayout=new QHBoxLayout();

            QToolButton *pBtn = new QToolButton();
            pBtn->setStyleSheet("border-style:none;font: 12pt YouYuan;"
                                "border-image:url(:/Image/people (2).png);");
            pBtn->setMinimumSize(QSize(80,80));   //width height
            pBtn->setMaximumSize(QSize(80,80));   //width height



            QTextEdit *lab = new QTextEdit();
            lab->setReadOnly(true);
            lab->setText("["+text_time+"]\n"+textstring);   //这里是传输消息的函数
            lab->setStyleSheet("border-style:none;"
                               "font: 12pt YouYuan;"
                               "border-radius:15px;"
                               "border-image: url(:/Image/bubble.png);");
            lab->setMinimumSize(QSize(350,80));   //width height
            lab->setMaximumSize(QSize(350,80));   //width height
            lab->setAlignment(Qt::AlignRight);
            HpLayout->addWidget(lab);
            HpLayout->addWidget(pBtn);
            HpLayout->setAlignment(Qt::AlignRight);
            VpLayout->addLayout(HpLayout);
        } else {
            int x1 = qlist.at(i).indexOf("/a");
            int x2 = qlist.at(i).indexOf("/b");
            QString text_time = qlist.at(i).mid(x1+2,x2-x1-2);
            QString textstring = qlist.at(i).mid(x2+2,qlist.at(i).length()-x2-2);
            QHBoxLayout *HpLayout=new QHBoxLayout();

            QToolButton *pBtn = new QToolButton();
            pBtn->setStyleSheet("border-style:none;font: 12pt YouYuan;"
                                "border-image:url(:/Image/people (2).png);");
            pBtn->setMinimumSize(QSize(80,80));   //width height
            pBtn->setMaximumSize(QSize(80,80));   //width height



            QTextEdit *lab = new QTextEdit();
            lab->setReadOnly(true);
            lab->setText("["+text_time+"]\n"+textstring);   //这里是传输消息的函数
            lab->setStyleSheet("border-style:none;"
                               "font: 12pt YouYuan;"
                               "border-radius:15px;"
                               "border-image: url(:/Image/bubble.png);");
            lab->setMinimumSize(QSize(350,80));   //width height
            lab->setMaximumSize(QSize(350,80));   //width height
            lab->setAlignment(Qt::AlignLeft);
            HpLayout->addWidget(pBtn);
            HpLayout->addWidget(lab);
            HpLayout->setAlignment(Qt::AlignLeft);
            VpLayout->addLayout(HpLayout);

        }
    }

    ui->scrollArea->widget()->setLayout(VpLayout);//把布局放置到QScrollArea的内部QWidget中
    ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximumHeight());

    ui->textEdit->installEventFilter(this);//设置完后自动调用其eventFilter函数

}

ChatForm::~ChatForm()
{
    delete ui;
}



void ChatForm::on_toolButton_4_clicked()
{
    emit chatFormClosed(fID);
    this->close();
}

void ChatForm::on_toolButton_3_clicked()
{
    this->showMinimized();
}

bool ChatForm::eventFilter(QObject *target, QEvent *event)
{
    if(target == ui->textEdit)
    {
        if(event->type() == QEvent::KeyPress)//回车键
        {
             QKeyEvent *k = static_cast<QKeyEvent *>(event);
             if((k->key() == Qt::Key_Return) && (k->modifiers() == Qt::ControlModifier))
             {
                ui->textEdit->textCursor().insertBlock();
                return true;
             }
             else if(k->key() == Qt::Key_Return)
             {
                 on_toolButton_clicked();
                 return true;
             }
        }
    }
    return QWidget::eventFilter(target,event);
}

void ChatForm::on_toolButton_clicked()   //点击发送信息   传输到label中
{



    QString textstring =  ui->textEdit->toPlainText();   //这个是99行处的对应Qstring
    tcpclient * socket = common::getClientInstance();
    if(!ui->textEdit->document()->isEmpty()){
    socket->sendmsg(socket->msgslip_e(fID,QTime::currentTime().toString(),textstring));

    QHBoxLayout *HpLayout=new QHBoxLayout();

    QToolButton *pBtn = new QToolButton();
    pBtn->setStyleSheet("border-style:none;font: 12pt YouYuan;"
                        "border-image:url(:/Image/people (2).png);");
    pBtn->setMinimumSize(QSize(80,80));   //width height
    pBtn->setMaximumSize(QSize(80,80));   //width height



    QTextEdit *lab = new QTextEdit();
    lab->setReadOnly(true);
    lab->setText("["+QTime::currentTime().toString()+"]\n"+textstring);   //这里是传输消息的函数
    lab->setStyleSheet("border-style:none;"
                       "font: 12pt YouYuan;"
                       "border-radius:15px;"
                       "border-image: url(:/Image/bubble.png);");
    lab->setMinimumSize(QSize(350,80));   //width height
    lab->setMaximumSize(QSize(350,80));   //width height
    lab->setAlignment(Qt::AlignRight);
    HpLayout->addWidget(lab);
    HpLayout->addWidget(pBtn);
    HpLayout->setAlignment(Qt::AlignRight);
    VpLayout->addLayout(HpLayout);
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());

    db->Insert_record(mID,fID,1,QTime::currentTime().toString(),textstring); //存入数据库

    ui->textEdit->clear();
    }

}
void ChatForm::display(message msg)
{

    if(msg.sender_f!=fID)
    return;

    QHBoxLayout *HpLayout=new QHBoxLayout();

    QToolButton *pBtn = new QToolButton();
    pBtn->setStyleSheet("border-style:none;font: 12pt YouYuan;"
                        "border-image:url(:/Image/people (2).png);");
    pBtn->setMinimumSize(QSize(80,80));   //width height
    pBtn->setMaximumSize(QSize(80,80));   //width height

    HpLayout->addWidget(pBtn);


    QTextEdit *lab = new QTextEdit();
    lab->setReadOnly(true);
    lab->setText("["+msg.time_f+"]\n"+msg.text_f);//对方消息
    lab->setStyleSheet("border-style:none;"
                       "font: 12pt YouYuan;"
                       "border-radius:15px;"
                       "border-image: url(:/Image/bubble.png);");
    lab->setMinimumSize(QSize(350,80));   //width height
    lab->setMaximumSize(QSize(350,80));   //width height
    lab->setAlignment(Qt::AlignLeft);
    HpLayout->addWidget(lab);
    HpLayout->setAlignment(Qt::AlignLeft);

    VpLayout->addLayout(HpLayout);
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());
}
