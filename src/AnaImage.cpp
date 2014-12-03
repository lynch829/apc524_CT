
#include"AnaImage.h"
#include<iostream>
#include<stdio.h>

AnaImage::AnaImage( Dimension dim, f1D f):Image(dim){
    _f1d = f;
    _f2d = NULL; _f3d = NULL;	var = 0;
}

AnaImage::AnaImage( Dimension dim, f2D f):Image(dim){
    _f2d = f;
    _f1d = NULL; _f3d = NULL;	var = 0;
}

AnaImage::AnaImage( Dimension dim, f3D f):Image(dim){
    _f3d = f;
    _f1d = NULL; _f2d = NULL;	var = 0;
}

AnaImage::~AnaImage(){}

double& AnaImage::operator()(double x, double y, double z){
    switch(_dim){
        case Dim1 : var = _f1d(x); break;
        case Dim2 : var = _f2d(x,y); break;
        case Dim3 : var = _f3d(x,y,z); break;
        default : var = 0; break;
    }
    return var;
}

void AnaImage::Print(){
    for(double y=5; y>=-5; y-=0.2){
        for( double x = -5; x<=5; x+=0.2)
            printf(" %.9f",(*this)(x,y,0));
        printf("\n");
        if(_dim == Dim1) break;
    }
}
