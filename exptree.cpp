#include "exptree.h"
#include <cmath>
#include <algorithm>
#include <sstream>
exptree::number::number(double _val, node* _parent)
{
    parent = _parent;
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
        std::stringstream ss;
        ss << val;
        std::string s = ss.str();
        return "\\color{red}{" + s + "}";
    }
    else
    {
        std::stringstream ss;
        ss << val;
        std::string s = ss.str();
        return s;
    }
}

exptree::variable::variable(node* _parent)
{
    parent = _parent;
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

exptree::oper::oper(type _t, node* _parent)
{
    parent = _parent;
    nodetype = _t;
    switch (nodetype)
    {
    case exptree::add:
    case exptree::sub:
    case exptree::mul:
    case exptree::div:
    case exptree::frc:
    case exptree::pow:
    case exptree::log:
        children.push_back(new blank(this));
        children.push_back(new blank(this));
        break;
    case exptree::sin:
    case exptree::cos:
    case exptree::tan:
    case exptree::cot:
    case exptree::sec:
    case exptree::csc:
    case exptree::ln:
    case exptree::sqrt:
    case exptree::abs:
        children.push_back(new blank(this));
        break;
    default:
        break;
    }
}
double exptree::oper::eval(double x)
{
    switch (nodetype)
    {
    case add:
        return children[0]->eval(x) + children[1]->eval(x);
    case sub:
        return children[0]->eval(x) - children[1]->eval(x);
    case mul:
        return children[0]->eval(x) * children[1]->eval(x);
    case div:
        return children[0]->eval(x) / children[1]->eval(x);
    case frc:
        return children[0]->eval(x) / children[1]->eval(x);
    case pow:
        return std::pow(children[0]->eval(x), children[1]->eval(x));
    case sin:
        return std::sin(children[0]->eval(x));
    case cos:
        return std::cos(children[0]->eval(x));
    case tan:
        return std::tan(children[0]->eval(x));
    case cot:
        return 1.0 / std::tan(children[0]->eval(x));
    case sec:
        return 1.0 / std::cos(children[0]->eval(x));
    case csc:
        return 1.0 / std::sin(children[0]->eval(x));
    case log:
        return std::log(children[0]->eval(x)) / std::log(children[1]->eval(x));
    case ln:
        return std::log(children[0]->eval(x));
    case sqrt:
        return std::sqrt(children[0]->eval(x));
    case abs:
        return std::abs(children[0]->eval(x));

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
        ret = "(" + children[0]->to_latex(selected) + "+" + children[1]->to_latex(selected) + ")";
        break;
    case sub:
        ret = "(" + children[0]->to_latex(selected) + "-" + children[1]->to_latex(selected) + ")";
        break;
    case mul:
        ret = "(" + children[0]->to_latex(selected) + "\\times " + children[1]->to_latex(selected) + ")";
        break;
    case div:
        ret = "(" + children[0]->to_latex(selected) + "\\div " + children[1]->to_latex(selected) + ")";
        break;
    case frc:
        ret = "\\frac{" + children[0]->to_latex(selected) + "}{" + children[1]->to_latex(selected) + "}";
        break;
    case pow:
        ret = "{" + children[0]->to_latex(selected) + "}^{" + children[1]->to_latex(selected) + "}";
        break;
    case sin:
        ret = "\\sin{" + children[0]->to_latex(selected) + "}";
        break;
    case cos:
        ret = "\\cos{" + children[0]->to_latex(selected) + "}";
        break;
    case tan:
        ret = "\\tan{" + children[0]->to_latex(selected) + "}";
        break;
    case cot:
        ret = "\\cot{" + children[0]->to_latex(selected) + "}";
        break;
    case sec:
        ret = "\\sec{" + children[0]->to_latex(selected) + "}";
        break;
    case csc:
        ret = "\\csc{" + children[0]->to_latex(selected) + "}";
        break;
    case log:
        ret = "\\log_{" + children[1]->to_latex(selected) + "}{" + children[0]->to_latex(selected) + "}";
        break;
    case ln:
        ret = "\\ln{" + children[0]->to_latex(selected) + "}";
        break;
    case sqrt:
        ret = "\\sqrt{" + children[0]->to_latex(selected) + "}";
        break;
    case abs:
        ret = "\\left|" + children[0]->to_latex(selected) + "\\right|";
        break;

    default:
        break;
    }
    if (selected == this)
    {
        ret = "\\color{red}{" + ret + "}";
    }
    return ret;
}

exptree::blank::blank(node* _parent)
{
    parent = _parent;
    nodetype = blk;
};
double exptree::blank::eval(double x)
{
    emit qDebug("Trying to evaluate a blank node");
    return -1;
}
std::string exptree::blank::to_latex(node* selected)
{
    std::string s = "\\Box";
    if (selected == this)
    {
        return "\\color{red}{" + s + "}";
    }
    else
    {
        return s;
    }
}

exptree::exptree(node &_root):root(&_root), selected(nullptr),hist_mem(new History_memory()){};
exptree::exptree(double val):root(new number(val)), selected(nullptr),hist_mem(new History_memory()){};
double exptree::eval(double x)
{
    return root->eval(x);
}

std::string exptree::to_latex(node *_selected)
{
    return root->to_latex(_selected);
}  
std::string exptree::to_latex()
{
    return root->to_latex(selected);
}

void exptree::next()
{
    if (selected == nullptr)
    {
        selected = root;
        emit changed();
        return;
    }
    else if (selected->nodetype != num && selected->nodetype != var && selected->nodetype != blk)
    {
        selected = selected->children[0];
        emit changed();
        return;
    }
    else if (selected->parent == nullptr)
    {
		selected = nullptr;
		emit changed();
		return;
	}
    else if (find(selected->parent->children.begin(), selected->parent->children.end(), selected) < selected->parent->children.end() - 1)
    {
        selected = *(find(selected->parent->children.begin(), selected->parent->children.end(), selected) + 1);
		emit changed();
		return;
	}
    else if (selected->parent->children[selected->parent->children.size() - 1] == selected)
    {
		node *p = selected->parent;
        while (p->parent != nullptr && p->parent->children[p->parent->children.size() - 1] == p)
        {
			p = p->parent;
		}
        if (p->parent == nullptr)
        {
			selected = nullptr;
			emit changed();
			return;
		}
        else
        {
			selected = p->parent->children[p->parent->children.size() - 1];
			emit changed();
			return;
		}
	}
    else
    {
		selected = nullptr;
		emit changed();
		return;
	}
    emit changed();
}

void exptree::prev()
{
    if (selected == nullptr)
    {
        selected = root;
        emit changed();
        return;
    }
    else if (selected->parent == nullptr)
    {
        selected = nullptr;
        emit changed();
        return;
    }
    else if (find(selected->parent->children.begin(), selected->parent->children.end(), selected) > selected->parent->children.begin())
    {
		selected = *(find(selected->parent->children.begin(), selected->parent->children.end(), selected) - 1);
		emit changed();
		return;
	}
    else if (selected->parent->children[0] == selected)
    {
		node *p = selected->parent;
        /*while (p->parent != nullptr && p->parent->children[0] == p)
        {
			p = p->parent;
		}
        if (p->parent == nullptr)*/
        {
			//selected = nullptr;
            selected = p;
			emit changed();
			return;
		}
        /*else
        {
			selected = p->parent->children[0];
			emit changed();
			return;
		}*/
	}
    else
    {
		selected = nullptr;
		emit changed();
		return;
	}
    emit changed();
}

void exptree::del()
{
    if (selected != nullptr)
    {
        node *p = selected->parent;
        if (p == nullptr)
        {
            delete selected;
            root = new blank(nullptr);
            selected = root;
        }
        else
        {
			auto iter = find(p->children.begin(), p->children.end(), selected);
			delete selected;
            *iter = selected = new blank(p);
		}
        emit changed();
    }
}

void exptree::add_oper(exptree::type _ty)
{
    if (selected == nullptr)
    {
        return;
    }
	auto p = selected->parent, old = selected;
	if (p == nullptr)
	{
		root = selected = new oper(_ty, nullptr);
	}
	else
	{
		auto iter = find(p->children.begin(), p->children.end(), selected);
		*iter = selected = new oper(_ty, p);
	}
    if (old->nodetype != blk)
    {
        delete selected->children[0];
        selected->children[0] = old;
        old->parent = selected;
    }
    else
    {
        delete old;
    }
	emit changed();
}

void exptree::all_clear()
{
    delete root;
    root = new blank(nullptr);
    selected = root;
    emit changed();
}

void exptree::add_number(double val)
{
    if (selected == nullptr || selected->nodetype != blk)
    {
        return;
    }
	auto p = selected->parent, old = selected;
    if (p == nullptr)
    {
		root = selected = new number(val, nullptr);
	}
    else
    {
		auto iter = find(p->children.begin(), p->children.end(), selected);
		*iter = selected = new number(val, p);
	}
    if (old->nodetype != blk)
    {
		delete selected->children[0];
		selected->children[0] = old;
		old->parent = selected;
	}
    else
    {
		delete old;
	}
	emit changed();
}

void exptree::add_var()
{
    if (selected == nullptr || selected->nodetype != blk)
    {
		return;
	}
	auto p = selected->parent, old = selected;
    if (p == nullptr)
    {
		root = selected = new variable(nullptr);
	}
    else
    {
		auto iter = find(p->children.begin(), p->children.end(), selected);
		*iter = selected = new variable(p);
	}
    if (old->nodetype != blk)
    {
		delete selected->children[0];
		selected->children[0] = old;
		old->parent = selected;
	}
    else
    {
		delete old;
	}
	emit changed();
}

void exptree::slot_eval(double x)
{
    double result = root->eval(x);
    hist_mem->push_new_ans(result);
    delete root;
    root = new number(result, nullptr);
    selected = nullptr;
    emit changed();
}
