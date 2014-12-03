#ifndef INTEGRAL
#define INTEGRAL 1

#include<math.h>

class Integral{

public:
    Integral();
    virtual ~Integral();
    virtual double Integrate(double (*f)(double) f, double xmin, double xmax, int N)=0;
protected:
    int _dim;
};

#endif INTEGRAL
