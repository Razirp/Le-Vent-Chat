#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QObject>
#include <basewidget.h>
#include<hint.h>
#include<tcpclient.h>

namespace Ui {
class Form;
}

class Form : public BaseWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

signals:
    void sendhint(QString);

private slots:
    void on_lineEdit_editingFinished();

    void on_toolButton_4_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_clicked();
    void display(message);

protected:


private:
    Ui::Form *ui;
    //Hint *hint; //
};

#endif // FORM_H
