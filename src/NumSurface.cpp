/*!
  \file
  \brief Implementation for numerical surfaces.
*/

#include "NumSurface.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//! Default constructor, everything to 0 or Null
NumSurface::NumSurface() : Surface(0,0)
{
    _datax = 0;
    _datay = 0;
    _dataz = 0;
    _sizex = 0;
    _sizey = 0;
}

//! Constructor with a size input. Range is still 0 so subsequently range must be adjusted.
NumSurface::NumSurface(int sizex, int sizey): Surface(0,0), _sizex(sizex), _sizey(sizey)
{
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double*[_sizex];
    for(int i=0;i<_sizex;i++)
        _dataz[i] = new double[_sizey];
}

//! Constructor with a given array. Range is read from the maximum of the array element.
NumSurface::NumSurface(int sizex, double* x, int sizey, double* y, double** z)
: Surface(0,0), _sizex(sizex), _sizey(sizey)
{
    double avg = 0;		//!< x-direction, symmetrize the given array by subtracting the average.
    for(int i=0;i<_sizex;i++){avg += x[i];}
    avg /= _sizex;
    _datax = new double[_sizex];
    for(int i=0;i<_sizex;i++){
        _datax[i] = x[i]-avg;
    }

    avg = 0;			//!< y-direction, symmetrize the given array. Center them at 0.
    for(int i=0;i<_sizey;i++){avg += y[i];}
    avg /= _sizey;
    _datay = new double[_sizey];
    for(int i=0;i<_sizey;i++){
        _datay[i] = y[i]-avg;
    }

    _dataz = new double*[_sizex];
    for(int i=0;i<_sizex;i++)
        _dataz[i] = new double[_sizey];
    for(int i=0;i<_sizex;i++)
        for(int j=0;j<_sizey;j++)
            _dataz[i][j] = z[i][j];

    _rx = fabs(_datax[0]) > fabs(_datax[_sizex-1]) ? fabs(_datax[0]) : fabs(_datax[_sizex-1]);
    _ry = fabs(_datay[0]) > fabs(_datay[_sizey-1]) ? fabs(_datay[0]) : fabs(_datay[_sizey-1]);
				//!< Find the largest coordinate as the range.
    _r = sqrt(_rx*_rx+_ry*_ry);	//!< Don't forget to set the range.
}

//! Constructor with a given size, range and a set of z-values. Assumes equal spacing.
NumSurface::NumSurface(int sizex, double rx, int sizey, double ry, double** z)
: Surface(rx,ry), _sizex(sizex), _sizey(sizey)
{
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double*[_sizex];
    for(int i=0;i<_sizex;i++){
        _dataz[i] = new double[_sizey];
        _datax[i] = -_rx + i*(2*_rx)/(_sizex-1);	//!< include the endpoints.
    }
    for(int i=0;i<_sizey;i++){
        _datay[i] = -_ry + i*(2*_ry)/(_sizey-1);	//!< include endpoints.
    }
    for(int i=0;i<_sizex;i++)
        for(int j=0;j<_sizey;j++)
            _dataz[i][j] = z[i][j];
}

//! Constructor with a given size, range and a set of z-values. Coordinates are assumed to be uniformly spaced, and field values are initialized to 0.
NumSurface::NumSurface(int sizex, double rx, int sizey, double ry)
: Surface(rx,ry), _sizex(sizex), _sizey(sizey)
{
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double*[_sizex];
    for(int i=0;i<_sizex;i++){
        _dataz[i] = new double[_sizey];
        _datax[i] = -_rx + i*(2*_rx)/(_sizex-1);	//!< include endpoints
    }
    for(int i=0;i<_sizey;i++){
        _datay[i] = -_ry + i*(2*_ry)/(_sizey-1);	//!< include endpoints
    }
    for(int i=0;i<_sizex;i++)
        for(int j=0;j<_sizey;j++)
            _dataz[i][j] = 0;
				//!< **z is not specified, therefore initialize to 0.
}

//! Copy constructor that takes in the same type. Size and the array will be both read from the rhs.
NumSurface::NumSurface(const NumSurface& f) : Surface(f._rx, f._ry)
{
    _sizex = f._sizex; _sizey = f._sizey;
				//!< read size from the NumSurface.
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double*[_sizex];
    for (int i=0;i<_sizex;i++){
        _datax[i] = f._datax[i];
        _dataz[i] = new double[_sizey];
    }
    for (int i=0;i<_sizey;i++){
        _datay[i] = f._datay[i];
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataz[i][j] = f._dataz[i][j]; //!< Performs a deep copy.
        }
    }
}

