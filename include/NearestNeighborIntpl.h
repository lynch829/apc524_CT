#ifndef __NNI
#define __NNI 1
#include"Interpolator.h"

class NearestNeighborIntpl : public Interpolator {
public:
    NearestNeighborIntpl ();
    ~NearestNeighborIntpl ();
    double Interpolate(vector<double>& x, double** data_x, double* fx, int* size, int dim);
};


#endif /* defined(____NearestNeighborIntpl__) */
