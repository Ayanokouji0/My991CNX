#include <stdlib.h>
#include <vector>
#include <string>
class exptree
{
    public:
    enum type
    {
        add,
        sub,
        mul,
        div,
        pow,
        sin,
        cos,
        tan,
        cot,
        sec,
        csc,
        log,
        ln,
        sqrt,
        abs,
        var,
        num
    };
    class node
    {
        public:
        type nodetype;
        virtual double eval(double x) = 0;
        std::vector<node> children;
        virtual std::string to_latex(node *selected) = 0;
        
    };
    class variable : public node
    {
        public:
        variable();
        virtual double eval(double x);
        virtual std::string to_latex(node *selected);

    };
    class number : public node
    {
        public:

        double val;
        number(double _val);
        virtual double eval(double x);
        virtual std::string to_latex(node *selected);

    };
    class oper : public node
    {
        public:
        oper(type _t);
        virtual double eval(double x);
        virtual std::string to_latex(node *selected);

    };
    node *root;
    exptree(node &_root);
    exptree(double val);
    double eval(double x);
    
    std::string to_latex(node *selected);
};

