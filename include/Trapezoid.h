#ifndef TRAPEZOID
#define TRAPEZOID 1

#include"Integral.h"

class Trapezoid : public Integral {

public:
    Trapezoid(int n);
    ~Trapezoid();
    double Integrate(double (*f)(double) f, double xmin, double xmax, int N);
};

#endif
