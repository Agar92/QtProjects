#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include <QtSql/QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Скрываем элементы управления и рамку окна...
    this->setWindowFlags(Qt::FramelessWindowHint);
    //Включаем прозрачность главной формы...
    setAttribute(Qt::WA_TranslucentBackground );
    //center the frame:
    this->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());
    QPixmap pic("://close.png");
    int w = ui->exitButton->width();
    int h = ui->exitButton->height();
    pic.scaled(w, h, Qt::KeepAspectRatio);
    ui->exitButton->setIcon(pic);

    ui->statusbar->showMessage(QString("Hydrogen is chosen"));


    connect(ui->comboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(on_comboBox_currentIndexChanged(const QString &)));

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dEdxDB.db");
    if (!db.open()) qDebug() << "Database not opened!";

    ReadData("Hydrogen");//"Titanium");
    Plot("Hydrogen");//"Titanium");
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->widget, &QCustomPlot::plottableClick, this, &MainWindow::CurveSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->statusbar->showMessage(arg1 + " is chosen");//, 2000);
    ReadData(arg1);
    Plot(arg1);
}

void MainWindow::ReadData(QString material)
{
    x.clear();
    y.clear();
    QSqlQuery query(db);
    QString tablename;
    if(material=="Hydrogen")      tablename="dedxh";
    else if(material=="Titanium") tablename="dedxti";
    query.exec("SELECT * FROM " + tablename + ";");
    QSqlRecord rec = query.record();
    int id;
    double E, dEdx;
    QString name;
    //qDebug() << query.next();
    int count=0;
    //query.first();
    while (query.next()) {
        id = query.value(rec.indexOf("index")).toInt();
        E = query.value(rec.indexOf("E")).toDouble();
        dEdx = query.value(rec.indexOf("dEdx")).toDouble();
        x.push_back(log(E));
        y.push_back(log(dEdx));

        ++count;

        qDebug() << "id is " << id
                 << ". E is " << E
                 << ". dEdx is" << dEdx
                 << " count=" <<count
                 << query.lastError().text()
                 << query.lastError().number();
        //exit(0);
        }
    qDebug() << "count=" << count;
    assert(count==132 && "Not 132 values in the database!");
}

void MainWindow::Plot(QString material, bool changedColor)
{
    static const int N=132;//(b-a)/h + 2; //Вычисляем количество точек, которые будем отрисовывать
    double a = x[0]; //Начало интервала, где рисуем график по оси Ox
    double b = x[N-1]; //Конец интервала, где рисуем график по оси Ox
    //QVector<double> x(N), y(N); //Массивы координат точек

    qDebug() << "Plot:"<< endl;
//    for(int i=0; i<N; ++i) qDebug() << "x=" << x[i] <<" y=" << y[i];
//    qDebug() << "\n";

    ui->widget->clearGraphs();//Если нужно, то очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);

//    if(changedColor)              ui->widget->graph(0)->setPen(color);//задаем цвет точки
//    else if(material=="Hydrogen") ui->widget->graph(0)->setPen(QColor(200, 0, 0, 255));//задаем цвет точки
//    else if(material=="Titanium") ui->widget->graph(0)->setPen(QColor(0, 0, 200, 255));//задаем цвет точки

    if(!changedColor)
    {
        if(material=="Hydrogen")      color = QColor(200, 0, 0, 255);//задаем цвет точки
        else if(material=="Titanium") color = QColor(0, 0, 200, 255);//задаем цвет точки
    }
    QPen pen;
    pen.setColor(color);
    pen.setWidth(2);
    qDebug() << "color=" << color << endl;
    ui->widget->graph(0)->setPen(pen);
    /*
    ui->wui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));//задаем цвет точкиidget->graph(0)->setPen(QColor(50, 50, 50, 255));//задаем цвет точки
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии
    //формируем вид точек
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    */

    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("E, MeV");
    ui->widget->yAxis->setLabel(QString("dE/dx of protons in %1, Mev cm^2/gr").arg(material));
    //Установим область, которая будет показываться на графике
    //ui->widget->xAxis->setRange(a, b);//Для оси Ox
    ui->widget->xAxis->setRange(-7.0, 9.0);//Для оси Ox

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    double minY = y[0], maxY = y[0];
    for (int i=1; i<N; i++)
    {
        if (y[i]<minY) minY = y[i];
        if (y[i]>maxY) maxY = y[i];
    }
    //ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy
    ui->widget->yAxis->setRange(0.01, 10.0);//Для оси Oy
    ui->widget->xAxis2->setRange(-7.0, 9.0);//Для оси Ox
    ui->widget->xAxis2->setVisible(true);
    ui->widget->yAxis2->setRange(0.01, 10.0);//Для оси Oy
    ui->widget->yAxis2->setVisible(true);
    //И перерисуем график на нашем widget
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iSelectPlottables, true);
    // pass data points to graphs:
    ui->widget->replot();
    //ui->widget->graph(0)->selected();
}


void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::CurveSelected()
{
    qDebug() << "Curve selected!" << endl;
    QString curmat=0;
    for(int i=0; i<ui->widget->graphCount(); ++i)
    {
        if(ui->widget->graph(i)->selected()) curmat = ui->comboBox->currentText();
    }
    int ret = QMessageBox::question(this, "Pressed on the curve", QString("Do You wish to change the %1 curve color?").arg(curmat),
                                    QMessageBox::No, QMessageBox::Yes);
    qDebug() << "ret=" << ret;

    if(ret == QMessageBox::Yes)
    {
        color = QColorDialog::getColor(Qt::blue);
        qDebug() << color;
        if(color.isValid()) Plot(ui->comboBox->currentText(), true);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

