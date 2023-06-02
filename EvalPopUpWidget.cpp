#include "EvalPopUpWidget.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "mainwindow.h"
#include <QGridLayout>


EvalPopUpWidget::EvalPopUpWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	NumEdit = new QLineEdit(this);
	EvalPshBtn = new QPushButton(this);
	EvalPshBtn->setText("Evaluate");
	ui.gridLayout->addWidget(EvalPshBtn, 1, 0, 1, 2);
	ui.gridLayout->addWidget(NumEdit, 0, 0, 1, 2);
	QRegularExpression re("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?");
	QRegularExpressionValidator *validator = new QRegularExpressionValidator(re, this);
	NumEdit->setValidator(validator);
	connect(EvalPshBtn, &QPushButton::clicked,
				this, [=]() {emit EvalSignal(NumEdit->text().toDouble()); });

}

EvalPopUpWidget::~EvalPopUpWidget()
{
	
}

void EvalPopUpWidget::open_window()
{
	show();
}