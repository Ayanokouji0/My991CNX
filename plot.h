
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
// public slots:
//     void slot_plot(double func (double));
};

#endif // PLOT_H
