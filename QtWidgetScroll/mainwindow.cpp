#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,0);
    QPalette p;
    p.setColor(QPalette::Background, Qt::red);
    /* И устанавливаем палитру на QSplitter
    * */
    QPen pen;
    pen.setWidth(5);
    ui->splitter->setPalette(p);
    ui->splitter->setHandleWidth(100);

}

MainWindow::~MainWindow()
{
    delete ui;
}
