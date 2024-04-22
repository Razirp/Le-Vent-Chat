#ifndef HINT_H
#define HINT_H

#include <QWidget>
#include<basewidget.h>
namespace Ui {
class Hint;
}

class Hint : public BaseWidget
{
    Q_OBJECT

public:
    explicit Hint(QWidget *parent = nullptr);
    ~Hint();

signals:
    void openClientChs();   //改

public slots:
    void settext(QString);

private slots:
    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_pushButton_clicked();

private:
     Ui::Hint *ui;
};

#endif // HINT_H
