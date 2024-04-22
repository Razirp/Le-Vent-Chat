#ifndef CLIENTCHS_H
#define CLIENTCHS_H

#include <QWidget>
#include <hint.h>
#include<tcpclient.h>
#include<basewidget.h>
namespace Ui {
class ClientChs;
}

class ClientChs : public BaseWidget
{
    Q_OBJECT

public:
    explicit ClientChs(QWidget *parent = nullptr);
    ~ClientChs();
    static bool getflag();
signals:
    void sendhint(QString);
private slots:

    void on_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

private:
    Ui::ClientChs *ui;
    //Hint *hint; //
    static bool flag;
};

#endif // CLIENTCHS_H
