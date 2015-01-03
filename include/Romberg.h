#ifndef ROMBERG
#define ROMBERG 1

#include "LineIntegral.h"
#include <functional>

class Romberg : public LineIntegral {
public:
    Romberg();
    ~Romberg();
    double Integrate(std::function<double(double)>, double xmin, double xmax, double epsilon);
};

#endif