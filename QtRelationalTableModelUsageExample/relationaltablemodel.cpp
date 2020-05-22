#include <QtWidgets>
#include <QtSql>

#include <memory>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

const QString DBName = QString("DB.db");

static QSqlDatabase db;

static bool createConnection()
{
   db = QSqlDatabase::addDatabase("QSQLITE");
// See http://www.sqlite.org/c3ref/open.html:
// If the filename is ":memory:", then a private, temporary in-memory database
// is created for the connection. This in-memory database will vanish when the
// database connection is closed. Future versions of SQLite might make use of
// additional special filenames that begin with the ":" character. It is
// recommended that when a database filename actually does begin with a ":"
// character you should prefix the filename with a pathname such as "./" to avoid ambiguity.
    //db.setDatabaseName(":memory:");
    db.setDatabaseName(DBName);
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs SQLite support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
    query.exec("create table person (id int primary key, "
               "firstname varchar(20), lastname varchar(20))");
    if(!QFile::exists(QDir::currentPath() + "/" + DBName))
    {
        query.exec("insert into person values(101, 'Danny', 'Young')");
        query.exec("insert into person values(102, 'Christine', 'Holand')");
        query.exec("insert into person values(103, 'Lars', 'Gordon')");
        query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
        query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");

        query.exec("create table items (id int primary key,"
                                             "imagefile int,"
                                             "itemtype varchar(20),"
                                             "description varchar(100))");
        query.exec("insert into items "
               "values(0, 0, 'Qt',"
               "'Qt is a full development framework with tools designed to "
               "streamline the creation of stunning applications and  "
               "amazing user interfaces for desktop, embedded and mobile "
               "platforms.')");
        query.exec("insert into items "
               "values(1, 1, 'Qt Quick',"
               "'Qt Quick is a collection of techniques designed to help "
               "developers create intuitive, modern-looking, and fluid "
               "user interfaces using a CSS & JavaScript like language.')");
        query.exec("insert into items "
               "values(2, 2, 'Qt Creator',"
               "'Qt Creator is a powerful cross-platform integrated "
               "development environment (IDE), including UI design tools "
               "and on-device debugging.')");
        query.exec("insert into items "
               "values(3, 3, 'Qt Project',"
               "'The Qt Project governs the open source development of Qt, "
               "allowing anyone wanting to contribute to join the effort "
               "through a meritocratic structure of approvers and "
               "maintainers.')");
    }

    query.exec("create table images (itemid int, file varchar(20))");
    if(!QFile::exists(QDir::currentPath() + "/" + DBName))
    {
        query.exec("insert into images values(0, 'images/qt-logo.png')");
        query.exec("insert into images values(1, 'images/qt-quick.png')");
        query.exec("insert into images values(2, 'images/qt-creator.png')");
        query.exec("insert into images values(3, 'images/qt-project.png')");
    }

    return true;
}

void initializeModel(QSqlRelationalTableModel *model)
{
    model->setTable("employee");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setRelation(2, QSqlRelation("city", "id", "name"));
    model->setRelation(3, QSqlRelation("country", "id", "name"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("City"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Country"));
    model->select();
}

std::unique_ptr<QTableView> createView(const QString &title, QSqlTableModel *model)
{
    std::unique_ptr<QTableView> view{new QTableView};
    view->setModel(model);
    view->setItemDelegate(new QSqlRelationalDelegate(view.get()));

    view->setWindowTitle(title);
    return view;
}

void createRelationalTables()
{
    QSqlQuery query;

    if(QFile::exists(DBName))
        QMessageBox::information(new QWidget(), "DB", "Database exists");
    else
        QMessageBox::critical(new QWidget(), "DB", "Database does not exist");

    if(db.tables().contains(QLatin1String("employee")))
        QMessageBox::information(new QWidget(), "DB", "Table employee exists");
    else
        QMessageBox::critical(new QWidget(), "DB", "Table employee does not exist");

    if(!db.tables().contains(QLatin1String("employee")))
    {
        query.exec("create table if not exists employee(id int primary key, name varchar(20), city int, country int)");
        query.exec("insert into employee values(1, 'Espen', 5000, 47)");
        query.exec("insert into employee values(2, 'Harald', 80000, 49)");
        query.exec("insert into employee values(3, 'Sam', 100, 1)");
        query.exec("create table if not exists city(id int, name varchar(20))");
        query.exec("insert into city values(100, 'San Jose')");
        query.exec("insert into city values(5000, 'Oslo')");
        query.exec("insert into city values(80000, 'Munich')");
        query.exec("create table if not exists country(id int, name varchar(20))");
        query.exec("insert into country values(1, 'USA')");
        query.exec("insert into country values(47, 'Norway')");
        query.exec("insert into country values(49, 'Germany')");
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (!createConnection())
        return EXIT_FAILURE;

    createRelationalTables();

    QSqlRelationalTableModel model;

    initializeModel(&model);

    std::unique_ptr<QTableView> view = createView(QObject::tr("Relational Table Model"), &model);
    view->show();

    return app.exec();
}
