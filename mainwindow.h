#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QSvgWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "TexSvg.h"
#include "exptree.h"
#include "plot.h"
#include "dialog_intro.h"
#include "ui_dialog_intro.h"
#include "saveinput.h"
//#include "EvalPopUpWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSvgWidget *SvgW;
    TexSVG *m_texsvg;
    exptree *m_tree;
    PlotWindow *pltw;
    Plot *plt;
    QPushButton* LeftPshBtn;
    QPushButton* RightPshBtn;
    QPushButton* FracPshBtn;
    QPushButton* SqrtPshBtn;
    QPushButton* PowPshBtn;
    QPushButton* LogPshBtn;
    QPushButton* LnPshBtn;
    QPushButton* AbsPshBtn;
    QPushButton* SinPshBtn;
    QPushButton* CosPshBtn;
    QPushButton* TanPshBtn;
    QPushButton* SecPshBtn;
    QPushButton* CscPshBtn;
    QPushButton* CotPshBtn;
    QPushButton* MulPshBtn;
    QPushButton* DivPshBtn;
    QPushButton* AddPshBtn;
    QPushButton* SubPshBtn;
    QPushButton* DelPshBtn;
    QPushButton* ACPshBtn;
    QPushButton* EvalPshBtn;
    QPushButton* VarPshBtn;
    QPushButton* EvalXPshBtn;
    QPushButton* PltPshBtn;
    QPushButton* HistoryPshBtn;
    QPushButton* AnsPshBtn;
    QPushButton* APshBtn;
    QPushButton* BPshBtn;
    QPushButton* CPshBtn;
    QLineEdit* NumEdit;

    //EvalPopUpWidget *EvalPopUp;

    void loadSvg();
    void updSvg(QString latex, QByteArray svg);


private slots:
    void on_intro_pushButton_clicked();

    void on_HistorypushButton_clicked();

    void on_ApushButton_clicked();

    void on_BpushButton_clicked();

    void on_CpushButton_clicked();

    void on_AnspushButton_clicked();

    void on_SavepushButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
