#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include <QScrollArea>
#include<basewidget.h>
#include<tcpclient.h>
#include<database.h>

namespace Ui {
class ChatForm;
}

class ChatForm : public BaseWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = nullptr,QString="",QString="",QString="");
    ~ChatForm();
    QString fID,fname,mID;

protected:
    bool eventFilter(QObject *target, QEvent *event);//事件过滤器

signals:
    void chatFormClosed(QString fID);

private slots:

    void on_toolButton_4_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_clicked();

    void display(message);
private:
    Ui::ChatForm *ui;
    QVBoxLayout *VpLayout;
    database* db;
};

#endif // CHATFORM_H
