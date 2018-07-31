#include "mainwindow.h"
#include <QApplication>
#include "project_guide.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString root_dir = "hello/k";

    int index = root_dir.lastIndexOf("/");
    qDebug()<<"Index:"<<index;



    Project_guide guide;
    guide.show();

    return a.exec();
}
