#ifndef FINDFRIEND_H
#define FINDFRIEND_H

#include <QWidget>
#include <basewidget.h>
#include<tcpclient.h>
namespace Ui {
class FindFriend;
}

class FindFriend : public BaseWidget
{
    Q_OBJECT

public:
    explicit FindFriend(QWidget *parent = nullptr);
    ~FindFriend();
    QString mID;
signals:
    void setperson(QString,QString);
private slots:
    void on_toolButton_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_3_clicked();
    void display(message);

private:
    Ui::FindFriend *ui;
    bool IsHave=false;

};

#endif // FINDFRIEND_H
