/*!
    \file Source code for 1D function. S
*/

#include"Curve.h"

Curve::Curve(double rx):Image(Dim1){
	_r = rx;
}

Curve::~Curve(){}

void Curve::SetRange(double rx){
	_r = rx;
}

double Curve::GetRange(){
	return _r;
}
