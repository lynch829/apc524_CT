//
//  Interpolator.cpp
//  
//
//  Created by Qi Li on 12/17/14.
//
//

#include "Interpolator.h"
Interpolator::Interpolator(){}

Interpolator::~Interpolator(){
    if(_xptr!=0) delete [] _xptr;
    if(_yptr!=0) delete [] _yptr;
    if(_vptr!=0) {
        for(int i=0;i<_sizex;i++) delete [] _vptr[i];
        delete [] _vptr;
       }
}
 
void Interpolator::set_values(int sizex, int sizey, double* xptr, double* yptr, double** vptr){

_xptr = new double[sizex];
for (int i = 0;i<sizex;i++){
    double temp = xptr[i];
    _xptr[i] = temp;
}

_yptr = new double[sizey];
for (int i = 0;i<sizey;i++){
     double temp = yptr[i];
    _yptr[i] = temp;
}
_sizex = sizex; _sizey = sizey;

_vptr = new double*[sizex];
for (int i = 0;i<sizex;i++){
    _vptr[i] = new double[sizey];
}

for (int i = 0;i<sizex;i++){
    for (int j=0;j<sizey;j++){
    double temp = vptr[i][j];
    _vptr[i][j] = temp;
    }
}

//delete [] _xptr; delete [] _yptr;
//for(int i=0;i<_sizex;i++){
//   delete [] _vptr[i];
//   }
//delete [] _vptr;
}


void Interpolator::set_values(int sizex, int sizey,int sizez, double* xptr, double* yptr, double* zptr, double*** wptr){
_xptr = new double[sizex];
for (int i = 0;i<sizex;i++){
    _xptr[i] = xptr[i];
}
_yptr = new double[sizey];
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
