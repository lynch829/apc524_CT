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
int Interpolator::coord2index(int* coords, int* size, int dim){
    int ind = 0;
    int step = 1;
    for (int d=dim-1; d>=0; --d) {
        ind += coords[d]*step;
        step *= size[d];
    }
    return ind;
}
