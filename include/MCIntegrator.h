#ifndef MCINT
#define MCINT 1

#include"MCIntegrator.h"
#include"LineIntegral.h"
#include<functional>

/*!
    Monte-Carlo integrator. Performs integration using Monte-Carlo sampling.
*/
class MCIntegrator : public LineIntegral {

public:
    MCIntegrator();
    ~MCIntegrator();
    double Integrate(std::function<double(double)>, double xmin, double xmax, double N);
	//!< Performs sampling using Monte-Carlo sampling.
};

#endif
