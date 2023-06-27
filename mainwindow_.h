
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
    public slots:
    void mouseMove(QMouseEvent *e);

public:
    QCustomPlot * customplot;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QCPItemTracer *tracer;
    QCPItemText *tracerLabel;

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW__H



