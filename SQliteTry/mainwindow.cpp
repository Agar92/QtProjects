#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQueryModel>
#include <QtSql/QSqlQuery>

#include <QDebug>
#include <QSqlRecord>
#include <QtSql/QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    qDebug() << "STEP #1";

    ui->setupUi(this);
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("mydb.sqlite");
        if (!db.open()) {
            qDebug() << "Database not opened!";
        }

    qDebug() << "STEP #2";

    QSqlQuery query(db);
    query.exec("select * from one;");
    QSqlRecord rec = query.record();
    int id, age;
    QString name;
    qDebug() << query.next();
    while (query.next()) {
        id = query.value(rec.indexOf("id")).toInt();
        name = query.value(rec.indexOf("name")).toString();
        age = query.value(rec.indexOf("address")).toInt();

        qDebug() << "id is " << id
                 << ". name is " << name
                 << ". age is" << age
                 << query.lastError().text()
                 << query.lastError().number();
        }

    qDebug() << "STEP #3";

    model->setQuery(query);
    ui->tableView->setModel(model);

    qDebug() << "STEP #4";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ViewButton_clicked()
{




}
