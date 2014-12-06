/*!
    \file Source code for 2D image object. S
*/

#include"Image2D.h"
#include<stdio.h>
#include<math.h>

Image2D::Image2D(double rx, double ry) : Image(Dim2){
    _rx = rx; _ry = ry;
    _r = sqrt(_rx*_rx+_ry*_ry);
    _step = 0.01;
}

Image2D::~Image2D(){}

void Image2D::SetRange(double rx,double ry){ _rx = rx; _ry = ry; _r = sqrt(_rx*_rx+_ry*_ry); }

double Image2D::GetRangeX(){ return _rx; }

double Image2D::GetRangeY(){ return _ry; }

double Image2D::GetRadius(){ return _r; }

void Image2D::GetProjection(LineIntegral* l, double angle, double spacing){

    for(double d = -_r; d<_r; d += spacing){
        std::function<double (double)> fptr = [angle,d,_r,this](double t) -> double{
            double temp = (*this)((_r-t)*cos(angle)-d*sin(angle),(_r-t)*sin(angle)+d*cos(angle));
            return temp;
        };
	//!< Uses lambda expression to pass a parameterised function to integral method in the LineIntegral class. Since lambda with [capture] cannot be used as function pointers, have to wrap it with std::function.
	//!< Parameter angle is in radian.
	//!< For a given angle, the function computes line integral along parallel lines with spacing spacing. The parameter t in the lambda is the dummy integration variable moving along the parameterised line. Integration starts and end at the edge defined by _r. d in the loop is the distance of the line to the reference line passing through the origin. S

        double v = l->Integrate(fptr, -_r , _r, _step);
        printf("%.9f\t%.9f\n",d,v);
    }
}

void Image2D::GetProjectionAtAngle(LineIntegral* l, double angle, double d){

        std::function<double (double)> fptr = [angle,d,_r,this](double t) -> double{
            double temp = (*this)((_r-t)*cos(angle)-d*sin(angle),(_r-t)*sin(angle)+d*cos(angle));
            return temp;
        };
	//!< Uses lambda expression to pass a parameterised function to integral method in the LineIntegral class. Since lambda with [capture] cannot be used as function pointers, have to wrap it with std::function.
	//!< Angle is in radian.

        return l->Integrate(fptr, -_r , _r, _step);
}

