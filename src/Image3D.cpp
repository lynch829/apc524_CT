#include"Image3D.h"
#include<math.h>

Image3D::Image3D(double rx, double ry, double rz):Image(Dim3){
    _rx = rx; _ry = ry; _rz = rz;
    _r = sqrt(_rx*_rx+_ry*_ry);
}

Image3D::~Image3D(){}
void Image3D::SetRange(double rx, double ry, double rz){
    _rx = rx; _ry = ry; _rz = rz;
    _r = sqrt(_rx*_rx+_ry*_ry);
}

double Image3D::GetRangeX(){ return _rx; }

double Image3D::GetRangeY(){ return _ry; }

double Image3D::GetRangeZ(){ return _rz; }

double Image3D::GetRadius(){ return _r; }

