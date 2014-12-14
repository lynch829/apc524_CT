/*!
    \file Source code for 1D function. S
*/

#include "Curve.h"
#include <stdio.h>

Curve::Curve(double rx):Image(Dim1){
	_r = rx;
}

Curve::~Curve(){}

void Curve::SetRange(double rx){
	_r = rx;
}

double Curve::GetRange() const{
	return _r;
}

void Curve::Print(double xmin, double xmax, int N, Interpolator* intpl)
{
    double step = (xmax-xmin)/N;
    for( double x = xmin; x < xmax; x += step)
        printf("%.9f\t%.9f\n", x, (*this)(x,intpl));
}

void Curve::Print()
{ this->Print(-_r,_r,100); }

