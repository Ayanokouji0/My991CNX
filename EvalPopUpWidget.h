#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "ui_EvalPopUpWidget.h"

class EvalPopUpWidget : public QWidget
{
	Q_OBJECT

public:
	EvalPopUpWidget(QWidget *parent = nullptr);
	~EvalPopUpWidget();

private:
	Ui::EvalPopUpWidget ui;
	QLineEdit *NumEdit;
	QPushButton *EvalPshBtn;

signals:
	void EvalSignal(double x);
private slots:
	void open_window();
};
