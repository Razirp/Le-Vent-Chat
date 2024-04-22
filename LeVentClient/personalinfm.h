#ifndef PERSONALINFM_H
#define PERSONALINFM_H

#include <QWidget>
#include <basewidget.h>

namespace Ui {
class PersonalInfm;
}

class PersonalInfm : public BaseWidget
{
    Q_OBJECT

public:
    explicit PersonalInfm(QWidget *parent = nullptr);
    ~PersonalInfm();

private slots:
    void on_toolButton_4_clicked();

    void on_toolButton_3_clicked();

private:
    Ui::PersonalInfm *ui;
};

#endif // PERSONALINFM_H
