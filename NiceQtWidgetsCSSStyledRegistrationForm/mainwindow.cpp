#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDesktopWidget>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Скрываем элементы управления и рамку окна...
    this->setWindowFlags(Qt::FramelessWindowHint);
    //Включаем прозрачность главной формы...
    setAttribute(Qt::WA_TranslucentBackground );

    //ui->centralwidget->setStyleSheet("background-color: blue;");
    //ui->centralwidget->setFixedSize(this->size());
    this->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());

    QPixmap pic(":/rec/img/close.png");
    int w = ui->ExitButton->width();
    int h = ui->ExitButton->height();
    pic.scaled(w, h, Qt::KeepAspectRatio);
    ui->ExitButton->setIcon(pic);

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::IsRegistered(QString login, QString password)
{
    return false;
}


void MainWindow::on_LoginButton_clicked()
{
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();
    bool isRegistered = IsRegistered(login, password);
    if(isRegistered)
    {

    }
    else
    {
        QMessageBox::warning(this, "Not registered user tries to log in", "You need to register first");
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void MainWindow::on_ExitButton_clicked()
{
    QApplication::quit();
}
