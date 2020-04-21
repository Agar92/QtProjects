#include "FillDataBase.h"
#include <QDir>

#include <iostream>

int FillDataBase(QString DBname)
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    QString NAME = QDir::currentPath()+QString("/my_db.sqlite");
    std::cout<<"NAME="<<NAME.toUtf8().constData()<<std::endl;
    dbase.setDatabaseName(NAME);//"my_db.sqlite");
    if (!dbase.open()) {
        qDebug() << "Что-то пошло не так!";
        return -1;
    }

    QSqlQuery a_query = QSqlQuery(dbase);
    // DDL query
    QString str = "CREATE TABLE IF NOT EXISTS my_table ("
            "number integer PRIMARY KEY NOT NULL, "
            "address VARCHAR(255), "
            "age integer"
            ");";
    bool b = a_query.exec(str);
    if (!b) {
        qDebug() << "Вроде не удается создать таблицу, провертье карманы! b="<<b;
        //qDebug() << a_query.l
    }

    a_query.clear();

    // DML
    QString str_insert = "INSERT INTO my_table(number, address, age) "
            "VALUES (%1, '%2', %3);";
    str = str_insert.arg("14")
            .arg("hello world str.")
            .arg("37");
    b = a_query.exec(str);
    if (!b) {
        qDebug() << "Кажется данные не вставляются, проверьте дверь, может она закрыта?";
    }
    //.....
    if (!a_query.exec("SELECT * FROM my_table")) {
        qDebug() << "Даже селект не получается, я пас.";
        return -2;
    }
    QSqlRecord rec = a_query.record();
    int number = 0,
            age = 0;
    QString address = "";

    while (a_query.next()) {
        number = a_query.value(rec.indexOf("number")).toInt();
        age = a_query.value(rec.indexOf("age")).toInt();
        address = a_query.value(rec.indexOf("address")).toString();

        qDebug() << "number is " << number
                 << ". age is " << age
                 << ". address" << address;
    }
}
