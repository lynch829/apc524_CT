#include"Volume.h"
#include<math.h>

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

