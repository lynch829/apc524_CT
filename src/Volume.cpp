#include "Volume.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

Volume::Volume(double rx, double ry, double rz):Image(Dim3)
{
    _rx = rx; _ry = ry; _rz = rz;
    _r = sqrt(_rx*_rx+_ry*_ry);
    _step = 0.001;
}

Volume::~Volume(){}

void Volume::SetRange(double rx, double ry, double rz)
{
    _rx = rx; _ry = ry; _rz = rz;
    _r = sqrt(_rx*_rx+_ry*_ry+_rz*_rz);
}

double Volume::GetRangeX() const { return _rx; }
double Volume::GetRangeY() const { return _ry; }
double Volume::GetRangeZ() const { return _rz; }
double Volume::GetRadius() const { return _r; }

//!< This is the integration step size. For Romberg method this is the precision.
void Volume::SetIntegralStep(double epsilon)
{
    _step = epsilon;
}

//!< Returns projection curve at a particular angle and height.
NumCurve Volume::GetProjection(LineIntegral* l, double angle, double spacing, double z, Interpolator* intpl)
{
    int N = int(2*_r/spacing)+1;
    NumCurve ret(N,_r);
    double *x = ret.GetXPtr();
    double *y = ret.GetYPtr();
    
    for(int i=0; i < N; i++)
        y[i] = this->GetProjectionAtAngle(l,angle,x[i],z,intpl);
    return ret;
}

//!< Returns the projection at a certain angle, distance and height.
double Volume::GetProjectionAtAngle(LineIntegral* l, double angle_arg, double d, double z, Interpolator* intpl)
{
    double angle = angle_arg-pi/2;
    double ri = sqrt(_r*_r-d*d);
		//!< t goes from -range to +range
    std::function<double (double)> fptr = [angle,d,z,ri,intpl,this](double t) -> double
    {
        double temp = (*this)((ri-t)*sin(angle)+d*cos(angle),(t-ri)*cos(angle)+d*sin(angle),z,intpl);
        return temp;
    };
    return l->Integrate(fptr, 0 , 2*ri, _step);
}

//!< Default print method, will call overloaded print method.
void Volume::Print()
{ this->Print(-_rx,_rx,200,-_ry,_ry,200,0.0); }

//!< Print the volume information in the range specified.
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

// DO NOT include 'output/' in string 'file'.
void Volume::ExportHDF(const char* file)
{
    this->ExportHDF(file,-_rx,_rx,100,-_ry,_ry,100,-_rz,_rz,100);
}

void Volume::ExportHDF(const char* file,double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double zmin, double zmax, int Nz, Interpolator* intpl)
{
    char fname[strlen(file)+11];
    strcpy(fname, "output/"); // Automatically export to directory 'output/'
    strcat(fname, file);
// Allocate memory for output data
    double *x;
    x = new double[Nx];
    double *y;
    y = new double[Ny];
    double *z;
    z = new double[Nz];
    double *data;
    data= new double[Nz*Ny*Nx];
// Generate output data
    double stepx = (xmax-xmin)/Nx;
    double stepy = (ymax-ymin)/Ny;
    double stepz = (zmax-zmin)/Nz;
    for( int i = 0; i < Nx; i++) {
        x[i] = xmin + stepx * i;
    }
    for( int j = 0; j < Ny; j++) {
        y[j] = ymin + stepy * j;
    }
    for( int k = 0; k < Nz; k++) {
        z[k] = zmin + stepz * k;
        for( int j = 0; j < Ny; j++) {
            for( int i = 0; i < Nx; i++) {
// The indexing is meant for consistency with python, VisIt, etc.
                data[i+(j+k*Ny)*Nx] = (*this)(x[i], y[j], z[k], intpl);
            }
        }
    }
// Create file and save data
    hid_t file_id;
    herr_t status;
    hsize_t dims[Dim3];
    dims[0] = Nz;
    dims[1] = Ny;
    dims[2] = Nx;
    hsize_t dimx[Dim1];
    dimx[0] = Nx;
    hsize_t dimy[Dim1];
    dimy[0] = Ny;
    hsize_t dimz[Dim1];
    dimz[0] = Nz;
    file_id = H5Fcreate(fname, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
// Number of grids saved as attributes. Coodrinates saved as 1D arrays since the mesh is rectilinear. Data saved as 3D array. 
    status = H5LTmake_dataset_double(file_id,"/x",Dim1,dimx,x);
    status = H5LTmake_dataset_double(file_id,"/y",Dim1,dimy,y);
    status = H5LTmake_dataset_double(file_id,"/z",Dim1,dimz,z);
    status = H5LTmake_dataset_double(file_id,"/data",Dim3,dims,data);
    status = H5LTset_attribute_int(file_id,"/x","size of x",&Nx,1);
    status = H5LTset_attribute_int(file_id,"/y","size of y",&Ny,1);
    status = H5LTset_attribute_int(file_id,"/z","size of z",&Nz,1);
    status = H5Fclose(file_id);
// Clear up memory
    delete [] x;
    delete [] y;
    delete [] z;
    delete [] data;
// Create XMDF file that accompanies HDF5 file so as to enable VisIt reading.
    strcat(fname, ".xmf");
    FILE *xmf = 0;
    xmf = fopen(fname, "w");
    fprintf(xmf, "<?xml version=\"1.0\" ?>\n");
    fprintf(xmf, "<!DOCTYPE Xdmf SYSTEM \"Xdmf.dtd\" []>\n");
    fprintf(xmf, "<Xdmf Version=\"2.0\">\n");
    fprintf(xmf, " <Domain>\n");
    fprintf(xmf, "   <Grid Name=\"mesh\" GridType=\"Uniform\">\n");
    fprintf(xmf, "     <Topology TopologyType=\"3DRectMesh\" NumberOfElements=\"%d %d %d\"/>\n", Nz, Ny, Nx);
    fprintf(xmf, "     <Geometry GeometryType=\"VXVYVZ\">\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", Nx);
    fprintf(xmf, "        %s:/x\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", Ny);
    fprintf(xmf, "        %s:/y\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", Nz);
    fprintf(xmf, "        %s:/z\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Geometry>\n");
    fprintf(xmf, "     <Attribute Name=\"data\" AttributeType=\"Scalar\" Center=\"Node\">\n");
fprintf(xmf, "       <DataItem Dimensions=\"%d %d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", Nz, Ny, Nx);
    fprintf(xmf, "        %s:/data\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Attribute>\n");
    fprintf(xmf, "   </Grid>\n");
    fprintf(xmf, " </Domain>\n");
    fprintf(xmf, "</Xdmf>\n");
    fclose(xmf);
}
#endif
