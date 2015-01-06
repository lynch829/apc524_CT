#ifndef ROMBERG
#define ROMBERG 1

#include "LineIntegral.h"
#include <functional>
/*!
    Romberg integration method.
*/
class Romberg : public LineIntegral {
public:
    Romberg();
    ~Romberg();
    double Integrate(std::function<double(double)>, double xmin, double xmax, double epsilon);
	//!< Implements Integrate method from LineIntegral class.
};

#endif
