#include "testform.h"
#include "ui_testform.h"
#include <QHBoxLayout> //水平布局类
#include <QFile> //用文件类读取样式表文件qss
#include <QCheckBox>
#include <QDebug>
#include <QButtonGroup>

TestForm::TestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);

    //自定义控件一般在构造函数中实现大部分功能，可能包括一些布局设置
    //做一组开关按钮
    //开关核心类是基于QCheckBox
    QHBoxLayout *pLayout = new QHBoxLayout;
    //一组按钮放在布局中实现水平排列
    m_PButtonGroup =  new QButtonGroup(this);

    for (int i = 0; i < 3; ++i) {
        //设置文本显示
        QCheckBox *pCheckBox = new QCheckBox(this);
        pCheckBox->setText(QString::fromLocal8Bit("切换%1").arg(i+1));
        pLayout->addWidget(pCheckBox);

        QFile qss("://1.qss");
        qss.open(QIODevice::ReadOnly);
        pCheckBox->setStyleSheet(qss.readAll());
        qss.close();
    }

    pLayout->setSpacing(10);
    pLayout->setContentsMargins(10,10,10,10);
    this->setLayout(pLayout);

    //信号与槽函数的关联
    connect(m_PButtonGroup,
            SIGNAL(buttonClicked(QAbstractButton*)),
            this,
            SLOT(onButtonClicked(QAbstractButton* button)));
}

void TestForm::onButtonClicked(QAbstractButton* button)
{
    //当开关点击时，做初步提示
    qDebug() << QString("有个傻逼点了按钮%1一下").arg(button->text());
}

TestForm::~TestForm()
{
    delete ui;
}
