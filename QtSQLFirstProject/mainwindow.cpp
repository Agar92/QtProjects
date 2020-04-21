#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    list = new QStringList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FillingData()
{
    std::cout<<"FillingData() BEGIN"<<std::endl;
    AddTables();
    makeRequest();
    AddColumns();
    AddValues(0);
    std::cout<<"FillingData() END"<<std::endl;
}

void MainWindow::AddTables()
{
    ui->comboBoxColumn->clear();
    std::cout<<database.tables().count()<<std::endl;
    for(const QString & tablename : database.tables())
    {
        ui->comboBoxTables->addItem(tablename);
        std::cout<<"tablename="<<tablename.toUtf8().constData()<<std::endl;
    }
}

void MainWindow::makeRequest()
{
    QString tableName = ui->comboBoxTables->currentText();
    sqlQuery.exec("SELECT * FROM "+tableName+"");
}

void MainWindow::AddColumns()
{
    ui->comboBoxColumn->clear();
    int columnCount = sqlQuery.record().count();
    for(int i=0; i<columnCount; ++i)
            ui->comboBoxColumn->addItem(sqlQuery.record().field(i).name());
}

void MainWindow::AddValues(int index)
{
    ui->listWidget->clear();
    while (sqlQuery.next()) {
        ui->listWidget->addItem(sqlQuery.value(index).toString());
    }
}

void MainWindow::refreshlist()
{
    list->clear();
    for(int i=0; i<ui->listWidget->count(); ++i)
        list->append(ui->listWidget->item(i)->text());
}


void MainWindow::on_OpenDBButton_clicked()
{
    pathToDB = QFileDialog::getOpenFileName(this, "Open file", "", "Database (*.db) (*.sqlite)");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathToDB);
    if(db.open())
    {
        std::cout<<"DB open"<<std::endl;
        sqlQuery = QSqlQuery(db);
        FillingData();
        refreshlist();

    }

}

void MainWindow::on_comboBoxTables_activated(int index)
{
    makeRequest();
    AddColumns();
    AddValues(0);
    refreshlist();
}

void MainWindow::on_comboBoxColumn_activated(int index)
{
    makeRequest();
    AddColumns();
    AddValues(index);
    refreshlist();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QRegExp regExp(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    ui->listWidget->clear();
    ui->listWidget->addItems(list->filter(regExp));

}
