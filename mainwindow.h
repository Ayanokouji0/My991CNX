#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QSvgWidget>
#include "TexSvg.h"
#include "exptree.h"

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
    exptree m_tree = exptree(0);


public slots:
//    void loadSvg(bool isLoaded);
    void updSvg(QString latex, QByteArray svg);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
