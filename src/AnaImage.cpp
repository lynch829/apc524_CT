
#include"AnaImage.h"
#include<iostream>
#include<stdio.h>

AnaCurve::AnaCurve( f1D f, double x) : Curve(x)
{ _f1d = f; }

AnaCurve::~AnaCurve()
{}

AnaSurface::AnaSurface( f2D f, double x, double y):Surface(x,y)
{ _f2d = f; }

AnaSurface::~AnaSurface()
{ }

AnaVolume::AnaVolume( f3D f, double x, double y, double z):Volume(x,y,z)
{ _f3d = f; }

AnaVolume::~AnaVolume()
{ }

//================================================================

double AnaCurve::operator()(double x, Interpolator* intp)
{ return _f1d(x); }

void AnaCurve::Print()
{ this->Print(-_r,_r,100); }

void AnaCurve::Print(double xmin, double xmax, int N)
{
    double step = (xmax-xmin)/N;
    for( double x = xmin; x < xmax; x += step)
        printf("%.9f\t%.9f\n", x, _f1d(x));
}
//================================================================

double AnaSurface::operator()(double x, double y, Interpolator* intp)
{ return _f2d(x,y); }

void AnaSurface::Print()
{ this->Print(-_rx,_rx,200,-_ry,_ry,200); }

void AnaSurface::Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny)
{
    double stepx = (xmax-xmin)/Nx; double stepy = (ymax-ymin)/Ny;
    for( double y = ymax; y > ymin; y -= stepy){
        for( double x = xmin; x < xmax; x += stepx)
            printf(" %.9f", _f2d(x,y));
        printf("\n");
    }
}
//================================================================

double AnaVolume::operator()(double x, double y, double z, Interpolator* intp)
{ return _f3d(x,y,z); }

void AnaVolume::Print()
{ this->Print(-_rx,_rx,200,-_ry,_ry,200,0); }

void AnaVolume::Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double z)
{
    double stepx = (xmax-xmin)/Nx; double stepy = (ymax-ymin)/Ny;
    for( double y = ymax; y > ymin; y -= stepy){
        for( double x = xmin; x < xmax; x += stepx)
            printf(" %.9f", _f3d(x,y,z));
        printf("\n");
    }
}
