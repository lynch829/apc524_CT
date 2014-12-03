/*!
    \file Source code for 1D function. S
*/

#include"Function.h"

Function::Function(double rx):Image(Dim1){
	_r = rx;
}

Function::~Function(){}

void Function::SetRange(double rx){
	_r = rx;
}

double Function::GetRange(){
	return _r;
}
