#include <exptree.h>
#include <cmath>
exptree::number::number(double _val):val(_val)
{
    nodetype = num;
};
double exptree::number::eval(double x)
{
    return val;
}

exptree::variable::variable()
{
    nodetype = var;
};
double exptree::variable::eval(double x)
{
    return x;
}

exptree::oper::oper(type _t)
{
    nodetype = _t;
}
double exptree::oper::eval(double x)
{
    switch (nodetype)
    {
    case add:
        return children[0].eval(x) + children[1].eval(x);
    case sub:
        return children[0].eval(x) - children[1].eval(x);
    case mul:
        return children[0].eval(x) * children[1].eval(x);
    case div:
        return children[0].eval(x) / children[1].eval(x);
    case pow:
        return std::pow(children[0].eval(x), children[1].eval(x));
    case sin:
        return std::sin(children[0].eval(x));
    case cos:
        return std::cos(children[0].eval(x));
    case tan:
        return std::tan(children[0].eval(x));
    case cot:
        return 1.0 / std::tan(children[0].eval(x));
    case sec:
        return 1.0 / std::cos(children[0].eval(x));
    case csc:
        return 1.0 / std::sin(children[0].eval(x));
    case log:
        return std::log(children[0].eval(x)) / std::log(children[1].eval(x));
    case ln:
        return std::log(children[0].eval(x));
    case sqrt:
        return std::sqrt(children[0].eval(x));
    case abs:
        return std::abs(children[0].eval(x));

    default:
        break;
    }
}

exptree::exptree(node &&_root):root(_root){};
exptree::exptree(double val):root(number(val)){};
double exptree::eval(double x)
{
    return root.eval(x);
}