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
