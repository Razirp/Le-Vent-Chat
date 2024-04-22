#include "hint.h"
#include "ui_hint.h"

Hint::Hint(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::Hint)
{
    ui->setupUi(this);
    ui->pushButton->setShortcut(Qt::Key_Return);
    setAttribute(Qt::WA_DeleteOnClose);
}

Hint::~Hint()
{
    delete ui;
}

void Hint::settext(QString tex){
    ui->label->setText(tex);
}

void Hint::on_toolButton_3_clicked()
{
    this->showMinimized();
}

void Hint::on_toolButton_4_clicked()
{
    if(ui->label->text() == "未连接端口")
    {
        emit openClientChs();
    }
    this->close();
}

void Hint::on_pushButton_clicked()
{
    this->on_toolButton_4_clicked();
}
