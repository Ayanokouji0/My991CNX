
#include "mainwindow_.h"

#include <QApplication>
#include<QPushButton>
#include <QLocale>
#include <QTranslator>
#include"plot.h"
double func(double x) {
    return sin(x);
}//一个函数示例
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "demo5_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    Plot plt(&w);
    plt.makeplot(func,w,false);
    w.show();
    return a.exec();
}
