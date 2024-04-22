#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void showClientMsg(QString msg);

private slots:
    void on_startPB_clicked();

    void on_closePB_clicked();

    void on_getCSPB_clicked();

    void on_sendPB_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
