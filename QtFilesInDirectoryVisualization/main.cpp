#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QFileSystemModel>
#include <QListView>
#include <QTreeView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Готовая модель файловой системы:
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::homePath());
    //Показать как дерево, пользуясь готовым видом:
    QTreeView *tree = new QTreeView();
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::homePath()));
     //берем данные только через модель!
    tree->show();
    tree->resize(700, 500);

    //Показать как список, пользуясь готовым видом:
    QListView *list = new QListView();
    list->setModel(model);
    list->setRootIndex(model->index(QDir::homePath()));
    list->show();
    list->resize(700, 500);
    //так как не размещаем компоненты, будет в новом окне
    return a.exec();
}
