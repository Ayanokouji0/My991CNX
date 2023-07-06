#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QStringList>


MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->setWindowTitle("Calculator");
	// background picture
	this->setStyleSheet("QMainWindow{border-image: url(:/Assets/Background.png)}");

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
	//LeftPshBtn->setText("<-");
	LeftPshBtn->setFixedSize(90, 50);
	LeftPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/LeftPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->LeftLayout->addWidget(LeftPshBtn);
	connect(LeftPshBtn, &QPushButton::clicked,
		m_tree, &exptree::prev);
    LeftPshBtn->setShortcut(Qt::Key_Left);

	RightPshBtn = new QPushButton(this);
	//RightPshBtn->setText("->");
	RightPshBtn->setFixedSize(90, 50);
	RightPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/RightPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->RightLayout->addWidget(RightPshBtn);
	connect(RightPshBtn, &QPushButton::clicked,
		m_tree, &exptree::next);
    RightPshBtn->setShortcut(Qt::Key_Right);

	FracPshBtn = new QPushButton(this);
	//FracPshBtn->setText("Frac");
	FracPshBtn->setFixedSize(90, 50);
	FracPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/FracPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->FracLayout->addWidget(FracPshBtn);
	connect(FracPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::frc); });

	SqrtPshBtn = new QPushButton(this);
	//SqrtPshBtn->setText("Sqrt");
	SqrtPshBtn->setFixedSize(90, 50);
	SqrtPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/SqrtPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->SqrtLayout->addWidget(SqrtPshBtn);
	connect(SqrtPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::sqrt); });

	PowPshBtn = new QPushButton(this);
	//PowPshBtn->setText("Pow");
	PowPshBtn->setFixedSize(90, 50);
	PowPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/PowPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->PowLayout->addWidget(PowPshBtn);
	connect(PowPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::pow); });
    PowPshBtn->setShortcut(Qt::Key_AsciiCircum); // "^"¼ü

	LogPshBtn = new QPushButton(this);
	//LogPshBtn->setText("Log");
	LogPshBtn->setFixedSize(90, 50);
	LogPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/LogPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->LogLayout->addWidget(LogPshBtn);
	connect(LogPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::log); });

	LnPshBtn = new QPushButton(this);
	//LnPshBtn->setText("Ln");
	LnPshBtn->setFixedSize(90, 50);
	LnPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/LnPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->LnLayout->addWidget(LnPshBtn);
	connect(LnPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::ln); });

	SinPshBtn = new QPushButton(this);
	//SinPshBtn->setText("Sin");
	SinPshBtn->setFixedSize(90, 50);
	SinPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/SinPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->SinLayout->addWidget(SinPshBtn);
	connect(SinPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::sin); });

	CosPshBtn = new QPushButton(this);
	//CosPshBtn->setText("Cos");
	CosPshBtn->setFixedSize(90, 50);
	CosPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/CosPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->CosLayout->addWidget(CosPshBtn);
	connect(CosPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::cos); });

	TanPshBtn = new QPushButton(this);
	//TanPshBtn->setText("Tan");
	TanPshBtn->setFixedSize(90, 50);
	TanPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/TanPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->TanLayout->addWidget(TanPshBtn);
	connect(TanPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::tan); });

	CscPshBtn = new QPushButton(this);
	//CscPshBtn->setText("Csc");
	CscPshBtn->setFixedSize(90, 50);
	CscPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/CscPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->CscLayout->addWidget(CscPshBtn);
	connect(CscPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::csc); });

	SecPshBtn = new QPushButton(this);
	//SecPshBtn->setText("Sec");
	SecPshBtn->setFixedSize(90, 50);
	SecPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/SecPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->SecLayout->addWidget(SecPshBtn);
	connect(SecPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::sec); });

	CotPshBtn = new QPushButton(this);
	//CotPshBtn->setText("Cot");
	CotPshBtn->setFixedSize(90, 50);
	CotPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/CotPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->CotLayout->addWidget(CotPshBtn);
	connect(CotPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::cot); });

	AddPshBtn = new QPushButton(this);
	//AddPshBtn->setText("+");
	AddPshBtn->setFixedSize(90, 50);
	AddPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/AddPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->AddLayout->addWidget(AddPshBtn);
	connect(AddPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::add); });
    AddPshBtn->setShortcut(Qt::Key_Plus);

	SubPshBtn = new QPushButton(this);
	//SubPshBtn->setText("-");
	SubPshBtn->setFixedSize(90, 50);
	SubPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/SubPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->SubLayout->addWidget(SubPshBtn);
	connect(SubPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::sub); });
    SubPshBtn->setShortcut(Qt::Key_Minus);

	MulPshBtn = new QPushButton(this);
	//MulPshBtn->setText("*");
	MulPshBtn->setFixedSize(90, 50);
	MulPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/MulPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->MulLayout->addWidget(MulPshBtn);
	connect(MulPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::mul); });
    MulPshBtn->setShortcut(Qt::Key_Asterisk);

	DivPshBtn = new QPushButton(this);
	//DivPshBtn->setText("/");
	DivPshBtn->setFixedSize(90, 50);
	DivPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/DivPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->DivLayout->addWidget(DivPshBtn);
	connect(DivPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::div); });
    DivPshBtn->setShortcut(Qt::Key_Slash);

	AbsPshBtn = new QPushButton(this);
	//AbsPshBtn->setText("Abs");
	AbsPshBtn->setFixedSize(90, 50);
	AbsPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/AbsPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->AbsLayout->addWidget(AbsPshBtn);
	connect(AbsPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::abs); });

	IntPshBtn = new QPushButton(this);
	//IntPshBtn->setText("Int");
	IntPshBtn->setFixedSize(90, 50);
	IntPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/IntPshBtn.png); border: none}"
			"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->IntLayout->addWidget(IntPshBtn);
	connect(IntPshBtn, &QPushButton::clicked,
		m_tree, [=]() {m_tree->add_oper(exptree::intg); });

	ACPshBtn = new QPushButton(this);
	//ACPshBtn->setText("AC");
	ACPshBtn->setFixedSize(90, 50);
	ACPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/ACPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->ACLayout->addWidget(ACPshBtn);
	connect(ACPshBtn, &QPushButton::clicked,
		m_tree, &exptree::all_clear);
    ACPshBtn->setShortcut(Qt::Key_Delete);

	DelPshBtn = new QPushButton(this);
	//DelPshBtn->setText("Del");
	DelPshBtn->setFixedSize(90, 50);
	DelPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/DelPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->DelLayout->addWidget(DelPshBtn);
	connect(DelPshBtn, &QPushButton::clicked,
		m_tree, &exptree::del);
    DelPshBtn->setShortcut(Qt::Key_Backspace);

	VarPshBtn = new QPushButton(this);
	//VarPshBtn->setText("X");
	VarPshBtn->setFixedSize(90, 50);
	VarPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/VarPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->VarLayout->addWidget(VarPshBtn);
	connect(VarPshBtn, &QPushButton::clicked,
		m_tree, &exptree::add_var);

	EvalPshBtn = new QPushButton(this);
	//EvalPshBtn->setText("=");
	EvalPshBtn->setFixedSize(90, 50);
	EvalPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/EvalPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->EvalLayout->addWidget(EvalPshBtn);
	connect(EvalPshBtn, &QPushButton::clicked,
		m_tree, &exptree::slot_eval);
    EvalPshBtn->setShortcut(Qt::Key_Space);

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
	//PltPshBtn->setText("Plot");
	PltPshBtn->setFixedSize(90, 50);
	PltPshBtn->setStyleSheet("QPushButton{image: url(:/Assets/PltPshBtn.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
	ui->PltLayout->addWidget(PltPshBtn);
	connect(PltPshBtn, &QPushButton::clicked,
		plt, [=]() {
			plt->makeplot(m_tree, *pltw, false);
		});
    PltPshBtn->setShortcut(Qt::Key_P);

	// line edit
	NumEdit = new QLineEdit(this);
	ui->InputLayout->addWidget(NumEdit);
	NumEdit->setFixedSize(250, 50);
	NumEdit->setTextMargins(25, 0, 10, 0);
	NumEdit->setStyleSheet("QLineEdit{border-image: url(:/Assets/LineEdit.png);"
		"font-size: 20px; color: rgb(24, 37, 48);"
		"font-weight: bold;}");
	//NumEdit->setAlignment(Qt::AlignRight);
	NumEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$")));
    connect(NumEdit, &QLineEdit::returnPressed,
            m_tree, [=]() {m_tree->add_number(NumEdit->text().toDouble()); NumEdit->clear(); NumEdit->clearFocus();});



	ui->HistorypushButton->setFixedSize(90, 50);
	ui->HistorypushButton->setText("");
	ui->HistorypushButton->setStyleSheet("QPushButton{image: url(:/Assets/HistorypushButton.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");

	ui->AnspushButton->setFixedSize(90, 50);
	ui->AnspushButton->setText("");
	ui->AnspushButton->setStyleSheet("QPushButton{image: url(:/Assets/AnspushButton.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");

	ui->ApushButton->setFixedSize(90, 50);
	ui->ApushButton->setText("");
	ui->ApushButton->setStyleSheet("QPushButton{image: url(:/Assets/ApushButton.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
    ui->ApushButton->setShortcut(Qt::Key_A);

	ui->BpushButton->setFixedSize(90, 50);
	ui->BpushButton->setText("");
	ui->BpushButton->setStyleSheet("QPushButton{image: url(:/Assets/BpushButton.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
    ui->BpushButton->setShortcut(Qt::Key_B);

	ui->CpushButton->setFixedSize(90, 50);
	ui->CpushButton->setText("");
	ui->CpushButton->setStyleSheet("QPushButton{image: url(:/Assets/CpushButton.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
    ui->CpushButton->setShortcut(Qt::Key_C);

	ui->SavepushButton->setFixedSize(90, 50);
	ui->SavepushButton->setText("");
	ui->SavepushButton->setStyleSheet("QPushButton{image: url(:/Assets/SavepushButton.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
    ui->SavepushButton->setShortcut(Qt::Key_S);

	ui->intro_pushButton->setFixedSize(90, 50);
	ui->intro_pushButton->setText("");
	ui->intro_pushButton->setStyleSheet("QPushButton{image: url(:/Assets/intro_pushButton.png); border: none}"
		"QPushButton:pressed{image: url(:/Assets/BtnPressed.png); border: none}");
    ui->intro_pushButton->setShortcut(Qt::Key_I);

	// init
	m_texsvg->load();
	m_texsvg->render(m_tree->to_latex().c_str());

	// history and memory
//    HistoryPshBtn = new QPushButton(this);
//    HistoryPshBtn->setText("History");
//    ui->HistoryLayout->addWidget(HistoryPshBtn);
//    connect(HistoryPshBtn, &QPushButton::clicked,
//            hist_mem,
//            [=]() {hist_mem->show_history();});

	QPalette winpalette;
	//ÉèÖÃÖ÷´°¿Ú±³¾°ÑÕÉ«
	winpalette.setColor(QPalette::Window, QColor(225, 225, 225));
	this->setPalette(winpalette);

	//QPalette svgpalette;
	////ÉèÖÃsvg´°¿Ú±³¾°ÑÕÉ«
	//svgpalette.setColor(QPalette::Window, QColor(255, 255, 255));
	//SvgW->setPalette(svgpalette);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::updSvg(QString latex, QByteArray svg)
{
	SvgW->load(svg);
	SvgW->resize(SvgW->sizeHint() / 30);
	SvgW->show();

}

void MainWindow::loadSvg()
{
	//m_texsvg->load();
	m_texsvg->render(m_tree->to_latex().c_str());
}

void MainWindow::on_intro_pushButton_clicked()
{
	Dialog_intro* IntroWindow = new Dialog_intro;
	IntroWindow->show();
}

void MainWindow::on_HistorypushButton_clicked()
{
	m_tree->hist_mem->show_history();
}


void MainWindow::on_ApushButton_clicked()
{
	m_tree->add_number(m_tree->hist_mem->return_a());
}


void MainWindow::on_BpushButton_clicked()
{
	m_tree->add_number(m_tree->hist_mem->return_b());
}


void MainWindow::on_CpushButton_clicked()
{
	m_tree->add_number(m_tree->hist_mem->return_c());
}


void MainWindow::on_AnspushButton_clicked()
{
	double ans = m_tree->hist_mem->get_ans();
	m_tree->add_number(ans);
}


void MainWindow::on_SavepushButton_clicked()
{
	QStringList list = SaveInput::getStrings(this);
	if (!list.empty()) {
		QString sa = list[0];
		m_tree->hist_mem->set_a(sa.toDouble());
		QString sb = list[1];
		m_tree->hist_mem->set_b(sb.toDouble());
		QString sc = list[2];
		m_tree->hist_mem->set_c(sc.toDouble());
	}
}

