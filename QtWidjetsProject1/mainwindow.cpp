#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QPixmap>
#include <QIcon>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/resources/img/smailik-ylibka-1.jpg");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    ui->statusbar->addPermanentWidget(ui->label_3, 1);
    ui->statusbar->addPermanentWidget(ui->progressBar, 3);
    ui->checkBox->setChecked(true);
//    ui->comboBox->addItem(QIcon(":/rec/img/close.png"), "Mark");
//    ui->comboBox->addItem(QIcon(":/rec/img/new.jpg"), "John");
//    ui->comboBox->addItem(QIcon(":/rec/img/open.jpg"), "July");

    for(int i=0; i<10; ++i)
    {
        ui->comboBox->addItem(QString::number(i) + "name");
    }

    ui->comboBox->insertItem(3, QIcon(":/rec/img/close.png"), "new text");

//    ui->listWidget->addItem("Mark");
//    ui->listWidget->addItem("John");
//    ui->listWidget->addItem("July");
    QListWidgetItem * item1 = new QListWidgetItem(QIcon(":/rec/img/close.png"), "Mark");
    ui->listWidget->addItem(item1);
    QListWidgetItem * item2 = new QListWidgetItem(QIcon(":/rec/img/new.jpg"), "July");
    ui->listWidget->addItem(item2);
    QListWidgetItem * item3 = new QListWidgetItem(QIcon(":/rec/img/open.jpg"), "John");
    ui->listWidget->addItem(item3);

    QDir dir;//("/home/andrey/Desktop/QtProjects/QtWidjetsProject1");
    foreach (QFileInfo var, dir.drives()) {
        ui->comboBox->addItem(var.absoluteFilePath());
    }

    QDir dir2;
    foreach (QFileInfo var, dir.entryInfoList()) {
        if(var.isDir())  ui->listWidget->addItem("Dir: " + var.absoluteFilePath());
        if(var.isFile()) ui->listWidget->addItem("File: " + var.absoluteFilePath());
    }

//    if(dir.exists())
//    {
//        QMessageBox::information(this, "title", "true");
//    }
//    else
//    {
//        QMessageBox::information(this, "title", "false");
//    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    if(username == "test" && password=="test")
    {
        QMessageBox::information(this, "Login", "Username and password are correct");
        hide();
        secdialog = new SecDialog(this);
        secdialog->show();
        ui->statusbar->showMessage("Username and password are correct", 1000);
        ui->label_3->setText("Username and password are correct");
    }
    else
    {
        QMessageBox::warning(this, "Login", "Username and password are not correct");
        SecDialog secdialog;
        secdialog.setModal(true);
        secdialog.exec();
        ui->statusbar->showMessage("Username and password are incorrect", 1000);
        ui->label_3->setText("Username and password are incorrect");
    }
}

void MainWindow::on_pushButton_CheckBox_clicked()
{
    if(ui->checkBox->isChecked())
    {
        QMessageBox::information(this, "apples", "Yes, user likes apples");
    }
    else
    {
        QMessageBox::information(this, "apples", "No, user does not like apples");
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        QMessageBox::information(this, "apples", "Yes, user likes apples");
    }
    else
    {
        QMessageBox::information(this, "apples", "No, user does not like apples");
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->radioButton1->isChecked())
    {
        QMessageBox::information(this, "title" , "Mark");
    }
    if(ui->radioButton_2->isChecked())
    {
        QMessageBox::information(this, "title" , "John");
    }
}

void MainWindow::on_actionNew_triggered()
{
    QMessageBox::information(this, "title", "New");
}

void MainWindow::on_actionOpen_triggered()
{
    QMessageBox::information(this, "title", "Open");
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_combo_clicked()
{
    QMessageBox::information(this, "title", QString::number(ui->comboBox->currentIndex()));
}

void MainWindow::on_pushButton_2_clicked()
{

    QMessageBox::information(this, "HERE WE ARE", "HERE WE ARE");

//    QMessageBox::information(this, "title", ui->listWidget->currentItem()->text());
    //ui->listWidget->currentItem()->setBackgroundColor(Qt::red);
    QDir dir("/home/andrey/Desktop/QtProjects/QtWidjetsProject1/YYY");
    if(dir.exists())
    {
        QMessageBox::information(this, "title", "dir exists");
    }
    else
    {
        QMessageBox::information(this, "title", "dir does not exist");
        dir.mkdir("/home/andrey/Desktop/QtProjects/QtWidjetsProject1/YYY");
    }
}
