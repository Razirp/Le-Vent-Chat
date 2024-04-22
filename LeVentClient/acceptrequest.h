#ifndef ACCEPTREQUEST_H
#define ACCEPTREQUEST_H

#include <QWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGridLayout>
#include<basewidget.h>
namespace Ui {
class AcceptRequest;
}

class AcceptRequest : public BaseWidget
{
    Q_OBJECT

public:
    explicit AcceptRequest(QWidget *parent = nullptr);
    ~AcceptRequest();

private slots:
    void accept(QPushButton *,QHBoxLayout*);
    void refuse(QPushButton *,QHBoxLayout*);

    void on_toolButton_4_clicked();

    void on_toolButton_3_clicked();

private:
    Ui::AcceptRequest *ui;
    QVBoxLayout *VpLayout;
};

#endif // ACCEPTREQUEST_H
