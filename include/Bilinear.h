#ifndef __BL
#define __BL 1
#include"Interpolator.h"

class Bilinear : public Interpolator {
public:
    Bilinear ();
    ~Bilinear ();
    double Interpolate(vector<double>& x, double** data_x, double* fx, int* size, int dim);
};


#endif /* defined(____Bilinear__) */

