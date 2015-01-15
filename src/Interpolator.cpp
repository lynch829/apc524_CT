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

//! Set necessary values for interpolator. This method is called before interpolation is performed.
//! Interpolator has access to the private data of respective classes, and access that information idrectly through pointers.
//! This is for 2D.
void Interpolator::set_values(int sizex, int sizey, double* xptr, double* yptr, double** vptr) 
{ 
    _xptr = xptr; 
    _yptr = yptr; 
    _sizex = sizex; 
    _sizey = sizey; 
    _zzptr = vptr; 
}

//! 3D interpolator set value method. This function must be called before interpolation.
void Interpolator::set_values(int sizex, int sizey,int sizez, double* xptr, double* yptr, double* zptr, double*** wptr) 
{ 
    _xptr = xptr; 
    _yptr = yptr; 
    _zptr = zptr; 
    _sizex = sizex; 
    _sizey = sizey; 
    _sizez = sizez; 
    _wptr = wptr; 
}
