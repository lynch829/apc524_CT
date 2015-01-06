#ifndef TRAPEZOID
#define TRAPEZOID 1

#include"LineIntegral.h"
#include<functional>
/*!
    Trapezoid integration class.
*/
class Trapezoid : public LineIntegral {

public:
    Trapezoid();
    ~Trapezoid();
    double Integrate(std::function<double(double)>, double xmin, double xmax, double step);
	//!< Implements LineIntegral::Integrate method.
};

#endif
