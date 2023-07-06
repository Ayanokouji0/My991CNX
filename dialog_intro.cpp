#include "dialog_intro.h"
#include "ui_dialog_intro.h"

Dialog_intro::Dialog_intro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_intro)
{
    ui->setupUi(this);
    ui->label->setText("这是一款计算器软件，可以点击左箭头和右箭头来调整红框的位置，即新输入的位置，然后在输入框中输入数字，\n"
                       "按enter键使得输入的数显示在上方的显示框的红框中正式参与运算，然后在下方按键处点击输入操作符\n"
                       "同时这款软件也可以实现简单一元函数图像的绘制，先在显示框中输入用变量x表示的函数表达式，\n按下plot按钮即可完成函数图像的绘制。\n"
                       "键盘快捷键：\n"
                       "加法：+\n"
                       "减法：-\n"
                       "乘法：*\n"
                       "除法：/\n"
                       "乘方：^\n"
                       "介绍：i\n"
                       "存储：s\n"
                       "A：a\n"
                       "B：b\n"
                       "C：c\n"
                       "del：Backspace\n"
                       "AC：Delete\n");
}

Dialog_intro::~Dialog_intro()
{
    delete ui;
}
