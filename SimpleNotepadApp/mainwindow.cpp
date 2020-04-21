#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <iostream>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include <QFontDialog>
#include <QFont>

#include <QColorDialog>
#include <QColor>

#include <QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    file_path = "";
    ui->textEdit->setText("");
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a new file");
    QFile file(file_name);
    file_path= file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "..", "file not opened");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "..", "file not opened");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save the file");
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "..", "file not opened");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();

    qDebug() << text;

    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    qDebug() << "CUT";
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    qDebug() << "COPY";
    ui->textEdit->copy();

}

void MainWindow::on_actionPaste_triggered()
{
    qDebug() << "PASTE";
    ui->textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    qDebug() << "REDO";
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    qDebug() << "UNDO";
    ui->textEdit->undo();
}

void MainWindow::on_actionAbout_Notepad_triggered()
{
    QString about_text;
    about_text = "Author: smb\n";
    about_text += "Date: 1.04.2020\n";
    about_text += "(C) Notepad (R)\n";
    QMessageBox::information(this, "About Notepad", about_text);
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
    else return;
}

void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color:");
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
    else return;
}

void MainWindow::on_actionBackground_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color:");
    if(color.isValid())
    {
        ui->textEdit->setTextBackgroundColor(color);
    }
    else return;
}

void MainWindow::on_actionBackground_Color_Edit_Text_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color:");
    if(color.isValid())
    {
        ui->textEdit->setPalette(QPalette(color));
    }
    else return;
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("desire printer name");
    QPrintDialog dialog(&printer, this);
    if(dialog.exec()) return;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("output.pdf");
    ui->textEdit->print(&printer);
}
