#include "set.h"
#include "ui_set.h"


Set::Set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Set)
{
    ui->setupUi(this);
}

Set::~Set()
{
    delete ui;
}



void Set::on_pushButton_4_clicked()
{
    //QString lib_dir = QFileDialog::getExistingDirectory();
    QString file_name = QFileDialog::getOpenFileName();
    libs_list.append(file_name);
    ui->textEdit_2->append(file_name);

}

void Set::on_pushButton_clicked()
{
    emit this->ToMainWindows(libs_list);
    this->close();
}

void Set::FromMainWinidows(QStringList libs)
{
    this->libs_list = libs;

    for(QStringList::iterator it = this->libs_list.begin();it != this->libs_list.end();it ++)
        ui->textEdit_2->append(*it);

}
