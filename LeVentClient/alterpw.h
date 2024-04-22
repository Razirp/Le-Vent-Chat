#ifndef ALTERPW_H
#define ALTERPW_H

#include <QWidget>
#include<basewidget.h>
#include<hint.h>
#include<tcpclient.h>
#include<common.h>
namespace Ui {
class AlterPw;
}

class AlterPw : public BaseWidget
{
    Q_OBJECT

public:
    explicit AlterPw(QWidget *parent = nullptr);
    ~AlterPw();

signals:
    void sendhint(QString);
private slots:
    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_clicked();
     void display(message);

private:
    Ui::AlterPw *ui;
    //Hint *hint; //
};

#endif // ALTERPW_H
