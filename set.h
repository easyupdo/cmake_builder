#ifndef SET_H
#define SET_H

#include <QDialog>
#include"global.h"

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
    void ToMainWindows(QString project_name , ProjectProperty project_type);

private slots:

    void on_checkBox_clicked(bool checked);

    void on_pushButton_clicked();

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_3_clicked(bool checked);

    void on_checkBox_4_clicked(bool checked);

private:
    Ui::Set *ui;
};

#endif // SET_H
