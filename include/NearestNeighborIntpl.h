#ifndef __NNI
#define __NNI 1
#include"Interpolator.h"
#include <vector>

/*!
    Interpolate a function using nearest neighbour method.
*/

//class NumSurface;
//class NumVolume;
class NearestNeighborIntpl : public Interpolator {
public:
    NearestNeighborIntpl ();
    ~NearestNeighborIntpl ();
    double Interpolate(double x, double y, NumSurface* f);
    double Interpolate(double x, double y, double z, NumVolume* f);
std::vector <int> FindDist(int dim,std::vector<int> size,std::vector<double*> coord,std::vector<double> coord_in);   
   //double Interpolate(vector<double>& x, double** data_x, double* fx, int* size, int dim);
	//!< Implements the virtual method of class Interpolator.
};


#endif /* defined(____NearestNeighborIntpl__) */
