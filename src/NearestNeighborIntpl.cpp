#include "NearestNeighborIntpl.h"
#include <math.h>
#include <vector>
NearestNeighborIntpl::NearestNeighborIntpl() {}

NearestNeighborIntpl::~NearestNeighborIntpl() {}

double NearestNeighborIntpl::Interpolate(double x, double y, NumSurface* f){
const int dim = 2;
double* xptr = f->GetXPtr();
double* yptr = f->GetYPtr();
double** zptr = f->GetZPtr();
int sizex = f->GetSizeX();
int sizey = f->GetSizeY();
vector <double*> coord; coord.resize(dim); coord[0] = xptr; coord[1] = yptr; //set the vector of dimension 2 for the coord.
vector <int> size; size.resize(dim); size[0] = sizex; size[1] = sizey; //set the vector of dimension 2 for the size information.
vector <double> coord_in; size.resize(dim); coord_in[0] = x; coord_in[1] = y; 
vector <int> coord_out; coord_out.resize(dim);
coord_out = this->FindDist(dim,size,coord,coord_in);

double ret = zptr[coord_out[0]][coord_out[1]];
return ret;
}
double NearestNeighborIntpl::Interpolate(double x, double y, double z, NumVolume* f){
const int dim = 3;
vector <int> nearest; nearest.resize(dim); //set the vector of dimension 2 for the nearest points.
double* xptr = f->GetXPtr();
double* yptr = f->GetYPtr();
double* zptr = f->GetZPtr();
double*** wptr = f->GetWPtr();
int sizex = f->GetSizeX();
int sizey = f->GetSizeY();
int sizez = f->GetSizeZ();

vector <double*> coord; coord.resize(dim); coord[0] = xptr; coord[1] = yptr; coord[2] = zptr;//set the vector of dimension 3 for the coord.
vector <int> size; size.resize(dim); size[0] = sizex; size[1] = sizey; size[2] = sizez;//set the vector of dimension 3 for the size information.
vector <double> coord_in; size.resize(dim); coord_in[0] = x; coord_in[1] = y; coord_in[3] = z;

vector <int> coord_out; coord_out.resize(dim);
coord_out = this->FindDist(dim,size,coord,coord_in);
double ret = wptr[coord_out[0]][coord_out[1]][coord_out[2]];
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
}
