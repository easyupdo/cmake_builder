#include "project_guide.h"
#include "ui_project_guide.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

Project_guide::Project_guide(QWidget *parent) :
    QDialog(parent),
    root_choose(false),
    sub_choose(false),
    ui(new Ui::Project_guide)
{
    ui->setupUi(this);
    ui->checkBox_6->setEnabled(false);//static
    ui->checkBox_5->setEnabled(false);//shared

    ui->checkBox_2->setEnabled(false);//static
    ui->checkBox->setEnabled(false);//shared


}

Project_guide::~Project_guide()
{
    delete ui;
}

void Project_guide::on_pushButton_clicked()
{

    if(ui->checkBox_7->checkState() == Qt::Checked)//root exec
    {
        project_config.project_type = ERootProjectType::EXEC;
        project_config.root_lib_type = ERootLibType::ROOT_LIB_NONE;
        if(ui->checkBox->checkState() == Qt::Checked )//sub lib
        {
            project_config.sub_lib_type = ESubLibType::SUB_LIB_SHARED;
            main = new MainWindow;
            this->close();
            main->setProjectConfig(project_config);
            main->show();
            main->move ((QApplication::desktop()->width() - main->width())/2,(QApplication::desktop()->height() - main->height())/2);
        }
        else if(ui->checkBox_2->checkState() == Qt::Checked)
        {
            project_config.sub_lib_type = ESubLibType::SUB_LIB_STATIC;
            main = new MainWindow;
            main->setProjectConfig(project_config);
            this->close();
            main->show();
            main->move ((QApplication::desktop()->width() - main->width())/2,(QApplication::desktop()->height() - main->height())/2);
        }
        else
        {
            QMessageBox box;
            box.setText("Please choose sub directory build type!");
            box.exec();
        }
    }
    else//root lib
    {
        project_config.project_type = ERootProjectType::LIB;
        QMessageBox box;
        if(root_choose && !sub_choose)
        {
            box.setText("Please choose sub directory build type!");
            box.exec();
        }

        if(sub_choose && !root_choose)
        {
            box.setText("Please choose root directory build type!");
            box.exec();
        }

        if(!sub_choose && !root_choose)
        {
            box.setText("Please choose root directory and sub directory build type!");
            box.exec();
        }

        if(sub_choose && root_choose)
        {
            if(root_choose == 1)
                project_config.root_lib_type = ERootLibType::ROOT_LIB_STATIC;
            else if(root_choose == 2)
                project_config.root_lib_type = ERootLibType::ROOT_LIB_SHARED;

            if(sub_choose == 1)
                project_config.sub_lib_type = ESubLibType::SUB_LIB_STATIC;
            else if(sub_choose == 2)
                project_config.sub_lib_type = ESubLibType::SUB_LIB_SHARED;

            main = new MainWindow;
            main->setProjectConfig(project_config);
            this->close();
            main->show();
            main->move ((QApplication::desktop()->width() - main->width())/2,(QApplication::desktop()->height() - main->height())/2);
        }
    }



}

//root lib
void Project_guide::on_checkBox_3_clicked(bool checked)
{
    if(checked)
    {
        ui->checkBox_7->setEnabled(false);//exec project
        ui->checkBox_6->setEnabled(true);//static
        ui->checkBox_5->setEnabled(true);//shared

        ui->checkBox_2->setEnabled(true);//static
        ui->checkBox->setEnabled(true);//shared

    }
    else
    {
        ui->checkBox_7->setEnabled(true);//exec project
        ui->checkBox_2->setEnabled(false);//static
        ui->checkBox->setEnabled(false);//shared
    }

}

//root exec
void Project_guide::on_checkBox_7_clicked(bool checked)
{
    if(checked)
    {
        ui->checkBox_3->setEnabled(false);//lib project
        ui->checkBox_6->setEnabled(false);//static
        ui->checkBox_5->setEnabled(false);//shared

        ui->checkBox_2->setEnabled(true);//static
        ui->checkBox->setEnabled(true);//shared
    }
    else
    {
        ui->checkBox_3->setEnabled(true);//lib project
        ui->checkBox_2->setEnabled(false);//static
        ui->checkBox->setEnabled(false);//shared
    }
}

void Project_guide::on_checkBox_6_clicked(bool checked)
{
    if(checked)
    {
        root_choose = 1;
        ui->checkBox_5->setEnabled(false);//Dynamic library
    }
    else
    {
        root_choose = 0;
        ui->checkBox_5->setEnabled(true);//Dynamic library
    }
}

void Project_guide::on_checkBox_5_clicked(bool checked)
{
    if(checked)
    {
        root_choose = 2;
        ui->checkBox_6->setEnabled(false);//static library
    }
    else
    {
        root_choose = 0;
        ui->checkBox_6->setEnabled(true);//Dynamic library
    }
}

void Project_guide::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        sub_choose = 2;
        ui->checkBox_2->setEnabled(false);//static library
    }
    else
    {
        sub_choose = 0;
        ui->checkBox_2->setEnabled(true);//Dynamic library
    }

}

void Project_guide::on_checkBox_2_clicked(bool checked)
{
    if(checked)
    {
        sub_choose = 1;
        ui->checkBox->setEnabled(false);//static library
    }
    else
    {
        sub_choose = 0;
        ui->checkBox->setEnabled(true);//Dynamic library
    }
}
