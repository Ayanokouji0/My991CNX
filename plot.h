
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
    //��������
    QCPItemTracer* tracer;	//�α�
    QCPItemText* textLabel;	//ͼ���ǩ
    QCPItemText* tracerLabel; //�α��ǩ
    QCPGraph* tracerGraph;//�α�Ҫ�����ĸ�graph
};

#endif // PLOT_H