//! Copy assignment, used when modifying existing objects. If currently holds memory, must free it first.
NumSurface& NumSurface::operator=(const NumSurface& f)
{
    if(_datax!=0) delete [] _datax;	//!< if with memory, free it first.
    if(_datay!=0) delete [] _datay;
    if(_dataz!=0) delete [] _dataz;
    _sizex = f._sizex;
    _sizey = f._sizey;
    _rx = f._rx;			//!< don't forget to copy range.
    _ry = f._ry;
    _r = f._r;
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double*[_sizex];
    for (int i=0;i<_sizex;i++){
        _datax[i] = f._datax[i];
        _dataz[i] = new double[_sizey];
    }
    for (int i=0;i<_sizey;i++){
        _datay[i] = f._datay[i];
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataz[i][j] = f._dataz[i][j]; //!< Performs a deep copy.
        }
    }
    return (*this);
}

//! Constructor with a size and a Surface object. Use operator () of Surface class to initialize.
NumSurface::NumSurface(int sizex, int sizey, const Surface& f) : Surface(0,0)
{
    _sizex = sizex;
    _sizey = sizey;
    _rx = f.GetRangeX();
    _ry = f.GetRangeY();
    _r = f.GetRange();
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double*[_sizex];
    for(int i=0;i<_sizex;i++){
        _datax[i] = -_rx + i*(2*_rx)/(_sizex-1);
        _dataz[i] = new double[_sizey];
    }
    for(int i=0;i<_sizey;i++){
        _datay[i] = -_ry + i*(2*_ry)/(_sizey-1);
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataz[i][j] = f(_datax[i],_datay[j],0);
		//!< used default interpolation method.
        }
    }
}

//! Copy method. This will copy values from Surface object specified in the argument.
void NumSurface::Copy(int sizex, int sizey, const Surface& f)
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;
    if(_dataz!=0) delete [] _dataz;
    _sizex = sizex;
    _sizey  = sizey;
    _rx = f.GetRangeX();	//!< Don't forget range.
    _ry = f.GetRangeY();
    _r = f.GetRange();
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double*[_sizex];
    for(int i=0;i<_sizex;i++){
        _datax[i] = -_rx + i*(2*_rx)/(_sizex-1);
        _dataz[i] = new double[_sizey];
    }
    for(int i=0;i<_sizey;i++){
        _datay[i] = -_ry + i*(2*_ry)/(_sizey-1);
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataz[i][j] = f(_datax[i],_datay[j],0);
        }
    }
}

//! Destructor. Must delete memory allocated.
NumSurface::~NumSurface()
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;
    if(_dataz!=0) {
        for(int i=0;i<_sizex;i++) delete [] _dataz[i];
        delete [] _dataz;
    }
}

//! operator (double,double) will return values using the interpolation method used.
double NumSurface::operator()(double x, double y, Interpolator* intpl) const
{
    intpl->set_values(_sizex,_sizey,_datax,_datay,_dataz);
    return intpl->Interpolate(x,y);
}

//! operator(int,int) will retern REFERENCE to the function value at the given indexes.
double& NumSurface::operator()(int indexX, int indexY)
{
    if(indexX < 0 || indexX >_sizex-1 || indexY <0 || indexY >_sizey-1){
        fprintf(stderr,"Error: NumSurface::operator(,) index %d %d out of range.\n",indexX,indexY);
		//! print out of range error to stderror.
        indexX=0; indexY=0;
    }
    return _dataz[indexX][indexY];
}

//! Return pointer to x-coordinates for fast access.
double* NumSurface::GetXPtr()
{
    return _datax;
}

//! Return pointer to y-coordinates for fast access.
double* NumSurface::GetYPtr()
{
    return _datay;
}

//! Return pointer to z-coordinates for fast access.
double** NumSurface::GetZPtr()
{
    return _dataz;
}

int NumSurface::GetSizeX()
{
    return _sizex;
}

int NumSurface::GetSizeY()
{
    return _sizey;
}

//! Default print method. Print out function values at the nodes.
void NumSurface::Print()
{
    for(int j=_sizey-1;j>=0;j--){
        for(int i=0;i<_sizex;i++)
            printf("%.9f\t",_dataz[i][j]);
        printf("\n");
    }
}

//! Print out the surface values within the specified range.
void NumSurface::Print(double xi, double xf, int Nx, double yi, double yf, int Ny)
{

}

