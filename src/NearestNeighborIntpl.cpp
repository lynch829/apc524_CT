#include "NearestNeighborIntpl.h"
#include <math.h>

NearestNeighborIntpl::NearestNeighborIntpl() {}

NearestNeighborIntpl::~NearestNeighborIntpl() {}

double NearestNeighborIntpl::Interpolate(double x, double y, NumSurface& f){
return 0;
}
double NearestNeighborIntpl::Interpolate(double x, double y, double z, NumVolume& f){
return 0;
}

//double NearestNeighborIntpl::Interpolate(vector<double>& x, double** data_x, double* fx, int* size, int dim){    int* nearest = new int [dim];
//    for (int d=0; d<dim; ++d) {
//        double minDist=1e10;
        
//        for (int i=0; i<size[d]; ++i) {
//            double dist = fabs(data_x[d][i] - x[d]);
//            if (dist<minDist) {
//                minDist = dist;
//                nearest[d] = i;
//            }
//        }
//    }
//    double value = fx[coord2index(nearest,size,dim)];
//    delete [] nearest;
//    return value;
//}
