
#include "plotwindow.h"
#include "ui_plotwindow.h"


PlotWindow::PlotWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
    customplot=ui->customPlot;
    setWindowFlags(Qt::Window);
    setWindowTitle("Plot");
    //新增
    tracer = new QCPItemTracer(customplot); //生成游标

    tracer->setPen(QPen(Qt::red));//圆圈轮廓颜色
    tracer->setBrush(QBrush(Qt::red));//圆圈圈内颜色
    tracer->setStyle(QCPItemTracer::tsCircle);//圆圈
    tracer->setSize(5);//设置大小
    //游标说明
    tracerLabel = new QCPItemText(customplot); //生成游标说明
    tracerLabel->setLayer("overlay");//设置图层为overlay，因为需要频繁刷新
    tracerLabel->setPen(QPen(Qt::black));//设置游标说明颜色
    tracerLabel->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);//左上
    tracerLabel->position->setParentAnchor(tracer->position);//将游标说明锚固在tracer位置处，实现自动跟随

    connect(customplot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    //设置基本坐标轴（左侧Y轴和下方X轴）可拖动、可缩放、曲线可选、legend可选、设置伸缩比例，使所有图例可见
    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    //设置legend只能选择图例
    customplot->legend->setSelectableParts(QCPLegend::spItems);
    connect(customplot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect(customplot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(change()));
	

}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::mouseMove(QMouseEvent *e)
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
    //connect(customplot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
}

void PlotWindow::selectionChanged()
{

    if (customplot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) ||
        customplot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        customplot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) ||
        customplot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        customplot->xAxis2->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels);
        customplot->xAxis->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels);
    }

    if (customplot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) ||
        customplot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        customplot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) ||
        customplot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        customplot->yAxis2->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels);
        customplot->yAxis->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels);
    }

    // 将图形的选择与相应图例项的选择同步
    for (int i = 0; i < customplot->graphCount(); ++i)
    {
        QCPGraph* graph = customplot->graph(i);
        QCPPlottableLegendItem* item = customplot->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            item->setSelected(true);
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
            //graph->setSelected(true);
        }
    }
}
