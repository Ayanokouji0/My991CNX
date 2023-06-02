#include "exptree.h"
#include <cstdio>
int main()
{
    // test
    exptree::number n(1);
    exptree::variable v;
    exptree::oper o(exptree::add);
    o.children.push_back(n);
    o.children.push_back(v);
    printf("%f\n", o.eval(2));
    printf("%s\n", o.to_latex(nullptr).c_str());
}