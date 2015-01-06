#ifndef INTEGRAL
#define INTEGRAL 1

#include <math.h>
#include <functional>
/*!
  LineIntegral base class. It has only one method that performs line integral according to a function f. This function f should be the parameterised function from a class.
*/

class LineIntegral{

public:
    LineIntegral();
    virtual ~LineIntegral();
    virtual double Integrate(std::function< double (double)> , double xmin, double xmax, double N)=0;
	//!< Performs integration from xmin to xmax, with N steps to the function object.
};

#endif
