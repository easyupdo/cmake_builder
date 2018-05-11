 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmake_build.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    builded_flag(false),
    dir_model(NULL),
    root_item(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString source_dir = QFileDialog::getExistingDirectory();
    ui->lineEdit->setText(source_dir);
    SetTree(source_dir);
    AnalysisCurrentDirectoryFile(root_item,source_dir,0,NONE);
}

void MainWindow::SetTree(QString dir)
{
    qDebug()<<"What fuck!";

    dir_model = new QStandardItemModel;
    QStandardItem * head1 = new QStandardItem("Name");
   dir_model->setHorizontalHeaderItem(0,head1);

//    QStandardItem * head2 = new QStandardItem("Type");
//    dir_model->setHorizontalHeaderItem(1,head2);


    QString root_path = ui->lineEdit->text();
    int index  = root_path.lastIndexOf("/");
    QString root_dir = root_path.right(root_path.length()-index-1);

    root_item = new QStandardItem(root_dir);
    root_item->setEditable(false);
    root_item->setCheckable(true);
    dir_model->setItem(0,0,root_item);
    ui->treeView->setModel(dir_model);

}


void MainWindow::AnalysisCurrentDirectoryFile(QStandardItem *item ,QString root_dir,int dir_depth, enum BuildOrClean options_type)//Dir And File   NOUSED
{
    QList<QString>current_sub_direcotry_lists;
    qDebug()<<"Set root_Dir"<<root_dir;

    QString cmake_config_path;


    CleanCmakeListsFile(root_dir);//clean
     if(options_type == BUILD)
    {
        cmake_config_path = CreateCmakeListsFile(root_dir);
    }

    QFileInfoList file_full = QDir(root_dir).entryInfoList();
    QFileInfoList::iterator it = file_full.begin();
    int item_rows = 0;
    for(it;it!=file_full.end();it++)
    {
        if((*it).isDir())
        {
//            //qDebug()<<"This is DIR";
            if((*it).fileName().compare(".") && (*it).fileName().compare(".."))//ready sub direcotry not include . .. dir
            {
                dir_depth +=1;
                current_sub_direcotry_lists.append((*it).filePath());
                qDebug()<<"This is Dir"<<(*it).fileName()<<"Path"<<(*it).filePath();
                QStandardItem * item1 = new QStandardItem((*it).fileName());
                item1->setEditable(false);
                item1->setCheckable(true);
                item->setChild(item_rows,0,item1);
                item_rows +=1;
                AnalysisCurrentDirectoryFile(item1,(*it).filePath(),dir_depth,options_type);
            }
        }
        else
        {
            if(!(*it).suffix().compare("cpp") || !(*it).suffix().compare("c") || !(*it).suffix().compare("h") || !(*it).fileName().compare("CMakeLists.txt"))// file just .c .cpp
            {
                qDebug()<<(*it).fileName();
                QStandardItem * item1 = new QStandardItem((*it).fileName());
                item1->setEditable(false);
                item->setChild(item_rows,0,item1);
                item_rows +=1;
            }
        }
     }
    dir_depth -=1;//use for determine root dir;
    this->SetADirectoryCMakeListFile(root_dir,cmake_config_path,current_sub_direcotry_lists,dir_depth);// have subdirectory

}

//
void MainWindow::GetDirecotryUnderCurrentDirectory(QString root_dir)
{
    QFileInfoList file_full = QDir(root_dir).entryInfoList();
    QFileInfoList::iterator it = file_full.begin();
    for(it;it!=file_full.end();it++)
    {
        if((*it).isDir())
        {
            qDebug()<<(*it).filePath();
            if((*it).fileName().compare(".") && (*it).fileName().compare(".."))
            {
                qDebug()<<"Dir Name"<<(*it).fileName();
            }
        }
    }
}


QString MainWindow::CreateCmakeListsFile(QString current_dir)
{
    QString str;
    QString cmake_config_name = "/CMakeLists.txt";
    QString cmake_config_path = current_dir + cmake_config_name;
    QFile new_file(cmake_config_path);
    new_file.open(QIODevice::ReadWrite);
    if(new_file.isOpen())
    {
        qDebug()<<"CMakeLists.txt create successful!";
        new_file.close();
    }
    return cmake_config_path;
}

void MainWindow::CleanCmakeListsFile(QString current_dir)
{
    QString str;
    QString cmake_config_name = "/CMakeLists.txt";
    QString cmake_config_path = current_dir + cmake_config_name;
    QFile new_file(cmake_config_path);
    new_file.open(QIODevice::ReadWrite);
    if(new_file.exists())
        new_file.remove();
    new_file.close();
}

