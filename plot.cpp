#include "qcustomplot.h"
#include "plot.h"
#include <QPushButton>
#include "plotwindow.h"
#include "exptree.h"
#include <stdlib.h>
#include <time.h>
Plot::Plot()
{

}
Plot::Plot(PlotWindow* parent){
    // QPushButton but;
    // but.setText("绘图");
    // but.setParent(parent);
    // but.show();

};
// void Plot::slot_plot(exptree *tree){
//     PlotWindow * w = new PlotWindow();
//     w->show();
//     makeplot(tree->eval,*w);
// }
void Plot::makeplot(exptree *tree,PlotWindow & w,bool calculus=false){
    w.show();
    QVector<double> x(3000), y(3000); //初始化向量x和y
    /* double minx=999999;
    double maxx=-999999;
    double miny=999999;
    double maxy=-999999;*/; //初始化向量x和y
    for (int i=0; i<3000; ++i)
    {
        x[i] = i/50.0 - 1; //
        y[i] = tree->eval(x[i]); //
    }
   // w.customplot->xAxis->setRange(-100, 100);
    //w.customplot->yAxis->setRange(-100, 100);
    w.customplot->addGraph();//添加数据曲线（一个图像可以有多个数据曲线）
    if(calculus){
        w.customplot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));//积分曲线图绘制
    }
    // graph(0);可以获取某个数据曲线（按添加先后排序）
    // setData();为数据曲线关联数据

    w.customplot->graph(0)->setData(x, y);
    w.customplot->graph(0)->setName("graph");// 设置图例名称
        // 为坐标轴添加标签
    w.customplot->xAxis->setLabel("x");
    w.customplot->yAxis->setLabel("y");
    w.customplot->axisRect()->setRangeZoomFactor(2);
    w.customplot->axisRect()->setRangeZoom(Qt::Vertical);
    w.tracer = new QCPItemTracer(w.customplot); //生成游标

    w.tracer->setPen(QPen(Qt::red));//圆圈轮廓颜色
    w.tracer->setBrush(QBrush(Qt::red));//圆圈圈内颜色
    w.tracer->setStyle(QCPItemTracer::tsCircle);//圆圈
    w.tracer->setSize(5);//设置大小
    // 设置坐标轴的范围，以看到所有数据
    w.tracerLabel = new QCPItemText(w.customplot); //生成游标说明
    w.tracerLabel->setLayer("overlay");//设置图层为overlay，因为需要频繁刷新
    w.tracerLabel->setPen(QPen(Qt::black));//设置游标说明颜色
    w.tracerLabel->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);//左上
    w.tracerLabel->position->setParentAnchor(w.tracer->position);
    w.customplot->rescaleAxes();
    w.customplot->legend->setVisible(true);
    w.customplot->xAxis->setTickLabels(true);
    w.customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


}
