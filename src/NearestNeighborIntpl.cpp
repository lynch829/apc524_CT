#include "NearestNeighborIntpl.h"
#include <math.h>
#include <vector>
NearestNeighborIntpl::NearestNeighborIntpl() {}

NearestNeighborIntpl::~NearestNeighborIntpl() {}

double NearestNeighborIntpl::Interpolate(double x, double y){
const int dim = 2;
vector <double*> coord; coord.resize(dim); coord[0] = _xptr; coord[1] = _yptr; //set the vector of dimension 2 for the coord.
vector <int> size; size.resize(dim); size[0] = _sizex; size[1] = _sizey; //set the vector of dimension 2 for the size information.
vector <double> coord_in; coord_in.resize(dim); coord_in[0] = x; coord_in[1] = y; 
vector <int> coord_out; coord_out.resize(dim);
coord_out = this->FindDist(dim,size,coord,coord_in);
double ret = _vptr[coord_out[0]][coord_out[1]];
return ret;
}
double NearestNeighborIntpl::Interpolate(double x, double y, double z){
const int dim = 3;
vector <int> nearest; nearest.resize(dim); //set the vector of dimension 2 for the nearest points.
vector <double*> coord; coord.resize(dim); coord[0] = _xptr; coord[1] = _yptr; coord[2] = _zptr;//set the vector of dimension 3 for the coord.
vector <int> size; size.resize(dim); size[0] = _sizex; size[1] = _sizey; size[2] = _sizez;//set the vector of dimension 3 for the size information.
vector <double> coord_in; coord_in.resize(dim); coord_in[0] = x; coord_in[1] = y; coord_in[3] = z;

vector <int> coord_out; coord_out.resize(dim);
coord_out = this->FindDist(dim,size,coord,coord_in);
double ret = _wptr[coord_out[0]][coord_out[1]][coord_out[2]];
return ret;
}

vector <int> NearestNeighborIntpl::FindDist(int dim, vector<int> size, vector<double*> coord, vector<double> coord_in){
vector<int> nearest; nearest.resize(dim);
for (int d=0; d<dim;d++){
    double minDist = 1e10;
    for (int i=0; i<size[d];i++){
        double dist = fabs((coord[d])[i]-coord_in[d]);
        if (dist<minDist) {
           minDist = dist;
           nearest[d] = i;
        }
    }
}
return nearest;
}
