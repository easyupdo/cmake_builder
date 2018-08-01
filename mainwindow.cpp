 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmake_build.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    builded_flag(false),
    dir_model(NULL),
    root_item(NULL),
    quote_item_acount(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Cmake_builder");

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QString source_dir = QFileDialog::getExistingDirectory();
    quote_item_acount = 0;
    quote_list.clear();
    ui->lineEdit->setText(source_dir);
    on_pushButton_3_clicked();
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

    quote_item = new QStandardItem(QString::fromLocal8Bit("引用"));

    dir_model->setItem(0,0,root_item);
    root_item->setChild(0,0,quote_item);
    quote_item->setEditable(false);


    ui->treeView->setModel(dir_model);

}


void MainWindow::AnalysisCurrentDirectoryFile(QStandardItem *item ,QString root_dir,int dir_depth, enum BuildOrClean options_type)//Dir And File   NOUSED
{
    int item_rows = 0;
    QList<QString>current_sub_direcotry_lists;
    qDebug()<<"Set root_Dir"<<root_dir;


     if(options_type == BUILD)
    {
         QString cmake_config_path;
         cmake_config_path = CreateCmakeListsFile(root_dir);
         //root dir CMakeLists.txt
         this->SetADirectoryCMakeListFile(root_dir,cmake_config_path,quote_list,1);// have subdirectory

         QStringList::iterator itt = quote_list.begin();
         int row = 0;
         for(;itt != quote_list.end();itt++)//add quote sub project
         {
             QStandardItem * sub_quote_item = new QStandardItem(*itt);
             sub_quote_item->setEditable(false);
             quote_item->setChild(row,sub_quote_item);
             qDebug()<<"######################:"<<*itt<<row;

             QString cmake_config_path;
             cmake_config_path = CreateCmakeListsFile(*itt);
             QStringList new_list;
             new_list.clear();
              this->SetADirectoryCMakeListFile(*itt,cmake_config_path,new_list,0);// have subdirectory

             QFileInfoList file_full = QDir(*itt).entryInfoList();
             QFileInfoList::iterator itd = file_full.begin();
             item_rows = 0;
             for(itd;itd!=file_full.end();itd++)// add directory files
             {
                     if(!(*itd).suffix().compare("cpp") || !(*itd).suffix().compare("c") ||!(*itd).suffix().compare("cc")|| !(*itd).suffix().compare("h") || !(*itd).fileName().compare("CMakeLists.txt"))// file just .c .cpp
                     {
                         qDebug()<<(*itd).fileName();
                         QStandardItem * item1 = new QStandardItem((*itd).fileName());
                         item1->setEditable(false);
                         sub_quote_item->setChild(item_rows,0,item1);
                         item_rows +=1;
                     }
              }
               row += 1;

         }

    }


     if(options_type == QUOTE)
     {
         item_rows = 0;
         QFileInfoList file_full = QDir(root_dir).entryInfoList();


         QFileInfoList::iterator it = file_full.begin();

         for(it;it!=file_full.end();it++)
         {
             qDebug()<<"&&&&&&&&&&&&&&&&:"<<(*it).filePath();
                 if(!(*it).suffix().compare("cpp") || !(*it).suffix().compare("c") || !(*it).suffix().compare("cc")|| !(*it).suffix().compare("h") || !(*it).fileName().compare("CMakeLists.txt"))// file just .c .cpp
                 {
                     qDebug()<<(*it).fileName();
                     QStandardItem * item1 = new QStandardItem((*it).fileName());
                     item1->setEditable(false);
                     item->setChild(item_rows,0,item1);
                     item_rows +=1;
                 }
          }
     }


    if(options_type == CLEAN)
    {
         CleanCmakeListsFile(root_dir);//clean
        int row = 0;
        QStringList::iterator it = quote_list.begin();
        for(;it != quote_list.end();it++)
        {
            CleanCmakeListsFile(*it);//clean
            QStandardItem * sub_quote_item = new QStandardItem(*it);
             sub_quote_item->setEditable(false);
            quote_item->setChild(row,sub_quote_item);

            QFileInfoList file_full = QDir(*it).entryInfoList();
            QFileInfoList::iterator itd = file_full.begin();
            item_rows = 0;
            for(itd;itd!=file_full.end();itd++)
            {
                    if(!(*itd).suffix().compare("cpp") || !(*itd).suffix().compare("c") || !(*itd).suffix().compare("cc")|| !(*itd).suffix().compare("h") || !(*itd).fileName().compare("CMakeLists.txt"))// file just .c .cpp
                    {
                        qDebug()<<(*itd).fileName();
                        QStandardItem * item1 = new QStandardItem((*itd).fileName());
                        item1->setEditable(false);
                        sub_quote_item->setChild(item_rows,0,item1);
                        qDebug()<<"item_rows:"<<item_rows;
                        item_rows +=1;
                    }
             }

            row += 1;
        }
    }

    if(options_type == NONE)
    {
            item_rows = 1;
            QFileInfoList file_full = QDir(root_dir).entryInfoList();
            QFileInfoList::iterator it = file_full.begin();
            for(it;it!=file_full.end();it++)
            {

                    if(!(*it).suffix().compare("cpp") || !(*it).suffix().compare("c") || !(*it).suffix().compare("cc")|| !(*it).suffix().compare("h") || !(*it).fileName().compare("CMakeLists.txt"))// file just .c .cpp
                    {
                        qDebug()<<(*it).fileName();
                        QStandardItem * item1 = new QStandardItem((*it).fileName());
                        item1->setEditable(false);
                        item->setChild(item_rows,0,item1);
                        item_rows +=1;
                    }
             }
    }


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

    qDebug()<<"Clean CMakeLists.txt:"<<cmake_config_path;

}

