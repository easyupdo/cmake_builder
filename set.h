#ifndef SET_H
#define SET_H

#include <QDialog>
#include"global.h"
#include <QFile>
#include <QDialog>
#include <QFileDialog>

namespace Ui {
class Set;
}

class Set : public QDialog
{
    Q_OBJECT

public:
    explicit Set(QWidget *parent = 0);
    ~Set();
signals:
    void ToMainWindows(QStringList libs);

public slots:
    void FromMainWinidows(QStringList libs);

private slots:

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::Set *ui;
    QStringList libs_list;
};

#endif // SET_H
