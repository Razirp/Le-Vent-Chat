#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
}

Setting::~Setting()
{
    delete ui;
}


void Setting::on_toolButton_4_clicked()
{
    this->close();
}

void Setting::on_toolButton_3_clicked()
{
    this->lower();
}
