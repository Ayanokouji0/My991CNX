
#include "history_memory.h"

History_memory::History_memory():my_vector(0),len(0),memory_a(0),memory_b(0),memory_c(0),memory_ans(0)
{

}

double History_memory::get_last_result() {
    if(len!=0)
        return my_vector[len-1];
    return 0;
}

void History_memory::set_a(double a) {
    memory_a = a;
}

void History_memory::set_b(double b) {
    memory_b = b;
}

void History_memory::set_c(double c) {
    memory_c = c;
}

double History_memory::return_a() {
    return memory_a;
}

double History_memory::return_b() {
    return memory_b;
}

double History_memory::return_c() {
    return memory_c;
}

void History_memory::set_ans() {
    memory_ans = History_memory::get_last_result();
}

double History_memory::get_ans() {
    History_memory::set_ans();
    return memory_ans;
}

void History_memory::push_new_ans(double a) {

    my_vector.push_back(a);
    len++;
}

void History_memory::show_history() {
    QTextEdit* history_list = new QTextEdit(nullptr);
    history_list->setWindowTitle("History");
    for(int i=len-1 ; i>=0 && i>=len-10 ; --i) {
        double temp = my_vector[i];
        history_list->append(QString::number(temp,'f',8));
    }
    history_list->setStyleSheet("font: bold; font-size: 14px;");
    history_list->setReadOnly(true);
    history_list->show();
    //emit changed();
}