void MainWindow::SetADirectoryCMakeListFile(QString current_dir, QString cmakelists_file, QList<QString> sub_lists, bool root)// A directory
{
    QString str;
    qDebug()<<cmakelists_file;
    QFile cmake_config_file(cmakelists_file);

    cmake_config_file.open(QIODevice::ReadWrite);

    bool status = cmake_config_file.isOpen();

    if(cmake_config_file.isOpen())
    {
        QString last_dir_name = current_dir.right(current_dir.length()- current_dir.lastIndexOf("/")-1);
        QString source_dir_argv =  last_dir_name + "SRC" ;

        QString include_dir_argv = last_dir_name + "INCLUDE_DIR";




        str = cmake_build::cmake_minimum_required("VERSION 3.10");
        cmake_config_file.write(str.toLatin1());
        cmake_config_file.write("\n");

        if(root)
        str = cmake_build::project(this->project_config.project_name);
        else
        str = cmake_build::project(last_dir_name);

            cmake_config_file.write(str.toLatin1());
            cmake_config_file.write("\n");

          //  QString RelativePath =  GetRelativePath(current_dir);
            str = cmake_build::aux_source_directory(current_dir,source_dir_argv,CMAKE_STRING);
            qDebug()<<str;
            cmake_config_file.write(str.toLatin1());
            cmake_config_file.write("\n");

    //set_include
            str.clear();
            QString include_argv = "INCLUDE_DIR";
            str = cmake_build::set(include_dir_argv,source_dir_argv,CMAKE_ARGV);
            qDebug()<<str;
            cmake_config_file.write(str.toLatin1());
            cmake_config_file.write("\n");


            str.clear();
            str = cmake_build::include_directories(include_dir_argv,CMAKE_ARGV);
            qDebug()<<str;
            cmake_config_file.write(str.toLatin1());
            cmake_config_file.write("\n");

            qDebug()<<"ERootProjectTypeKKKKKKKKKKKKKKK"<<project_config.project_type;

            if(project_config.project_type == ERootProjectType::EXEC)
            {
               if(root)
               {
                   str.clear();
                   str = cmake_build::add_executable(cmake_build::exec_name,source_dir_argv,CMAKE_ARGV);
                   qDebug()<<str;
                   cmake_config_file.write(str.toLatin1());
                   cmake_config_file.write("\n");
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


            ///******************************* 添加 第三方 库 *******************************
            ///
                if(sub_lists.length() <= 0)
                {

                    for(QStringList::iterator it = this->other_includes.begin();it != other_includes.end();it++)
                    {
                        str.clear();
                        str = cmake_build::include_directories(*it,CMAKE_STRING);
                        qDebug()<<str;
                        cmake_config_file.write(str.toLatin1());
                        cmake_config_file.write("\n");
                    }


                    for(QStringList::iterator it = this->other_libs.begin();it != other_libs.end();it++)
                    {
                        str.clear();
                        str = cmake_build::target_link_libraries(this->project_config.project_name,*it);
                        qDebug()<<str;
                        cmake_config_file.write(str.toLatin1());
                        cmake_config_file.write("\n");
                    }

                }

           //******************************** 添加 第三方 库 **************************/


            str.clear();
            if(sub_lists.length() > 0)
            for(int i =0;i<sub_lists.size();i++)
            {

                str = cmake_build::target_link_libraries(this->project_config.project_name,sub_lists.at(i),CMAKE_STRING);
                qDebug()<<str;
                cmake_config_file.write(str.toLatin1());
                cmake_config_file.write("\n");
            }


            // /*************************** 添加第三方链接库 **************************
              // //添加第三方库 使用find_ 不要使用link_directories() 使用此方法的时候 会出现找不到指定路径的库
        //*************************** 添加第三方链接库 ****************************/








    //add_sub
            if(sub_lists.length() > 0)
            {
                qDebug()<<"*****************************"<<sub_lists.length();
                for(int i = 0;i<sub_lists.size();i++)
                {
                    str.clear();

                    //QString RelativePath =  GetRelativePath(sub_lists.at(i));
                    str = cmake_build::add_subdirectory(sub_lists.at(i),CMAKE_STRING);
                    qDebug()<<str;
                    cmake_config_file.write(str.toLatin1());
                    cmake_config_file.write("\n");
                }
            }
    }
    cmake_config_file.close();
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
        AnalysisCurrentDirectoryFile(root_item,ui->lineEdit->text(),0,NONE);
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
         AnalysisCurrentDirectoryFile(root_item,ui->lineEdit->text(),0,NONE);

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
    bool flag = false;
    QString file_name = index.data().toString();
    QString file_path = file_name;

    QString dir_parent_str;
    dir_parent_str.clear();
    QModelIndex current_index = index;
    while(current_index.parent().isValid())
    {

        current_index  = current_index.parent();
        dir_parent_str  = current_index.data().toString();
        if(!dir_parent_str.compare(QString::fromLocal8Bit("引用")))
        {
            flag = true;
            break;
        }
        file_path = current_index.data().toString()+ "/" + file_path;
    }

    if(!flag)
    {
        qDebug()<<"L"<<file_path;
        int file_index = file_path.indexOf("/");
        file_path = file_path.right(file_path.length() - file_index - 1);
        qDebug()<<"file:"<<file_path;

        file_path = ui->lineEdit->text() + "/" + file_path;
        qDebug()<<"all file path:"<<file_path;
    }


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


void MainWindow::AddLibsAndIncludes(QStringList libs,QStringList includes)
{
    this->other_libs = libs;
    this->other_includes = includes;
    qDebug()<<"Receive signal!";
    for(QStringList::iterator it = other_libs.begin();it!=other_libs.end();it++)
        qDebug()<<"Receive:"<<*it;

}

QString MainWindow::GetRelativePath(QString dir)
{
    qDebug()<<"NNNNNNNNNNNN"<<dir;
    QString root_dir = ui->lineEdit->text();


    int RelativeAcount = 0;
    QString RelativeDir;
    QString now_dir;

    int root_index = root_dir.lastIndexOf("/");
    int dir_index = dir.lastIndexOf("/");
    if(root_index > dir_index)
    {
        QString tmp = dir;
        dir = root_dir;
        root_dir = tmp;
    }
      QString sub_dir = dir;

    while(root_dir != dir)//root_dir 总是短的
    {
        qDebug()<<"Now Dir:"<<dir;
        QString tmp_dir = dir.left( dir.lastIndexOf("/"));
        dir = tmp_dir;
        RelativeAcount += 1;
    }

    if(sub_dir.length() > root_dir.length())
        now_dir = sub_dir.right(sub_dir.length() - root_dir.length() - 1);



    qDebug()<<"FFFFFFFFFFFFFFF:"<<now_dir<<"KKKKKKKKKKKKKKK"<<dir;

       if(root_index > dir_index)
       {
           for(;RelativeAcount > 0; RelativeAcount--)
                RelativeDir += "../";

           RelativeDir += now_dir;
       }
       else if(root_index == dir_index)
       {
           RelativeDir += ".";
           RelativeDir += now_dir;
       }
       else
       {
           for(;RelativeAcount > 0; RelativeAcount--)
                RelativeDir += "./";

           RelativeDir += now_dir;
       }


    qDebug()<<"root_dir:"<<dir;

    return RelativeDir;
}


void MainWindow::on_actionSet_triggered()
{
    Set * set = new Set;

    connect(this,&MainWindow::ToSet,set,&Set::FromMainWinidows);
    connect(set,&Set::ToMainWindows,this,&MainWindow::AddLibsAndIncludes);

    emit this->ToSet(this->other_libs,this->other_includes);

    set->exec();
}

void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    qDebug()<<ui->treeView->indexAt(pos).data().toString();


    if(!QString::fromLocal8Bit("引用").compare(ui->treeView->indexAt(pos).data().toString()))
    {
        qDebug()<<ui->treeView->indexAt(pos).data().toString();
        QMenu *menu=new QMenu();
        QAction *addAction = new QAction(QString::fromLocal8Bit("添加引用"),this);
        connect(addAction,&QAction::triggered,this,&MainWindow::Quote);
        menu->addAction(addAction);
        menu->exec(QCursor::pos());

    }
}

void MainWindow::Quote(bool checked)
{
     QString quote_dir = QFileDialog::getExistingDirectory();

     if(quote_dir == ui->lineEdit->text())
     {
         QMessageBox box;
         box.setText("can not add self!");
         box.exec();
     }else
     {
         QStandardItem * quote_sub = new QStandardItem(quote_dir);
         quote_list.append(quote_dir);
         quote_sub->setEditable(false);
         quote_item->setChild(quote_item_acount,0,quote_sub);
         quote_item_acount += 1;

         AnalysisCurrentDirectoryFile(quote_sub,quote_dir,0,QUOTE);
         on_pushButton_3_clicked();

        qDebug()<<"Quote"<<quote_dir;
     }

}
