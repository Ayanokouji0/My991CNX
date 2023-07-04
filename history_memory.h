
#ifndef HISTORY_MEMORY_H
#define HISTORY_MEMORY_H
#include <queue>
#include <QVector>
#include <QtCore/QObject>
#include <QListView>
#include <QStringListModel>
#include <QTextEdit>

class History_memory: public QObject
{
public:
    History_memory();
    QVector<double> my_vector;
private:
    int len;
    double memory_a, memory_b, memory_c, memory_ans;

public:
    double get_last_result();
    void set_a(double a);
    void set_b(double b);
    void set_c(double c);
    double return_a();
    double return_b();
    double return_c();
    void set_ans();
    double get_ans();
    void push_new_ans(double a);
    void show_history();
public slots:
signals:
    //void changed();
};

#endif // HISTORY_MEMORY_H
