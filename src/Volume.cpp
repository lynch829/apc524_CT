#include "Volume.h"
#include <math.h>
#include <stdio.h>

Volume::Volume(double rx, double ry, double rz):Image(Dim3){
    _rx = rx; _ry = ry; _rz = rz;
    _r = sqrt(_rx*_rx+_ry*_ry);
    _step = 0.001;
}

Volume::Volume(double rx, double ry, double rz, double epsilon):Image(Dim3){
    _rx = rx; _ry = ry; _rz = rz;
    _r = sqrt(_rx*_rx+_ry*_ry);
    _step = epsilon;
}  //! This constructor is especicailly for Romberg Integration Method, for it needs a value of epsilon instead of step size.


Volume::~Volume(){}
void Volume::SetRange(double rx, double ry, double rz){
    _rx = rx; _ry = ry; _rz = rz;
    _r = sqrt(_rx*_rx+_ry*_ry);
}

double Volume::GetRangeX() const { return _rx; }
double Volume::GetRangeY() const { return _ry; }
double Volume::GetRangeZ() const { return _rz; }
double Volume::GetRadius() const { return _r; }

void Volume::SetIntegralStep(double epsilon){
    _step = epsilon;
}

NumSurface Volume::GetProjection(LineIntegral* l, double angle, double spacingr, double spacingz, Interpolator* intpl){
    int counterr = 0;
    int counterz = 0;
    for(double d = -_r; d<_r; d += spacingr){ counterr++; }
    for(double d = -_rz; d<_rz; d += spacingz){ counterz++; }
    NumSurface ret(counterz, counterr);
    double *x = ret.GetXPtr();
    double *y = ret.GetYPtr();
    double **z = ret.GetZPtr();
    
    int i = 0;
    for(double d1 = -_rz; d1 < _rz; d1 += spacingz){
        x[i] = d1;
        int j = 0;
        for(double d2 = -_r; d2 < _r; d2 += spacingr){
            y[j] = d2;
            z[i][j] = this->GetProjectionAtAngle(l,angle,d2,d1,intpl);
            j++;
        }
        i++;
    }
    return NumSurface(counterz, x, counterr, y, z);
}

double Volume::GetProjectionAtAngle(LineIntegral* l, double angle_arg, double d, double z, Interpolator* intpl){
    double angle = angle_arg-pi/2;
    double ri = sqrt(_r*_r-d*d);	//!< t goes from -range to +range
    std::function<double (double)> fptr = [angle,d,z,ri,intpl,this](double t) -> double{
        double temp = (*this)((ri-t)*sin(angle)+d*cos(angle),(t-ri)*cos(angle)+d*sin(angle),z,intpl);
        return temp;
    };
    return l->Integrate(fptr, 0 , 2*ri, _step);
}
void Volume::Print()
{ this->Print(-_rx,_rx,200,-_ry,_ry,200,0.0); }

void Volume::Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double z, Interpolator* intpl)
{
    double stepx = (xmax-xmin)/Nx; double stepy = (ymax-ymin)/Ny;
    for( double y = ymax; y >= ymin; y -= stepy){
        for( double x = xmin; x <= xmax; x += stepx)
            printf(" %.9f", (*this)(x,y,z,intpl));
        printf("\n");
    }
}
#ifdef USE_HDF
void Volume::ExportHDF(const char* file)
{
    this->ExportHDF(file,-_rx,_rx,200,-_ry,_ry,200,0.0,0.0,0.0);
}

void Volume::ExportHDF(const char* file,double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double zmin, double zmax, int Nz, Interpolator* intpl)
{
    hid_t file_id;
    hsize_t dims[Dim3];
    dims[0] = Nx;
    dims[1] = Ny;
    dims[2] = Nz;
    hsize_t dimx[Dim1];
    dimx[0] = Nx;
    hsize_t dimy[Dim1];
    dimy[0] = Ny;
    hsize_t dimz[Dim1];
    dimz[0] = Nz;
    double x[Nx];
    double y[Ny];
    double z[Nz];
    double data[Nx*Ny*Nz];
    double stepx = (xmax-xmin)/Nx;
    double stepy = (ymax-ymin)/Ny;
    double stepz = (zmax-zmin)/Nz;
    herr_t status;
    for( int j = 0; j < Ny; j++) {
        y[j] = ymin + stepy * j;
    }
    for( int k = 0; k < Nz; k++) {
        z[k] = zmin + stepz * k;
    }
    for( int i = 0; i < Nx; i++) {
        x[i] = xmin + stepx * i;
        for( int j = 0; j < Ny; j++) {
            for( int k = 0; k < Nz; k++) {
                data[(i*Ny+j)*Nz + k] = (*this)(x[i], y[j], z[k], intpl);
            }
        }
    }
    file_id = H5Fcreate(file, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    status = H5LTmake_dataset(file_id,"/x",Dim1,dimx,H5T_NATIVE_DOUBLE,x);
    status = H5LTmake_dataset(file_id,"/y",Dim1,dimy,H5T_NATIVE_DOUBLE,y);
    status = H5LTmake_dataset(file_id,"/z",Dim1,dimz,H5T_NATIVE_DOUBLE,z);
    status = H5LTmake_dataset(file_id,"/data",Dim3,dims,H5T_NATIVE_DOUBLE,data);
    status = H5Fclose(file_id);
}
#endif
