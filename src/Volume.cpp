#include "Volume.h"
#include <math.h>
#include <stdio.h>
#define FILE "output/Volume.h5"

Volume::Volume(double rx, double ry, double rz):Image(Dim3){
    _rx = rx; _ry = ry; _rz = rz;
    _r = sqrt(_rx*_rx+_ry*_ry);
}

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
    int j = 0;
    for(double d1 = -_rz; d1 < _rz; d1 += spacingz){
        x[i] = d1;
        for(double d2 = -_r; d2 < _r; d2 += spacingr){
            y[j] = d2;
            z[i][j] = this->GetProjectionAtAngle(l,angle,d2,d1,intpl);
            printf("$lf %lf\n",d2,d1);
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
        printf("getatangle %lf\n", temp);
        return temp;
    };
    return l->Integrate(fptr, 0 , 2*ri, _step);
}

void Volume::Print()
{ this->Print(-_rx,_rx,200,-_ry,_ry,200,0.0); }

void Volume::Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double z, Interpolator* intpl)
{
    hid_t file_id;
    hsize_t dims[Dim2]={Nx, Ny};
    hsize_t dimx[Dim1]={Nx};
    hsize_t dimy[Dim1]={Ny};
    hsize_t dimz[Dim1]={1};
    double x[Nx];
    double y[Ny];
    double data[Nx][Ny];
    double stepx = (xmax-xmin)/Nx;
    double stepy = (ymax-ymin)/Ny;
    herr_t status;
    for( int j = 0; j < Ny; j++) {
        y[j] = ymin + stepy * j;
    }
    for( int i = 0; i < Nx; i++) {
        x[i] = xmin + stepx * i;
        for( int j = 0; j < Ny; j++) {
            data[i][j] = (*this)(x[i], y[j], z, intpl);
        }
    }
    file_id = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    status = H5LTmake_dataset(file_id,"/x",Dim1,dimx,H5T_NATIVE_DOUBLE,x);
    status = H5LTmake_dataset(file_id,"/y",Dim1,dimy,H5T_NATIVE_DOUBLE,y);
    status = H5LTmake_dataset(file_id,"/z",Dim1,dimz,H5T_NATIVE_DOUBLE,&z);
    status = H5LTmake_dataset(file_id,"/data",Dim2,dims,H5T_NATIVE_DOUBLE,data);
    status = H5Fclose(file_id);
}

