#include "set.h"
#include "ui_set.h"


Set::Set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Set)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(true);
}

Set::~Set()
{
    delete ui;
}


void Set::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->checkBox_2->setChecked(false);
    }

}

void Set::on_pushButton_clicked()
{
    if(ui->checkBox->checkState() == Qt::Checked)
        if(ui->checkBox_3->checkState() ==Qt::Checked)
            this->ToMainWindows(ui->lineEdit->text() , EXEC_PROJ);
        else
            this->ToMainWindows(ui->lineEdit->text() , EXEC_PROJ);

    if(ui->checkBox_2->checkState() == Qt::Checked)
        if(ui->checkBox_3->checkState() ==Qt::Checked)
            this->ToMainWindows(ui->lineEdit->text() , EXEC_PROJ);
        else
            this->ToMainWindows(ui->lineEdit->text() , EXEC_PROJ);

    this->close();
}

void Set::on_checkBox_2_clicked(bool checked)
{
    if(checked)
        ui->checkBox->setChecked(false);
}


void Set::on_checkBox_3_clicked(bool checked)
{
    if(checked)
        ui->checkBox_4->setCheckable(false);
}

void Set::on_checkBox_4_clicked(bool checked)
{
    if(checked)
        ui->checkBox_3->setCheckable(false);
}
