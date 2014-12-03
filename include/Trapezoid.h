#ifndef TRAPEZOID
#define TRAPEZOID 1

#include"LineIntegral.h"
#include<functional>

class Trapezoid : public LineIntegral {

public:
    Trapezoid();
    ~Trapezoid();
    double Integrate(std::function<double(double)>, double xmin, double xmax, int N);
};

#endif
