#ifndef PARABOLA
#define PARABOLA 1

#include "LineIntegral.h"
#include <functional>

/*!
    Parabola integration.
*/
class Parabola : public LineIntegral {
    
public:
    Parabola();
    ~Parabola();
    double Integrate(std::function<double(double)>, double xmin, double xmax, double step);
	//!< Implements the Integrate method.
};

#endif
