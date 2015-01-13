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
    if(_zptr!=0) delete [] _zptr;
    if(_zzptr!=0) {
        for(int i=0;i<_sizex;i++) delete [] _zzptr[i];
        delete [] _zzptr;
       }

    if(_wptr!=0){
    for (int i = 0; i < _sizex; ++i) {
        for (int j = 0; j < _sizey; ++j)
            delete [] _wptr[i][j];
        delete [] _wptr[i];
    }
    delete [] _wptr;
      }
}
 

