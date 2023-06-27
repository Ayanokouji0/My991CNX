#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // plt
    pltw = new PlotWindow(this);
    // pltw->setWindowFlags(Qt::Popup);
    pltw->setWindowModality(Qt::WindowModal);

	plt = new Plot(pltw);
	// connect(pltw->customplot, &QCustomPlot::mouseMove,
	// 	this, &MainWindow::mouseMove);
	// connect(pltw->customplot, &QCustomPlot::mousePress, 

    // svg
    SvgW = new QSvgWidget(this);
    ui->SVGLayout->addWidget(SvgW);
    m_texsvg = new TexSVG();
    m_tree = new exptree(0);
    delete m_tree->root;
	m_tree->root = new exptree::blank();
    m_tree->selected = nullptr;
    connect(m_texsvg, &TexSVG::rendered,
        this, &MainWindow::updSvg);
    connect(m_tree, &exptree::changed,
        this, &MainWindow::loadSvg);
    
    // push buttons
    LeftPshBtn = new QPushButton(this);
    LeftPshBtn->setText("<-");
    ui->LeftLayout->addWidget(LeftPshBtn);
    connect(LeftPshBtn, &QPushButton::clicked,
        m_tree, &exptree::prev);

    RightPshBtn = new QPushButton(this);
    RightPshBtn->setText("->");
    ui->RightLayout->addWidget(RightPshBtn);
    connect(RightPshBtn, &QPushButton::clicked,
		m_tree, &exptree::next);

    FracPshBtn = new QPushButton(this);
    FracPshBtn->setText("Frac");
    ui->FracLayout->addWidget(FracPshBtn);
    connect(FracPshBtn, &QPushButton::clicked,
        m_tree, [=](){m_tree->add_oper(exptree::frc); });

	SqrtPshBtn = new QPushButton(this);
	SqrtPshBtn->setText("Sqrt");
	ui->SqrtLayout->addWidget(SqrtPshBtn);
	connect(SqrtPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::sqrt); });

	PowPshBtn = new QPushButton(this);
	PowPshBtn->setText("Pow");
	ui->PowLayout->addWidget(PowPshBtn);
	connect(PowPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::pow); });

	LogPshBtn = new QPushButton(this);
	LogPshBtn->setText("Log");
	ui->LogLayout->addWidget(LogPshBtn);
	connect(LogPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::log); });

	LnPshBtn = new QPushButton(this);
	LnPshBtn->setText("Ln");
	ui->LnLayout->addWidget(LnPshBtn);
	connect(LnPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::ln); });

	SinPshBtn = new QPushButton(this);
	SinPshBtn->setText("Sin");
	ui->SinLayout->addWidget(SinPshBtn);
	connect(SinPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::sin); });

	CosPshBtn = new QPushButton(this);
	CosPshBtn->setText("Cos");
	ui->CosLayout->addWidget(CosPshBtn);
	connect(CosPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::cos); });

	TanPshBtn = new QPushButton(this);
	TanPshBtn->setText("Tan");
	ui->TanLayout->addWidget(TanPshBtn);
	connect(TanPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::tan); });

	CscPshBtn = new QPushButton(this);
	CscPshBtn->setText("Csc");
	ui->CscLayout->addWidget(CscPshBtn);
	connect(CscPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::csc); });

	SecPshBtn = new QPushButton(this);
	SecPshBtn->setText("Sec");
	ui->SecLayout->addWidget(SecPshBtn);
	connect(SecPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::sec); });

	CotPshBtn = new QPushButton(this);
	CotPshBtn->setText("Cot");
	ui->CotLayout->addWidget(CotPshBtn);
	connect(CotPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::cot); });

	AddPshBtn = new QPushButton(this);
	AddPshBtn->setText("+");
	ui->AddLayout->addWidget(AddPshBtn);
	connect(AddPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::add); });

	SubPshBtn = new QPushButton(this);
	SubPshBtn->setText("-");
	ui->SubLayout->addWidget(SubPshBtn);
	connect(SubPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::sub); });

	MulPshBtn = new QPushButton(this);
	MulPshBtn->setText("*");
	ui->MulLayout->addWidget(MulPshBtn);
	connect(MulPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::mul); });

	DivPshBtn = new QPushButton(this);
	DivPshBtn->setText("/");
	ui->DivLayout->addWidget(DivPshBtn);
	connect(DivPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::div); });

	AbsPshBtn = new QPushButton(this);
	AbsPshBtn->setText("Abs");
	ui->AbsLayout->addWidget(AbsPshBtn);
	connect(AbsPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::abs); });

	ACPshBtn = new QPushButton(this);
	ACPshBtn->setText("AC");
	ui->ACLayout->addWidget(ACPshBtn);
	connect(ACPshBtn, &QPushButton::clicked,
		m_tree, &exptree::all_clear);

    DelPshBtn = new QPushButton(this);
    DelPshBtn->setText("Del");
    ui->DelLayout->addWidget(DelPshBtn);
    connect(DelPshBtn, &QPushButton::clicked,
        m_tree, &exptree::del);

	VarPshBtn = new QPushButton(this);
	VarPshBtn->setText("X");
	ui->VarLayout->addWidget(VarPshBtn);
	connect(VarPshBtn, &QPushButton::clicked,
		m_tree, &exptree::add_var);

	EvalPshBtn = new QPushButton(this);
	EvalPshBtn->setText("=");
	ui->EvalLayout->addWidget(EvalPshBtn);
	connect(EvalPshBtn, &QPushButton::clicked,
		m_tree, &exptree::slot_eval);

	//EvalPopUp = new EvalPopUpWidget(this);
	//EvalPopUp->setWindowFlags(Qt::Popup);
	//EvalPopUp->setWindowModality(Qt::WindowModal);
	//EvalPopUp->setFocusPolicy(Qt::NoFocus);
	//EvalPopUp->setFocusProxy(this);
	//EvalPopUp->setAutoFillBackground(true);
	//EvalPopUp->setPalette(QPalette(QColor(255, 255, 255, 255)));
	//EvalPopUp->setGeometry(0, 0, 100, 100);
	//EvalPopUp->setMouseTracking(true);
	//EvalPopUp->hide();

	//EvalXPshBtn = new QPushButton(this);
	//EvalXPshBtn->setText("EvalX");
	//ui->EvalXLayout->addWidget(EvalXPshBtn);
	//connect(EvalXPshBtn, &QPushButton::clicked,
	//	m_tree, [=](){m_tree->slot_eval(x)});

	PltPshBtn = new QPushButton(this);
	PltPshBtn->setText("Plot");
	ui->PltLayout->addWidget(PltPshBtn);
	connect(PltPshBtn, &QPushButton::clicked,
        plt, [=](){
        plt->makeplot(m_tree, *pltw, false);
    });

	// line edit
	NumEdit = new QLineEdit(this);
	ui->InputLayout->addWidget(NumEdit);
	NumEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$")));
	connect(NumEdit, &QLineEdit::returnPressed,
		m_tree, [=]() {m_tree->add_number(NumEdit->text().toDouble()); NumEdit->clear(); });

	
    // init
    m_texsvg->load();
    m_texsvg->render(m_tree->to_latex().c_str());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updSvg(QString latex, QByteArray svg)
{
    SvgW->load(svg);
    SvgW->resize(SvgW->sizeHint()/30);
    SvgW->show();
    
}

void MainWindow::loadSvg()
{
    //m_texsvg->load();
    m_texsvg->render(m_tree->to_latex().c_str());
}


