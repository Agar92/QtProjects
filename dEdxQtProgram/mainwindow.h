#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_exitButton_clicked();

    void CurveSelected();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QVector<double> x;
    QVector<double> y;
    QColor color;

    //this is for moving the window with
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;


    void ReadData(QString material);
    void Plot(QString material, bool changedColor=false);

};
#endif // MAINWINDOW_H
