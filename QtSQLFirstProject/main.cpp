#include "mainwindow.h"

#include <QApplication>
#include "FillDataBase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FillDataBase("my_db.sqlite");

    MainWindow w;
    w.show();

    return a.exec();
}
