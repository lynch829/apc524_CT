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
 

