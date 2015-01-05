/*!
    \file Source code for 1D function (named Curve).
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
#ifdef USE_HDF
void Curve::ExportHDF(const char* file, double xmin, double xmax, const int N, Interpolator* intpl)
{
  hid_t file_id;
  double x[N];
  double data[N];
  hsize_t dims[Dim1];
  dims[0] = N;
  double step = (xmax-xmin)/N;
  herr_t status;
  for( int i = 0; i < N; i++) {
    x[i] = xmin + step * i; 
    data[i] = (*this)(x[i],intpl);
  }
  file_id = H5Fcreate(file, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
  status = H5LTmake_dataset(file_id,"/x",Dim1,dims,H5T_NATIVE_DOUBLE,x);
  status = H5LTmake_dataset(file_id,"/data",Dim1,dims,H5T_NATIVE_DOUBLE,data);
  status = H5Fclose(file_id);
}

void Curve::ExportHDF(const char* file)
{
  this->ExportHDF(file,-_r,_r,100);
}
#endif
void Curve::Print(double xmin, double xmax, const int N, Interpolator* intpl)
{
  double step = (xmax-xmin)/N;
  for( int i = 0; i < N; i++) {
    double x =  xmin + step * i;
    printf("%.8f %.8f\n",x,(*this)(x,intpl));
  }
}

void Curve::Print()
{
  this->Print(-_r,_r,100);
}
