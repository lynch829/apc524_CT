/*! \file
    \brief Source code for 1D function (Curve).
*/
#include "Curve.h"
#include <stdio.h>
#include <string.h>

Curve::Curve(double rx):Image(Dim1)
{
	_r = rx;
	//!< Curve must be initialized with the range over which it is defined.
}

Curve::~Curve(){}

void Curve::SetRange(double rx)
{
	_r = rx;
}

double Curve::GetRange() const
{
	return _r;
}

#ifdef USE_HDF
//! Export data to HDF5 file. DO NOT include 'output/' in string 'file'.
void Curve::ExportHDF(const char* file, double xmin, double xmax, const int N, Interpolator* intpl)
{
  char fname[strlen(file)+7];
  strcpy(fname, "output/"); // Automatically export to directory 'output/'
  strcat(fname, file);
// Allocate memory for output data
  double *x;
  x = new double[N];
  double *data;
  data = new double[N];
// Generate output data
  double step = (xmax-xmin)/N;
  for( int i = 0; i < N; i++) {
    x[i] = xmin + step * i; 
    data[i] = (*this)(x[i],intpl);
  }
// Create file and save data
  hid_t file_id;
  hsize_t dims[Dim1];
  dims[0] = N;
  herr_t status;
  file_id = H5Fcreate(fname, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
  status = H5LTmake_dataset_double(file_id,"/x",Dim1,dims,x);
  status = H5LTset_attribute_int(file_id,"/x","size of x",&N,1); // Number of grids is saved as an attribute
  status = H5LTmake_dataset_double(file_id,"/data",Dim1,dims,data);
  status = H5Fclose(file_id);
// Clear up memory
  delete [] x;
  delete [] data;
}

//! Export data to HDF5 file. DO NOT include 'output/' in string 'file'.
void Curve::ExportHDF(const char* file)
{
  this->ExportHDF(file,-_r,_r,100);
		//!< call overloaded ExportHDF with arguments.
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
