#include "personalinfm.h"
#include "ui_personalinfm.h"

PersonalInfm::PersonalInfm(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::PersonalInfm)
{
    ui->setupUi(this);
}

PersonalInfm::~PersonalInfm()
{
    delete ui;
}

void PersonalInfm::on_toolButton_4_clicked()
{
    this->close();
}

void PersonalInfm::on_toolButton_3_clicked()
{
    this->showMinimized();
}
