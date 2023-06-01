#include "exptree.h"
#include <cmath>
exptree::number::number(double _val)
{
    val = _val;
    nodetype = num;
};
double exptree::number::eval(double x)
{
    return val;
}
std::string exptree::number::to_latex(node *selected)
{
    if (selected == this)
    {
        return "\\color{red}{" + std::to_string(val) + "}";
    }
    else
    {
        return std::to_string(val);
    }
}

exptree::variable::variable()
{
    nodetype = var;
};
double exptree::variable::eval(double x)
{
    return x;
}
std::string exptree::variable::to_latex(node *selected)
{
    if (selected == this)
    {
        return "\\color{red}{x}";
    }
    else
    {
        return "x";
    }
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
    return 0;
}
std::string exptree::oper::to_latex(node *selected)
{
    std::string ret;
    switch (nodetype)
    {
    case add:
        ret = children[0].to_latex(selected) + "+" + children[1].to_latex(selected);
        break;
    case sub:
        ret = children[0].to_latex(selected) + "-" + children[1].to_latex(selected);
        break;
    case mul:
        ret = children[0].to_latex(selected) + "\\cdot " + children[1].to_latex(selected);
        break;
    case div:
        ret = "\\frac{" + children[0].to_latex(selected) + "}{" + children[1].to_latex(selected) + "}";
        break;
    case pow:
        ret = "{" + children[0].to_latex(selected) + "}^{" + children[1].to_latex(selected) + "}";
        break;
    case sin:
        ret = "\\sin{" + children[0].to_latex(selected) + "}";
        break;
    case cos:
        ret = "\\cos{" + children[0].to_latex(selected) + "}";
        break;
    case tan:
        ret = "\\tan{" + children[0].to_latex(selected) + "}";
        break;
    case cot:
        ret = "\\cot{" + children[0].to_latex(selected) + "}";
        break;
    case sec:
        ret = "\\sec{" + children[0].to_latex(selected) + "}";
        break;
    case csc:
        ret = "\\csc{" + children[0].to_latex(selected) + "}";
        break;
    case log:
        ret = "\\log_{" + children[1].to_latex(selected) + "}{" + children[0].to_latex(selected) + "}";
        break;
    case ln:
        ret = "\\ln{" + children[0].to_latex(selected) + "}";
        break;
    case sqrt:
        ret = "\\sqrt{" + children[0].to_latex(selected) + "}";
        break;
    case abs:
        ret = "\\left|" + children[0].to_latex(selected) + "\\right|";
        break;

    default:
        break;
    }
    return ret;
}

exptree::exptree(node &_root):root(&_root){};
exptree::exptree(double val):root(new number(val)){};
double exptree::eval(double x)
{
    return root->eval(x);
}

std::string exptree::to_latex(node *selected)
{
    return root->to_latex(selected);
}  
