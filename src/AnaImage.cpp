
#include"AnaImage.h"
#include<iostream>
#include<stdio.h>

AnaFunction::AnaFunction( f1D f, double x) : Function(x){
    _f1d = f;
    var = 0;
}

AnaFunction::~AnaFunction(){}

AnaImage2D::AnaImage2D( f2D f, double x, double y):Image2D(x,y){
    _f2d = f;
     var = 0;
}

AnaImage2D::~AnaImage2D(){}

AnaImage3D::AnaImage3D( f3D f, double x, double y, double z):Image3D(x,y,z){
    _f3d = f;
    var = 0;
}

AnaImage3D::~AnaImage3D(){}

//================================================================

double& AnaFunction::operator()(double x){ return var = _f1d(x); }

void AnaFunction::Print(){
    this->Print(-_r,_r,100);
}
void AnaFunction::Print(double xmin, double xmax, int N){
    double step = (xmax-xmin)/N;
    for( double x = xmin; x < xmax; x += step)
        printf("%.9f\t%.9f\n", x, _f1d(x));
}
//================================================================

double& AnaImage2D::operator()(double x, double y){ return var = _f2d(x,y); }

void AnaImage2D::Print(){
    this->Print(-_rx,_rx,200,-_ry,_ry,200);
}
void AnaImage2D::Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny){
    double stepx = (xmax-xmin)/Nx; double stepy = (ymax-ymin)/Ny;
    for( double y = ymax; y > ymin; y -= stepy){
        for( double x = xmin; x < xmax; x += stepx)
            printf(" %.9f", _f2d(x,y));
        printf("\n");
    }
}
//================================================================

double& AnaImage3D::operator()(double x, double y, double z){ return var = _f3d(x,y,z); }

void AnaImage3D::Print(){
    this->Print(-_rx,_rx,200,-_ry,_ry,200,0);
}
void AnaImage3D::Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double z){
    double stepx = (xmax-xmin)/Nx; double stepy = (ymax-ymin)/Ny;
    for( double y = ymax; y > ymin; y -= stepy){
        for( double x = xmin; x < xmax; x += stepx)
            printf(" %.9f", _f3d(x,y,z));
        printf("\n");
    }
}
