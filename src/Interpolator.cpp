//
//  Interpolator.cpp
//  
//
//  Created by Qi Li on 12/17/14.
//
//

#include "Interpolator.h"
Interpolator::Interpolator(){}
Interpolator::~Interpolator(){} 
void Interpolator::set_values(int sizex, int sizey, double* xptr, double* yptr, double** vptr){

_xptr = new double[sizex];
for (int i = 0;i<sizex;i++){
    _xptr[i] = xptr[i];
}

_yptr = new double[sizey];
for (int i = 0;i<sizey;i++){
    _yptr[i] = yptr[i];
}
_sizex = sizex; _sizey = sizey;

_vptr = new double*[sizex];
for (int i = 0;i<sizex;i++){
    _vptr[i] = new double[sizey];
}

for (int i = 0;i<sizex;i++){
    for (int j=0;j<sizey;j++){
    _vptr[i][j] = vptr[i][j];
    }
}
}


void Interpolator::set_values(int sizex, int sizey,int sizez, double* xptr, double* yptr, double* zptr, double*** wptr){
for (int i = 0;i<sizex;i++){
    _xptr[i] = xptr[i];
}
for (int i = 0;i<sizey;i++){
    _yptr[i] = yptr[i];
}
for (int i = 0;i<sizez;i++){
    _zptr[i] = zptr[i];
}

_sizex = sizex; _sizey = sizey; _sizez = sizez;

for (int i = 0;i<sizex;i++){
    for (int j=0;j<sizey;j++){
        for(int k=0;k<sizez;k++){
           _wptr[i][j][k] = wptr[i][j][k];
           }
    }
}
}
int Interpolator::coord2index(int* coords, int* size, int dim){
    int ind = 0;
    int step = 1;
    for (int d=dim-1; d>=0; --d) {
        ind += coords[d]*step;
        step *= size[d];
    }
    return ind;
}
