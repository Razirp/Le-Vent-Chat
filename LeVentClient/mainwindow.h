#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QScrollArea>
#include<chatform.h>
#include<findfriend.h>
#include<QToolButton>
#include <basewidget.h>
#include<tcpclient.h>
#include<alterpw.h>
#include <QMap>
namespace Ui {
class MainWindow;
}

class MainWindow : public BaseWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QString getID();

signals:
    void mysignal();
    void setchat(QString,QString);
    void closeall();

public slots:
   void sendMysigal();
   void addnew(QString,QString);

private slots:
    void open(QString,QString);

    void removeChatFormPtr(QString fID);


    void on_toolButton_5_clicked();

    void remindMessage(QString senderID);

    void on_toolButton_4_clicked();

    void on_toolButton_3_clicked();
    void recemsg(message);
    void display(message);

    void on_toolButton_8_clicked();
    void silogin(QString);

    void on_toolButton_6_clicked();

    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;
    FindFriend *findfriend;
    QToolButton *pBtn;
    QVBoxLayout *VpLayout;
    AlterPw * alterpw;
    static QString ID;
    QMap<QString, ChatForm *> openedForms;
    QMap<QString, QString> _friend_fID_Name;
public:
    QScrollArea scrollArea;

};

#endif // MAINWINDOW_H
