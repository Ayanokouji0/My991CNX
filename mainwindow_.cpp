
#include "mainwindow_.h"
#include "ui_mainwindow_.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    customplot=ui->customPlot;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMove(QMouseEvent *e)
{
    //获得鼠标位置处对应的横坐标数据x
    double x = customplot->xAxis->pixelToCoord(e->pos().x());

    tracer->setGraph(customplot->graph(0)); //将游标和该曲线图层想连接
    tracer->setGraphKey(x); //将游标横坐标设置成刚获得的横坐标数据x
    tracer->setInterpolating(true); //游标的纵坐标可以通过曲线数据线性插值自动获得
    tracer->updatePosition(); //使得刚设置游标的横纵坐标位置生效
    //更新游标说明的内容
    double xValue = tracer->position->key();
    double yValue = tracer->position->value();
    tracerLabel->setText(QString("x = %1, y = %2").arg(xValue).arg(yValue));

    customplot->replot(); //重绘
    connect(customplot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove1(QMouseEvent*)));
}
