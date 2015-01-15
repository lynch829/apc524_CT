/*!
    \file Source code for 2D image object. S
*/

#include "Surface.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

Surface::Surface(double rx, double ry) : Image(Dim2){
    _rx = rx; _ry = ry;
    _r = sqrt(_rx*_rx+_ry*_ry);
    _step = 0.001;
}

Surface::~Surface(){}

void Surface::SetRange(double rx,double ry){ _rx = rx; _ry = ry; _r = sqrt(_rx*_rx+_ry*_ry); }

double Surface::GetRangeX() const { return _rx; }

double Surface::GetRangeY() const { return _ry; }

double Surface::GetRange() const { return _r; }

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
#ifdef USE_HDF
// DO NOT include 'output/' in string 'file'.
void Surface::ExportHDF(const char* file)
{
    this->ExportHDF(file,-_rx,_rx,200,-_ry,_ry,200);
}

void Surface::ExportHDF(const char* file, double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, Interpolator* intpl)
{
    char fname[strlen(file)+11];
    strcpy(fname, "output/");
    strcat(fname, file);
// The indexing is meant for consistency with python, VisIt, etc.
    hid_t file_id;
    hsize_t dims[Dim2];
    dims[0] = Ny;
    dims[1] = Nx; 
    hsize_t dimx[Dim1];
    dimx[0] = Nx;
    hsize_t dimy[Dim1];
    dimy[0] = Ny;
    double *x;
    x = new double[Nx];
    double *y;
    y = new double[Ny];
    double *data;
    data = new double[Ny*Nx];
    double stepx = (xmax-xmin)/Nx;
    double stepy = (ymax-ymin)/Ny;
    herr_t status;
    for( int i = 0; i < Nx; i++) {
        x[i] = xmin + stepx * i;
    }
    for( int j = 0; j < Ny; j++) {
        y[j] = ymin + stepy * j;
        for( int i = 0; i < Nx; i++) {
            data[i + j*Nx] = (*this)(x[i], y[j], intpl);
        }
    } 
    file_id = H5Fcreate(fname, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    status = H5LTmake_dataset_double(file_id,"/x",Dim1,dimx,x);
    status = H5LTset_attribute_int(file_id,"/x","size of x",&Nx,1);
    status = H5LTmake_dataset_double(file_id,"/y",Dim1,dimy,y);
    status = H5LTset_attribute_int(file_id,"/y","size of y",&Ny,1);
    status = H5LTmake_dataset_double(file_id,"/data",Dim2,dims,data);
    status = H5Fclose(file_id);
    delete [] x;
    delete [] y;
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
    fprintf(xmf, "     <Topology TopologyType=\"2DRectMesh\" NumberOfElements=\"%d %d\"/>\n", Ny, Nx);
    fprintf(xmf, "     <Geometry GeometryType=\"VXVY\">\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", Nx);
    fprintf(xmf, "        %s:/x\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", Ny);
    fprintf(xmf, "        %s:/y\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Geometry>\n");
    fprintf(xmf, "     <Attribute Name=\"data\" AttributeType=\"Scalar\" Center=\"Node\">\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", Ny, Nx);
    fprintf(xmf, "        %s:/data\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Attribute>\n");
    fprintf(xmf, "   </Grid>\n");
    fprintf(xmf, " </Domain>\n");
    fprintf(xmf, "</Xdmf>\n");
    fclose(xmf);

}
#endif
