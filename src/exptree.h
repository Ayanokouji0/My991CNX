#include <vector>
class exptree
{
    public:
    typedef enum type
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
        virtual double eval(double x);
        std::vector<node> children;
    };
    class variable : public node
    {
        variable();
        virtual double eval(double x);
    };
    class number : public node
    {
        double val;
        number(double _val):val(_val){};
        virtual double eval(double x);
    };
    class oper : public node
    {

        oper(type _t);
        virtual double eval(double x);
    };
    node root;

    exptree(node &&_root);
};