void MainWindow::SetADirectoryCMakeListFile(QString current_dir, QString cmakelists_file, QList<QString> sub_lists,int dir_depth, QString lib_type_string)// A directory
{
    QString str;
    qDebug()<<cmakelists_file;
    QFile cmake_config_file(cmakelists_file);

    cmake_config_file.open(QIODevice::ReadWrite);

    bool status = cmake_config_file.isOpen();

    if(cmake_config_file.isOpen())
    {
        QString source_dir_argv = "SRC_DIR" ;

        QString include_dir_argv = "INCLUDE_DIR";



        str = cmake_build::project(current_dir);
        cmake_config_file.write(str.toLatin1());
        cmake_config_file.write("\n");



        str = cmake_build::aux_source_directory(current_dir,source_dir_argv,CMAKE_STRING);
        qDebug()<<str;
        cmake_config_file.write(str.toLatin1());
        cmake_config_file.write("\n");

//set_include
        str.clear();
        QString include_argv = "INCLUDE_DIR";
        str = cmake_build::set(include_argv,source_dir_argv,CMAKE_ARGV);
        qDebug()<<str;
        cmake_config_file.write(str.toLatin1());
        cmake_config_file.write("\n");


        str.clear();
        str = cmake_build::include_directories(include_dir_argv,CMAKE_ARGV);
        qDebug()<<str;
        cmake_config_file.write(str.toLatin1());
        cmake_config_file.write("\n");






        qDebug()<<"DDDDDDDDDDDDDDDDDDDDDD"<<dir_depth;
        if(!dir_depth)// root dir first time
        {
            if(project_config.project_type == ERootProjectType::EXEC)
            {
                str.clear();
                QString exec_name = "main";
                str = cmake_build::add_executable(exec_name,source_dir_argv,CMAKE_ARGV);
                qDebug()<<str;
                cmake_config_file.write(str.toLatin1());
                cmake_config_file.write("\n");
            }
            if(project_config.project_type == ERootProjectType::LIB)
            {
                str.clear();
                if(project_config.root_lib_type == ERootLibType::ROOT_LIB_STATIC)
                    str =  cmake_build::add_library(current_dir,source_dir_argv,CMAKE_ARGV,STATIC);
                else
                    str =  cmake_build::add_library(current_dir,source_dir_argv,CMAKE_ARGV,SHARED);
                qDebug()<<str;
                cmake_config_file.write(str.toLatin1());
                cmake_config_file.write("\n");
            }

        }else
        {
            str.clear();
            qDebug()<<"KKKKK"<<project_config.sub_lib_type;
            if(project_config.sub_lib_type == ESubLibType::SUB_LIB_STATIC)
                str =  cmake_build::add_library(current_dir,source_dir_argv,CMAKE_ARGV,STATIC);
            else if(project_config.sub_lib_type == ESubLibType::SUB_LIB_SHARED)
                str =  cmake_build::add_library(current_dir,source_dir_argv,CMAKE_ARGV,SHARED);
            qDebug()<<str;
            cmake_config_file.write(str.toLatin1());
            cmake_config_file.write("\n");
        }


        str.clear();
        QString lib_name = "hello";



        for(int i =0;i<sub_lists.size();i++)
        {


            str.clear();
            QString lib_argv = "LIB_DIR";
            str = cmake_build::set(lib_argv,sub_lists.at(i),CMAKE_STRING);
            qDebug()<<str;
            cmake_config_file.write(str.toLatin1());
            cmake_config_file.write("\n");

            str.clear();
            str = cmake_build::link_directories(lib_argv,CMAKE_ARGV);
            qDebug()<<str;
            cmake_config_file.write(str.toLatin1());
            cmake_config_file.write("\n");

            str = cmake_build::target_link_libraries(current_dir,sub_lists.at(i),CMAKE_STRING);
            qDebug()<<str;
            cmake_config_file.write(str.toLatin1());
            cmake_config_file.write("\n");
        }






//add_sub
        for(int i = 0;i<sub_lists.size();i++)
        {
            str.clear();
            str = cmake_build::add_subdirectory(sub_lists.at(i),CMAKE_STRING);
            qDebug()<<str;
            cmake_config_file.write(str.toLatin1());
            cmake_config_file.write("\n");
        }



    }


}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox box;
        box.setText("The project source dir is not be set,Please set the source dir!");
        box.exec();
    }else
    {
        SetTree(ui->lineEdit->text());
        AnalysisCurrentDirectoryFile(root_item,ui->lineEdit->text(),0,BUILD);
        ui->treeView->expandAll();
    }

}

void MainWindow::on_pushButton_3_clicked()
{

    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox box;
        box.setText("The project source dir is not be set,Please set the source dir!");
        box.exec();
    }
    else
    {
//        dir_model->clear();
        SetTree(ui->lineEdit->text());
        AnalysisCurrentDirectoryFile(root_item,ui->lineEdit->text(),0,CLEAN);

        ui->treeView->update();
        ui->treeView->expandAll();
    }
}


//test pusbutton
void MainWindow::on_pushButton_5_clicked()
{
    SetTree("/root/CMake_Builder/");


}






void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString file_name = index.data().toString();
    QString file_path = file_name;

    QModelIndex current_index = index;
    while(current_index.parent().isValid())
    {
        current_index  = current_index.parent();
        file_path = current_index.data().toString() + "/" + file_path;
        qDebug()<<"1"<<file_path;
    }

    qDebug()<<"L"<<file_path;

    int file_index = file_path.indexOf("/");
    file_path = file_path.right(file_path.length() - file_index - 1);
    qDebug()<<"file:"<<file_path;

    file_path = ui->lineEdit->text() + "/" + file_path;

    QFile file(file_path);
    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
        ui->textBrowser->setText(file.readAll());
}


void MainWindow::setProjectConfig(SProjcetConfig project_config)
{
    this->project_config = project_config;
    qDebug()<<"Project type"<<this->project_config.project_type;//1 exec 2 lib (root dir)
    qDebug()<<"Project root directory type"<<this->project_config.root_lib_type;
    qDebug()<<"project sub directory type:"<<this->project_config.sub_lib_type;
}
