#include "dialog_intro.h"
#include "ui_dialog_intro.h"

Dialog_intro::Dialog_intro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_intro)
{
    ui->setupUi(this);
    ui->label->setText("这是一款计算器软件，可以点击左箭头和右箭头来调整红框的位置，即新输入的位置，然后在输入框中输入数字，\n"
                       "在下方按键处点击输入操作符。同时这款软件也可以实现简单函数图像的绘制。");
}

Dialog_intro::~Dialog_intro()
{
    delete ui;
}
