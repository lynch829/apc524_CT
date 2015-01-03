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

