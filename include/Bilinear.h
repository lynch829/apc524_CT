#ifndef __BILINEAR
#define __BILINEAR 1
#include"Interpolator.h"
#include <vector>

/*!
    Interpolate a function using nearest neighbour method.
*/


class Bilinear : public Interpolator {
public:
    Bilinear ();
    ~Bilinear ();
    double Interpolate(double x, double y);
    double Interpolate(double x, double y, double z);
		//!< Implements the virtual method of class Interpolator.
};

#endif /* defined(BILINEAR) */
