#include "mainwindow.h"
#include <QApplication>
#include "project_guide.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Project_guide guide;
    guide.show();



    return a.exec();
}
