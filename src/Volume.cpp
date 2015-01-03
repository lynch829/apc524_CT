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
    double stepx = (xmax-xmin)/Nx; double stepy = (ymax-ymin)/Ny;
    for( double y = ymax; y >= ymin; y -= stepy){
        for( double x = xmin; x <= xmax; x += stepx)
            printf(" %.9f", (*this)(x,y,z,intpl));
        printf("\n");
    }
}

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
    file_id = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    status = H5LTmake_dataset(file_id,"/x",Dim1,dimx,H5T_NATIVE_DOUBLE,x);
    status = H5LTmake_dataset(file_id,"/y",Dim1,dimy,H5T_NATIVE_DOUBLE,y);
    status = H5LTmake_dataset(file_id,"/z",Dim1,dimz,H5T_NATIVE_DOUBLE,z);
    status = H5LTmake_dataset(file_id,"/data",Dim3,dims,H5T_NATIVE_DOUBLE,data);
    status = H5Fclose(file_id);
}
