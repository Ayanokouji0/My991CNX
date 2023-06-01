#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SvgW = new QSvgWidget(this);
    ui->gridLayout->addWidget(SvgW);
    m_texsvg = new TexSVG();
    m_tree = exptree(0);
    connect(m_texsvg, &TexSVG::rendered,
    this, &MainWindow::updSvg);
//    connect(m_texsvg, &TexSVG::loadFinished,
//            this, &MainWindow::loadSvg);
    m_texsvg->load();
    m_texsvg->render(m_tree.to_latex(nullptr).c_str());
    SvgW->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::loadSvg(bool isLoaded)
//{
//    if (isLoaded)
//        m_texsvg->render("x^2");
    
//}

void MainWindow::updSvg(QString latex, QByteArray svg)
{
    SvgW->load(svg);
}
