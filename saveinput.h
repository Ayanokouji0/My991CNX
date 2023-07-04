
#ifndef SAVEINPUT_H
#define SAVEINPUT_H
#include <QDialog>
#include <QList>
#include <QLineEdit>
#include <QWidget>
#include <QString>
#include <QStringList>


class SaveInput: public QDialog
{
    Q_OBJECT
public:
    SaveInput();
public:
    explicit SaveInput(QWidget *parent = nullptr);
    static QStringList getStrings(QWidget *parent, bool *ok = nullptr);
private:
    QList<QLineEdit*> fields;
};

#endif // SAVEINPUT_H
