
#ifndef PLOT_H
#define PLOT_H
#include"mainwindow_.h"
#include"qcustomplot.h"


class Plot
{
public:
    Plot();
    Plot(MainWindow * parent);
    void makeplot(double func (double),MainWindow &,bool );
    Ui::MainWindow * ui;
    //新增变量
    QCPItemTracer *tracer;	//游标
    QCPItemText *textLabel;	//图标标签
    QCPItemText *tracerLabel; //游标标签
    QCPGraph *tracerGraph;//游标要吸附哪个graph
};

#endif // PLOT_H
