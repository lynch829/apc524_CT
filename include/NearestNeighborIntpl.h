#ifndef __NNI
#define __NNI 1
#include"Interpolator.h"
#include <vector>

/*!
    Interpolate a function using nearest neighbour method.
*/


class NearestNeighborIntpl : public Interpolator {
public:
    NearestNeighborIntpl ();
    ~NearestNeighborIntpl ();
    double Interpolate(double x, double y);
		//!< Interpolation for 2D.
    double Interpolate(double x, double y, double z);
		//!< Interpolation for 3D.
};
#endif /* defined(____NearestNeighborIntpl__) */
