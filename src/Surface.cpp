/*!
    \file Source code for 2D image object. S
*/

#include "Surface.h"
#include "NumImage.h"
#include <stdio.h>
#include <math.h>

Surface::Surface(double rx, double ry) : Image(Dim2){
    _rx = rx; _ry = ry;
    _r = sqrt(_rx*_rx+_ry*_ry);
    _step = 0.01;
}

Surface::~Surface(){}

void Surface::SetRange(double rx,double ry){ _rx = rx; _ry = ry; _r = sqrt(_rx*_rx+_ry*_ry); }

double Surface::GetRangeX(){ return _rx; }

double Surface::GetRangeY(){ return _ry; }

double Surface::GetRadius(){ return _r; }

Curve Surface::GetProjection(LineIntegral* l, double angle, double spacing){
    int counter = 0
    for(double d = -_r; d<_r; d += spacing){ counter++; }
    NumCurve ret(counter);
    double *x = new double[counter];
    double *y = new double[counter];

    int i=0
    for(double d = -_r; d<_r; d += spacing){
        x[i] = d;
        y[i] = this->GetProjectionAtAngle(l,angle,d);
    }
    return NumCurve(counter,x,y);
}

double Surface::GetProjectionAtAngle(LineIntegral* l, double angle, double d){

        std::function<double (double)> fptr = [angle,d,_r,this](double t) -> double{
            double temp = (*this)((_r-t)*cos(angle)-d*sin(angle),(_r-t)*sin(angle)+d*cos(angle));
            return temp;
        };
	//!< Uses lambda expression to pass a parameterised function to integral method in the LineIntegral class. Since lambda with [capture] cannot be used as function pointers, have to wrap it with std::function.
	//!< Parameter angle is in radian.
	//!< For a given angle, the function computes line integral along parallel lines with spacing spacing. The parameter t in the lambda is the dummy integration variable moving along the parameterised line. Integration starts and end at the edge defined by _r. d in the loop is the distance of the line to the reference line passing through the origin. S

        return l->Integrate(fptr, -_r , _r, _step);
}
