
#ifndef PLOTWINDOW__H
#define PLOTWINDOW__H

#include <QWidget>
#include "qcustomplot.h"


QT_BEGIN_NAMESPACE
namespace Ui { class PlotWindow; }
QT_END_NAMESPACE

class PlotWindow : public QWidget

{
    Q_OBJECT
    public slots:
    void mouseMove(QMouseEvent *e);
    void selectionChanged();

public:
    QCustomPlot * customplot;
    PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();
    QCPItemTracer *tracer;
    QCPItemText *tracerLabel;

private:
    Ui::PlotWindow *ui;

};

#endif // PLOTWINDOW__H



