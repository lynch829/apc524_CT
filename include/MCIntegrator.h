#ifndef MCINT
#define MCINT 1

#include"MCIntegrator.h"
#include"LineIntegral.h"
#include<functional>

class MCIntegrator : public LineIntegral {

public:
    MCIntegrator();
    ~MCIntegrator();
    double Integrate(std::function<double(double)>, double xmin, double xmax, int N);
};

#endif
