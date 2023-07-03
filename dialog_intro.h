#ifndef DIALOG_INTRO_H
#define DIALOG_INTRO_H

#include <QDialog>

namespace Ui {
class Dialog_intro;
}

class Dialog_intro : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_intro(QWidget *parent = nullptr);
    ~Dialog_intro();

private:
    Ui::Dialog_intro *ui;
};

#endif // DIALOG_INTRO_H
