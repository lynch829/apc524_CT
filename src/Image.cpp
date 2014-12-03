#include"Image.h"
#include<stdio.h>

Image::Image(Dimension dim){ _dim = dim; }

Image::~Image(){}

Dimension Image::GetDimension(){ return _dim;}


Function::Function(double rx):Image(Dim1){_rx = rx; _r = _rx; }
Function::~Function(){}
void Function::SetRange(double rx){ _rx = rx; _r = _rx; }
double Function::GetRange(){ return _rx; }

Image2D::Image2D(double rx, double ry):Image(Dim2){
    _rx = rx; _ry = ry;
    _r = sqrt(_rx*_rx+_ry*_ry);
}
Image2D::~Image2D(){}
void Image2D::SetRange(double rx,double ry){ _rx = rx; _ry = ry; _r = sqrt(_rx*_rx+_ry*_ry); }
double Image2D::GetRangeX(){ return _rx; }
double Image2D::GetRangeY(){ return _ry; }
double Image2D::GetRadius(){ return _r; }

void Image2D::GetProjection(double angle, double spacing, LineIntegral* l){
    double R = _r;
    for(double d = -_r; d<_r; d += spacing){
	std::function<double (double)> fptr = [angle,d,_r,this](double t) -> double{
		double temp = (*this)((_r-t)*cos(angle)-d*sin(angle),(_r-t)*sin(angle)+d*cos(angle));
		return temp;
	};
        double v = l->Integrate(fptr, -R , R, 1000);
	printf("%.9f\t%.9f\n",d,v);
    }
}

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
