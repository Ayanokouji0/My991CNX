#ifndef EXPTREE_H
#define EXPTREE_H

#include <stdlib.h>
#include <vector>
#include <string>
#include <QtCore/QObject>
#include <history_memory.h>

class exptree : public QObject
{
	Q_OBJECT
public:
	enum type
	{
		add,
		sub,
		mul,
		div,
		frc,
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
		intg,
		var,
		num,
		blk
	};
	class node
	{
	public:
		type nodetype;
		node* parent;
		std::vector<node*> children;
		virtual double eval(double x) = 0;
		virtual double operator()(double x);
		virtual std::string to_latex(node* selected) = 0;
	};
	class variable : public node
	{
	public:
		variable(node* parent = nullptr);
		virtual double eval(double x);
		virtual std::string to_latex(node* selected);

	};
	class number : public node
	{
	public:

		double val;
		number(double _val, node* _parent = nullptr);
		virtual double eval(double x);
		virtual std::string to_latex(node* selected);

	};
	class oper : public node
	{
	public:
		oper(type _t, node* _parent = nullptr);
		virtual double eval(double x);
		virtual std::string to_latex(node* selected);

	};
	class blank : public node
	{
	public:

		double val;
		blank(node* _parent = nullptr);
		virtual double eval(double x);
		virtual std::string to_latex(node* selected);

	};
	node* root;
	node* selected;
	exptree(node& _root);
	exptree(double val);
	double eval(double x);
	std::string to_latex(node* _selected);
	std::string to_latex();
    History_memory* hist_mem;

public slots:
	void next();
	void prev();
	void del();
	void all_clear();
	void add_oper(type t);
	void add_var();
	void add_number(double _val);
	void slot_eval(double x = 0);
signals:
	void changed();

};

#endif // EXPTREE_H
