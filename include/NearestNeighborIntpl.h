#ifndef __NNI
#define __NNI 1
#include"Interpolator.h"

/*!
    Interpolate a function using nearest neighbour method.
*/

class NearestNeighborIntpl : public Interpolator {
public:
    NearestNeighborIntpl ();
    ~NearestNeighborIntpl ();
    double Interpolate(double x, double y, NumSurface& f);
    double Interpolate(double x, double y, double z, NumVolume& f);
    //double Interpolate(vector<double>& x, double** data_x, double* fx, int* size, int dim);
	//!< Implements the virtual method of class Interpolator.
};


#endif /* defined(____NearestNeighborIntpl__) */
