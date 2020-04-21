#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlField>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QRegExp>

#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QSqlDatabase database;
    QSqlQuery sqlQuery;
    QString pathToDB;
    QStringList * list;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OpenDBButton_clicked();

    void on_comboBoxTables_activated(int index);

    void on_comboBoxColumn_activated(int index);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    void FillingData();
    void AddTables();
    void makeRequest();
    void AddColumns();
    void AddValues(int index);

    void refreshlist();
};
#endif // MAINWINDOW_H
