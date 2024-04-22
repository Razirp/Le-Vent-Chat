#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QPainter>
#include<QButtonGroup>
//实现一组开关状态的开关

namespace Ui {
class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = nullptr);
    ~TestForm();


protected:
    //绘图时间——程序运行自动调用，执行一些外观绘制
    //void paintEvent(QPaintEvent event);

public slots:
    void onButtonClicked(QAbstractButton*); //按钮连接信号槽函数

private:
    Ui::TestForm *ui;
    QButtonGroup *m_PButtonGroup;




};

#endif // TESTFORM_H
