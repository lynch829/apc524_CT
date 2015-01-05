#ifndef __BL
#define __BL 1
#include"Interpolator.h"

/*!
    Bilinear Interpolator class that performs bilinear interpolation on the data.
*/

class Bilinear : public Interpolator {
public:
    Bilinear ();
    ~Bilinear ();
    double Interpolate(vector<double>& x, double** data_x, double* fx, int* size, int dim);
	//!< meaning of each variable?
};


#endif /* defined(____Bilinear__) */

