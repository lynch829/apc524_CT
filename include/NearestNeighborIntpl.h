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
    void set_values(int,int,double*,double*,double**);
    void set_values(int,int,int,double*,double*,double*,double***);
    double Interpolate(double x, double y);
    double Interpolate(double x, double y, double z);
std::vector <int> FindDist(int dim,std::vector<int> size,std::vector<double*> coord,std::vector<double> coord_in);   
   //double Interpolate(vector<double>& x, double** data_x, double* fx, int* size, int dim);
	//!< Implements the virtual method of class Interpolator.
};


#endif /* defined(____NearestNeighborIntpl__) */
