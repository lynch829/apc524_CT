#include "Volume.h"
#include <math.h>
#include <stdio.h>

Volume::Volume(double rx, double ry, double rz):Image(Dim3){
    _rx = rx; _ry = ry; _rz = rz;
    _r = sqrt(_rx*_rx+_ry*_ry);
}

Volume::~Volume(){}
void Volume::SetRange(double rx, double ry, double rz){
    _rx = rx; _ry = ry; _rz = rz;
    _r = sqrt(_rx*_rx+_ry*_ry);
}

double Volume::GetRangeX() const { return _rx; }

double Volume::GetRangeY() const { return _ry; }

double Volume::GetRangeZ() const { return _rz; }

double Volume::GetRadius() const { return _r; }

void Volume::Print()
{ this->Print(-_rx,_rx,200,-_ry,_ry,200,0.0); }

void Volume::Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double z, Interpolator* intpl)
{
    double stepx = (xmax-xmin)/Nx; double stepy = (ymax-ymin)/Ny;
    for( double y = ymax; y > ymin; y -= stepy){
        for( double x = xmin; x < xmax; x += stepx)
            printf(" %.9f", (*this)(x,y,z,intpl));
        printf("\n");
    }
}

