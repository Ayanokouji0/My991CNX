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
    QPushButton *LeftPshBtn;
    QPushButton *RightPshBtn;
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
    QPushButton *DelPshBtn;
    QPushButton *ACPshBtn;
    QPushButton *EvalPshBtn;
    QPushButton *VarPshBtn;
    QPushButton *EvalXPshBtn;
    QPushButton *PltPshBtn;
    QLineEdit *NumEdit;

    //EvalPopUpWidget *EvalPopUp;

    void loadSvg();
    void updSvg(QString latex, QByteArray svg);


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
