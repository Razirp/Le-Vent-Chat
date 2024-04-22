#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QMouseEvent>
#include <form.h>
#include <basewidget.h>
#include <mainwindow.h>
#include<QToolButton>
#include<clientchs.h>
#include<hint.h>
#include<tcpclient.h>
namespace Ui {
class Widget;
}

class Widget : public BaseWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

    ~Widget();
signals:
    void sendhint(QString);
    void sendtomain(message);

private slots:
    void on_toolButton_2_clicked();
    void on_toolButton_clicked();
    void on_toolButton_4_clicked();
    void on_toolButton_3_clicked();

    void on_toolButton_5_clicked();
    void display(message);

private:
    bool LoginPermit;
protected:


private:
    Ui::Widget *ui;
    Form *SignMene;
    MainWindow *mainwindow;
    ClientChs *clientchs;
    //Hint *hint; //
};

#endif // WIDGET_H
