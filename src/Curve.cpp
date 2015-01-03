/*!
    \file Source code for 1D function. S
*/

#include "Curve.h"
#include <stdio.h>
#define FILE "output/Curve.h5"

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

void Curve::Print(double xmin, double xmax, const int N, Interpolator* intpl)
{
  hid_t file_id;
  hsize_t dims[Dim1]={N};
  double x[N];
  double data[N];
  double step = (xmax-xmin)/N;
  herr_t status;
  for( int i = 0; i < N; i++) {
    x[i] = xmin + step * i; 
    data[i] = (*this)(x[i],intpl);
  }
  file_id = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
  status = H5LTmake_dataset(file_id,"/x",Dim1,dims,H5T_NATIVE_DOUBLE,x);
  status = H5LTmake_dataset(file_id,"/data",Dim1,dims,H5T_NATIVE_DOUBLE,data);
  status = H5Fclose(file_id);
}

void Curve::Print()
{ this->Print(-_r,_r,100); }

