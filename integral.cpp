// Romberg Integral
#include "exptree.h"
#include <vector>
#include <cmath> 
double integral(exptree::node *tree, double a, double b, double e0)
{
    auto func = [=](double x) -> double
    {
		return tree->eval(x);
	};
    // init data
    std::vector<double> t0, t_last, t_cur;
    double h = (b - a)/2;
    t0.push_back(h * (func(a) + func(b)));
    t_last = t0;
    double e = 1;
    int cnt = 0;
    while ((e >= e0 || cnt <= 5) && cnt < 15)
    {
        double f = 0;
        for (unsigned long long i = 1; (a+(2*i-1)*h) < b; i++)
        {
            f += func(a+(2*i-1)*h);
        }
        t_cur.push_back(t0.back()/2 + f*h);
        for (unsigned long long i = 1; i <= t_last.size(); i++)
        {
            int p4i = pow(4, i);
            double t = (p4i*t_cur[0] - t_last[t_last.size() - i]) / (p4i - 1);
            t_cur.insert(t_cur.begin(), t);
        }
        t0.push_back(t_cur[0]);
        e = abs(t_last[0] - t_cur[0]);
        t_last = t_cur;
        t_cur.clear();
        h /= 2;
        cnt++;
    }
    return t0.back();
}
