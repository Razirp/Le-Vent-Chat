#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <basewidget.h>

namespace Ui {
class Setting;
}

class Setting : public BaseWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private slots:
    void on_toolButton_4_clicked();

    void on_toolButton_3_clicked();

private:
    Ui::Setting *ui;
};

#endif // SETTING_H
