
#ifndef PLOT_H
#define PLOT_H

#include "plotwindow.h"
#include "exptree.h"



class Plot : public QObject
{
    Q_OBJECT
public:
    Plot();
    Plot(PlotWindow * parent);
    void makeplot(exptree*,PlotWindow &,bool );
    Ui::PlotWindow * ui;
    //新增变量
    QCPItemTracer* tracer;	//游标
    QCPItemText* textLabel;	//图标标签
    QCPItemText* tracerLabel; //游标标签
    QCPGraph* tracerGraph;//游标要吸附哪个graph
};

#endif // PLOT_H
