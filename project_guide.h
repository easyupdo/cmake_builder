#ifndef PROJECT_GUIDE_H
#define PROJECT_GUIDE_H

#include <QDialog>
#include <mainwindow.h>
#include <QMessageBox>
#include "project_config.h"


namespace Ui {
class Project_guide;
}




class Project_guide : public QDialog
{
    Q_OBJECT

public:
    explicit Project_guide(QWidget *parent = 0);
    ~Project_guide();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_3_clicked(bool checked);

    void on_checkBox_7_clicked(bool checked);

    void on_checkBox_6_clicked(bool checked);

    void on_checkBox_5_clicked(bool checked);

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);





private:
    Ui::Project_guide *ui;
    MainWindow *main;
    int root_choose;//1:root static choose  2:root shared choose  0:all no choose
    int sub_choose;////1:root static choose  2:root shared choose  0:all no choose

    struct SProjcetConfig project_config;
};

#endif // PROJECT_GUIDE_H
