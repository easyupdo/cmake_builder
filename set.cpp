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


//add libs
void Set::on_pushButton_4_clicked()
{
    //QString lib_dir = QFileDialog::getExistingDirectory();
    QStringList file_name_list = QFileDialog::getOpenFileNames();
    for(QStringList::iterator it = file_name_list.begin();it != file_name_list.end();it++)
    {
        libs_list.append(*it);
        ui->textEdit_2->append(*it);
    }


}

void Set::on_pushButton_clicked()
{
    emit this->ToMainWindows(this->libs_list,this->includes_list);
    this->close();
}

void Set::FromMainWinidows(QStringList libs,QStringList includes)
{
    this->libs_list = libs;
    this->includes_list = includes;

    //libs
    for(QStringList::iterator it = this->libs_list.begin();it != this->libs_list.end();it ++)
        ui->textEdit_2->append(*it);

    //includes
    for(QStringList::iterator it = this->includes_list.begin();it != this->includes_list.end();it ++)
        ui->textEdit_3->append(*it);

}

//add includes
void Set::on_pushButton_5_clicked()
{
    //QString lib_dir = QFileDialog::getExistingDirectory();
    QString include_name = QFileDialog::getExistingDirectory();

    includes_list.append(include_name);
    ui->textEdit_3->append(include_name);

}
