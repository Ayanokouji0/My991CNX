
#ifndef MAINWINDOW__H
#define MAINWINDOW__H

#include <QMainWindow>
#include "qcustomplot.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT
    //新增两个槽函数，游标控制和图例曲线同步选中
    public slots:
    void mouseMove(QMouseEvent *e);
    void selectionChanged();
    //void change();
public:
    QCustomPlot * customplot;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //新增变量
    QCPItemTracer *tracer;
    QCPItemText *tracerLabel;

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW__H



