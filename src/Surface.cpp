/*!
    \file Source code for 2D image object. S
*/

#include "Surface.h"
#include <stdio.h>
#include <math.h>

Surface::Surface(double rx, double ry) : Image(Dim2){
    _rx = rx; _ry = ry;
    _r = sqrt(_rx*_rx+_ry*_ry);
    _step = 0.001;
}


Surface::Surface(double rx, double ry, double epsilon) : Image(Dim2){
    _rx = rx;
    _ry = ry;
    _step = epsilon;
}   //! This constructor is especicailly for Romberg Integration Method, for it needs a value of epsilon instead of step size.


Surface::~Surface(){}

void Surface::SetRange(double rx,double ry){ _rx = rx; _ry = ry; _r = sqrt(_rx*_rx+_ry*_ry); }

double Surface::GetRangeX() const { return _rx; }

double Surface::GetRangeY() const { return _ry; }

double Surface::GetRadius() const { return _r; }

NumCurve Surface::GetProjection(LineIntegral* l, double angle, double spacing, Interpolator* intpl){
    int N = int(2*_r/spacing)+1;
    NumCurve ret(N,_r);
    double *x = ret.GetXPtr();
    double *y = ret.GetYPtr();

    for(int i=0; i < N; i++)
        y[i] = this->GetProjectionAtAngle(l,angle,x[i],intpl);
    return ret;
}

void Surface::SetIntegralStep(double epsilon){
    _step = epsilon;
}

double Surface::GetProjectionAtAngle(LineIntegral* l, double angle, double d, Interpolator* intpl){
	double ri = sqrt(_r*_r-d*d);	//!< t goes from -range to +range
        std::function<double (double)> fptr = [angle,d,ri,intpl,this](double t) -> double{
            double temp = (*this)(-sin(angle)*(t-ri)+d*cos(angle),cos(angle)*(t-ri)+d*sin(angle),intpl);
            return temp;
        };
        return l->Integrate(fptr, 0 , 2*ri, _step);
	//!< Uses lambda expression to pass a parameterised function to integral method in the LineIntegral class. Since lambda with [capture] cannot be used as function pointers, have to wrap it with std::function.
	//!< Parameter angle is in radian.
	//!< For a given angle, the function computes line integral along parallel lines with spacing spacing. The parameter t in the lambda is the dummy integration variable moving along the parameterised line. Integration starts and end at the edge defined by _r. d in the loop is the distance of the line to the reference line passing through the origin. S
}

void Surface::Print()
{
  this->Print(-_rx,_rx,200,-_ry,_ry,200);
}

void Surface::Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, Interpolator* intpl)
{
    double stepx = (xmax-xmin)/Nx; double stepy = (ymax-ymin)/Ny;
    for( double y = ymax; y >= ymin; y -= stepy){
        for( double x = xmin; x <= xmax; x += stepx)
            printf(" %.9f", (*this)(x,y,intpl));
        printf("\n");
    }
}

void Surface::ExportHDF(const char* file)
{
    this->ExportHDF(file,-_rx,_rx,200,-_ry,_ry,200);
}

void Surface::ExportHDF(const char* file, double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, Interpolator* intpl)
{
    hid_t file_id;
    hsize_t dims[Dim2];
    dims[0] = Nx;
    dims[1] = Ny; 
    hsize_t dimx[Dim1];
    dimx[0] = Nx;
    hsize_t dimy[Dim1];
    dimy[0] = Ny;
    double x[Nx];
    double y[Ny];
    double data[Nx*Ny];
    double stepx = (xmax-xmin)/Nx;
    double stepy = (ymax-ymin)/Ny;
    herr_t status;
    for( int j = 0; j < Ny; j++) {
        y[j] = ymin + stepy * j;
    } 
    for( int i = 0; i < Nx; i++) {
        x[i] = xmin + stepx * i;
        for( int j = 0; j < Ny; j++) {
            data[i*Ny + j] = (*this)(x[i], y[j], intpl);
        }
    }
    file_id = H5Fcreate(file, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    status = H5LTmake_dataset(file_id,"/x",Dim1,dimx,H5T_NATIVE_DOUBLE,x);
    status = H5LTmake_dataset(file_id,"/y",Dim1,dimy,H5T_NATIVE_DOUBLE,y);
    status = H5LTmake_dataset(file_id,"/data",Dim2,dims,H5T_NATIVE_DOUBLE,data);
    status = H5Fclose(file_id);
}
