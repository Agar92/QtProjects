#include "mainwindow.h"

#include <QApplication>

//See https://seeklinwin.wordpress.com/2011/04/05/qtsql-database-and-table-view-examples/ .

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
