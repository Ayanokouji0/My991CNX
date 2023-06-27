
#ifndef PLOT_H
#define PLOT_H
#include"mainwindow_.h"



class Plot
{
public:
    Plot();
    Plot(MainWindow * parent);
    void makeplot(double func (double),MainWindow &,bool );
    Ui::MainWindow * ui;
};

#endif // PLOT_H
