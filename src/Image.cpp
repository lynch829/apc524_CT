#include"Image.h"
#include<math.h>

Image::Image(Dimension dim){ _dim = dim; }

Image::~Image(){}

Dimension Image::GetDimension(){ return _dim;}


Function::Function(double rx):Image(Dim1){_rx = rx;}
Function::~Function(){}
void Function::SetRange(double rx){ _rx = rx; }
double Function::GetRange(){return _rx;}

Image2D::Image2D(double rx, double ry):Image(Dim2){ _rx = rx; _ry = ry;}
Image2D::~Image2D(){}
void Image2D::SetRange(double rx,double ry){ _rx = rx; _ry = ry;}
double Image2D::GetRangeX(){return _rx;}
double Image2D::GetRangeY(){return _ry;}
double Image2D::GetRadius(){ return sqrt(_rx*_rx+_ry*_ry);}

Image3D::Image3D(double rx, double ry, double rz):Image(Dim2){_rx = rx; _ry = ry; _rz = rz;}
Image3D::~Image3D(){}
void Image3D::SetRange(double rx, double ry, double rz){ _rx = rx; _ry = ry; _rz = rz;}
double Image3D::GetRangeX(){return _rx;}
double Image3D::GetRangeY(){return _ry;}
double Image3D::GetRangeZ(){return _rz;}
double Image3D::GetRadius(){ return sqrt(_rx*_rx+_ry*_ry);}