#ifdef USE_HDF
//! DO NOT include 'output/' in string 'file'.
void NumSurface::ExportHDF(const char* file)
{
    char fname[strlen(file)+11];
    strcpy(fname, "output/"); //!< Automatically export to directory 'output/'
    strcat(fname, file);
//! 2D array _dataz incompatible with HDF5. 1D array 'data' needed for bridging.
    double *data;
    data = new double[_sizey*_sizex];
    for (int i = 0; i<_sizex; i++){
        for (int j = 0; j<_sizey; j++){
//! The indexing is meant for consistency with python, VisIt, etc.
            data[i + j*_sizex] = _dataz[i][j];
        }
    }
//! Create file and save data
    hid_t file_id;
    hsize_t dims[Dim2];
    dims[0] = _sizey;
    dims[1] = _sizex;
    hsize_t dimx[Dim1];
    dimx[0] = _sizex;
    hsize_t dimy[Dim1];
    dimy[0] = _sizey;
    herr_t status;
    file_id = H5Fcreate(fname, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
//! Number of grids saved as attributes. Coodrinates saved as 1D arrays since the mesh is rectilinear. Data saved as 2D array.
    status = H5LTmake_dataset_double(file_id,"/x",Dim1,dimx,_datax);
    status = H5LTmake_dataset_double(file_id,"/y",Dim1,dimy,_datay);
    status = H5LTmake_dataset_double(file_id,"/data",Dim2,dims,data);
    status = H5LTset_attribute_int(file_id, "/x", "size of x", &_sizex, 1);
    status = H5LTset_attribute_int(file_id, "/y", "size of y", &_sizey, 1); 
    status = H5Fclose(file_id);
//! Clear up memory
    delete [] data;
//! Create XMDF file that accompanies HDF5 file so as to enable VisIt reading.
    strcat(fname, ".xmf"); 
    FILE *xmf = 0;
    xmf = fopen(fname, "w");
    fprintf(xmf, "<?xml version=\"1.0\" ?>\n");
    fprintf(xmf, "<!DOCTYPE Xdmf SYSTEM \"Xdmf.dtd\" []>\n");
    fprintf(xmf, "<Xdmf Version=\"2.0\">\n");
    fprintf(xmf, " <Domain>\n");
    fprintf(xmf, "   <Grid Name=\"mesh\" GridType=\"Uniform\">\n");
    fprintf(xmf, "     <Topology TopologyType=\"2DRectMesh\" NumberOfElements=\"%d %d\"/>\n", _sizey, _sizex);
    fprintf(xmf, "     <Geometry GeometryType=\"VXVY\">\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", _sizex);
    fprintf(xmf, "        %s:/x\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", _sizey);
    fprintf(xmf, "        %s:/y\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Geometry>\n");
    fprintf(xmf, "     <Attribute Name=\"data\" AttributeType=\"Scalar\" Center=\"Node\">\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", _sizey, _sizex);
    fprintf(xmf, "        %s:/data\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Attribute>\n");
    fprintf(xmf, "   </Grid>\n");
    fprintf(xmf, " </Domain>\n");
    fprintf(xmf, "</Xdmf>\n");
    fclose(xmf);
}

void NumSurface::ExportHDF(const char* file, double xi, double xf, int Nx, double yi, double yf, int Ny){}

//! Constructor from a HDF5 file.
NumSurface::NumSurface(const char* file): Surface(0, 0)
{
//! Open target file, which needs to be in the same format as the exported .h5 file: Number of grids as attributes. Coodrinates as 1D arrays since the mesh is rectilinear. Data as 2D array. 
    hid_t file_id;
    herr_t status;
    file_id = H5Fopen(file, H5F_ACC_RDONLY, H5P_DEFAULT);
//! Read in number of grids
    status = H5LTget_attribute_int(file_id, "/x", "size of x", &_sizex);
    status = H5LTget_attribute_int(file_id, "/y", "size of y", &_sizey);
//! Allocate memory
    _datax = new double[_sizex];
    _datay = new double[_sizey];
//! 2D array _dataz incompatible with HDF5. 1D array 'data' needed for bridging.
    double *data;
    data = new double[_sizey*_sizex];
//! Read in data
    status = H5LTread_dataset_double(file_id,"/x",_datax);
    status = H5LTread_dataset_double(file_id,"/y",_datay);
    status = H5LTread_dataset_double(file_id,"/data",data);
//! Move data to _dataz
    _dataz = new double*[_sizex];
    for (int i=0;i<_sizex;i++){
        _dataz[i] = new double[_sizey];
        for (int j = 0; j<_sizey; j++){
            _dataz[i][j] = data[i + j*_sizex];
        }
    }
    status = H5Fclose(file_id);
//! Clear up memory
    delete [] data;
//! Initialize ranges. 
    _rx = -_datax[0];
    _ry = -_datay[0];
    _r = sqrt(_rx*_rx+_ry*_ry);
}

#endif
