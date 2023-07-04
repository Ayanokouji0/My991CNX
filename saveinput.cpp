#include "mainwindow.h"
#include "saveinput.h"
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <cstring>
#include <QtWidgets>
#include <cmath>
#include <QPushButton>

SaveInput::SaveInput(QWidget *parent) : QDialog(parent)
{
    QFormLayout *my_layout = new QFormLayout(this);
    for (int i = 0; i < 3; ++i)
    {
        QLabel *my_label = new QLabel(QString(QChar('A'+i)).arg(i), this);
        QLineEdit *my_line = new QLineEdit(this);
        my_line->setText("0");
        my_layout->addRow(my_label, my_line);
        fields << my_line;
    }
    QDialogButtonBox *buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this );
    my_layout->addWidget(buttonBox);

    bool con = connect(buttonBox, &QDialogButtonBox::accepted, this, &SaveInput::accept);
    Q_ASSERT(con);
    con = connect(buttonBox, &QDialogButtonBox::rejected,this, &SaveInput::reject);
    Q_ASSERT(con);
    setLayout(my_layout);
}


QStringList SaveInput::getStrings(QWidget *parent, bool* judge)
{
    SaveInput *dialog = new SaveInput(parent);
    QStringList list;
    const int ret = dialog->exec();
    if (judge)
    {
        *judge = !!ret;
    }
    if (ret)
    {
        foreach(auto field, dialog->fields)
        {
            list << field->text();
        }
    }
    dialog->deleteLater();
    return list;
}
