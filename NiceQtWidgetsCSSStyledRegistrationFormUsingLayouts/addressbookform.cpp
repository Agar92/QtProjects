#include "addressbookform.h"
#include "ui_addressbookform.h"

#include <QDesktopWidget>
#include <QSqlQueryModel>

AddressBookForm::AddressBookForm(QWidget *parent, DataBase _db) :
    QMainWindow(parent),
    ui(new Ui::AddressBookForm),
    db(_db)

{
    ui->setupUi(this);

    //Скрываем элементы управления и рамку окна...
    this->setWindowFlags(Qt::FramelessWindowHint);
    //Включаем прозрачность главной формы...
    setAttribute(Qt::WA_TranslucentBackground );
    //center the frame:
    this->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());

    QPixmap pic(":/rec/img/close.png");
    int w = ui->ExitButton->width();
    int h = ui->ExitButton->height();
    pic.scaled(w, h, Qt::KeepAspectRatio);
    ui->ExitButton->setIcon(pic);
}

AddressBookForm::~AddressBookForm()
{
    delete ui;
}

void AddressBookForm::SetText(QString name, QString surname)
{
    ui->labelPerson->setText(name + " " + surname);
}

void AddressBookForm::on_ExitButton_clicked()
{
    QApplication::quit();
}

void AddressBookForm::on_AddContactButton_clicked()
{
    //Dialog addContactDialog;
    addContactDialog = new Dialog();
    connect(addContactDialog, SIGNAL(DeleteDialog()), this, SLOT(CancelSlot()));
    connect(addContactDialog, SIGNAL(AddContact()), this, SLOT(AddContactSlot()));
    addContactDialog->setModal(true);
    addContactDialog->show();
    //addContactDialog.exec();
}

void AddressBookForm::CancelSlot()
{
    delete addContactDialog;
}

void AddressBookForm::AddContactSlot()
{
    addContactDialog->hide();
    QString name = addContactDialog->GetName();
    QString surname = addContactDialog->GetSurname();
    QString phone = addContactDialog->GetPhone();

    delete addContactDialog;

    emit AddContactSignal(name, surname, phone);
}

void AddressBookForm::on_ViewContactsButton_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query(db.GetDB());
    query.exec("SELECT * FROM contacts;");
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
    QHeaderView* header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    //renames the column name:
    //model->setHeaderData(1, Qt::Horizontal, "234");



    ui->tableView->setColumnWidth(0, ui->tableView->width()/5);
    ui->tableView->setColumnWidth(1, 2 * ui->tableView->width()/5);

}
