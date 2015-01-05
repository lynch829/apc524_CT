/*!
  \brief
  Implements numerical images.
*/

#include "NumSurface.h"
#include <stdio.h>

//! Default constructor, everything to Null
NumSurface::NumSurface() : Surface(0,0)
{
    _datax = 0;
    _datay = 0;
    _dataz = 0;
    _sizex = 0;
    _sizey = 0;
}

//! Constructor with a size input.
NumSurface::NumSurface(int sizex, int sizey): Surface(0,0), _sizex(sizex), _sizey(sizey)
{
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double*[_sizex];
    for(int i=0;i<_sizex;i++) _dataz[i] = new double[_sizey];
}

//! Constructor with a given array.
NumSurface::NumSurface(int sizex, double* x, int sizey, double* y, double** z)
: Surface(0,0), _sizex(sizex), _sizey(sizey)
{
    double avgx = 0;		// x-direction, symmetrize the given array. Center them at 0.
    for(int i=0;i<_sizex;i++){avgx += x[i];}
    avgx /= _sizex;
    _datax = new double[_sizex]; _dataz = new double*[_sizex];
    for(int i=0;i<_sizex;i++){
        _datax[i] = x[i]-avgx; _dataz[i] = new double[_sizey];
    }
    double avgy = 0;		// y-direction,symmetrize the given array. Center them at 0.
    for(int i=0;i<_sizey;i++){avgy += y[i];}
    avgy /= _sizey;
    _datay = new double[_sizey];
    for(int i=0;i<_sizey;i++){
        _datay[i] = y[i]-avgy;
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataz[i][j] = z[i][j];
        }
    }
    _rx = fabs(_datax[0]) > fabs(_datax[_sizex-1]) ? fabs(_datax[0]) : fabs(_datax[_sizex-1]);
    _ry = fabs(_datay[0]) > fabs(_datay[_sizey-1]) ? fabs(_datay[0]) : fabs(_datay[_sizey-1]);
}

// Constructor with a given size, range and a set of z-values
NumSurface::NumSurface(int sizex, double rx, int sizey, double ry, double** z)
: Surface(rx,ry), _sizex(sizex), _sizey(sizey)
{
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double*[_sizex];
    for(int i=0;i<_sizex;i++){
        _dataz[i] = new double[_sizey];
        _datax[i] = -_rx + i*(2*_rx)/(_sizex-1);
    }
    for(int i=0;i<_sizey;i++){
        _datay[i] = -_ry + i*(2*_ry)/(_sizey-1);
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataz[i][j] = z[i][j];
        }
    }
}

// Constructor with a given size, range and a set of z-values
NumSurface::NumSurface(int sizex, double rx, int sizey, double ry)
: Surface(rx,ry), _sizex(sizex), _sizey(sizey)
{
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double*[_sizex];
    for(int i=0;i<_sizex;i++){
        _dataz[i] = new double[_sizey];
        _datax[i] = -_rx + i*(2*_rx)/(_sizex-1);
    }
    for(int i=0;i<_sizey;i++){
        _datay[i] = -_ry + i*(2*_ry)/(_sizey-1);
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataz[i][j] = 0;
        }
    }
}

// Copy constructor that takes in the same type.
NumSurface::NumSurface(const NumSurface& f) : Surface(f._rx, f._ry)
{
    _sizex = f._sizex; _sizey = f._sizey;
    _datax = new double[_sizex]; _datay = new double[_sizey];
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
            _dataz[i][j] = f._dataz[i][j]; // Performs a deep copy.
        }
    }
}

//Copy assignment, used when modifying existing objects.
NumSurface& NumSurface::operator=(const NumSurface& f)
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;
    if(_dataz!=0) delete [] _dataz;
    _sizex = f._sizex; _sizey = f._sizey;
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
            _dataz[i][j] = f._dataz[i][j]; // Performs a deep copy.
        }
    }
    return (*this);
}
// Constructor with a size and a Surface object. Use operator () to initialize.
NumSurface::NumSurface(int sizex, int sizey, const Surface& f) : Surface(0,0)
{
    _sizex = sizex;
    _sizey = sizey;
    _rx = f.GetRangeX(); _ry = f.GetRangeY();
    _datax = new double[_sizex]; _datay = new double[_sizey];
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
// Assignment operator for construction.
    void NumSurface::Copy(int sizex, int sizey, const Surface& f)
    {
        if(_datax!=0) delete [] _datax;
        if(_datay!=0) delete [] _datay;
        if(_dataz!=0) delete [] _dataz;
        _sizex = sizex; _sizey  = sizey;
        _rx = f.GetRangeX(); _ry = f.GetRangeY();
        _datax = new double[_sizex]; _datay = new double[_sizey];
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
        
NumSurface::~NumSurface()
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;
    if(_dataz!=0) {
        for(int i=0;i<_sizex;i++) delete [] _dataz[i];
        delete [] _dataz;
    }
}
        
double NumSurface::operator()(double x, double y, Interpolator* intpl) const
{
    int dim=2; //dimmension is 2
    vector<double> x_in; x_in.resize(dim);
    x_in[1]=x ;x_in[2]=y; // set coordinate to be interpolated at
    int* size_in; //set size of data in each dimension.
    size_in = new int[dim];
    size_in[0] = _sizex; size_in[1] = _sizey;
    int size = size_in[0]; //size is the maximum of size in all dimensions
    for(int i=0;i<dim;i++){
        if(size > size_in[i]) size = size_in[i];
    }
    
    double** datax_in; // get the existing coordinates
    datax_in = new double*[dim];
    for (int i=0;i<dim;i++){
        datax_in[i] = new double[size];
    }
    for (int i=0;i<_sizex;i++){
        datax_in[0][i]=_datax[i];
    }
    for (int i=0;i<_sizey;i++){
        datax_in[1][i]=_datay[i];
    }
    
    double* fx_in; //set given values on original coord.
    fx_in = new double[_sizex*_sizey];
    for(int j=0;j<_sizey;j++){
        for(int i=0;i<_sizex;i++) {
            fx_in[i+j*_sizex] = _dataz[i][j];
        }
    }
    double ret = intpl->Interpolate(x_in,datax_in,fx_in,size_in,dim); //return interpolated result
    delete [] fx_in; //delete memory allocation
    delete [] size_in;
    for (int i=0;i<dim;i++){
        for (int j=0;j<size;j++){
            delete [] datax_in[i];
        }
    }
    delete [] datax_in;
    return ret;
}

double& NumSurface::operator()(int indexX, int indexY)
{
    if(indexX < 0 || indexX >_sizex-1 || indexY <0 || indexY >_sizey-1){
        fprintf(stderr,"Error: NumSurface::operator(,) index %d %d out of range.\n",indexX,indexY);
        indexX=0; indexY=0;
    }
    return _dataz[indexX][indexY];
}

double* NumSurface::GetXPtr(){
    return _datax;
}

double* NumSurface::GetYPtr(){
    return _datay;
}

double** NumSurface::GetZPtr(){
    return _dataz;
}

void NumSurface::Print()
{
    for(int j=_sizey-1;j>=0;j--){
        for(int i=0;i<_sizex;i++)
            printf("%.9f\t",_dataz[i][j]);
        printf("\n");
    }
}

void NumSurface::Print(double xi, double xf, int Nx, double yi, double yf, int Ny)
{

}
#ifdef USE_HDF
void NumSurface::ExportHDF(const char* file)
{
    double data[_sizex*_sizey];
    for (int i = 0; i<_sizex; i++){
        for (int j = 0; j<_sizey; j++){
            data[i*_sizey + j] = _dataz[i][j];
        }
    }
    hid_t file_id;
    hsize_t dims[Dim2];
    dims[0] = _sizex;
    dims[1] = _sizey;
    hsize_t dimx[Dim1];
    dimx[0] = _sizex;
    hsize_t dimy[Dim1];
    dimy[0] = _sizey;
    herr_t status;
    file_id = H5Fcreate(file, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    status = H5LTmake_dataset_double(file_id,"/x",Dim1,dimx,_datax);
    status = H5LTset_attribute_int(file_id, "/x", "size of x", &_sizex, 1);
    status = H5LTmake_dataset_double(file_id,"/y",Dim1,dimy,_datay);
    status = H5LTset_attribute_int(file_id, "/y", "size of y", &_sizey, 1);
    status = H5LTmake_dataset_double(file_id,"/data",Dim2,dims,data);
    status = H5Fclose(file_id);
}

void NumSurface::ExportHDF(const char* file, double xi, double xf, int Nx, double yi, double yf, int Ny){}

// Constructor from a HDF5 file.
NumSurface::NumSurface(const char* file): Surface(0, 0)
{
    hid_t file_id;
    herr_t status;
    int _sizex, _sizey;
    file_id = H5Fopen(file, H5F_ACC_RDONLY, H5P_DEFAULT);
    status = H5LTget_attribute_int(file_id, "/x", "size of x", &_sizex);
    status = H5LTget_attribute_int(file_id, "/y", "size of y", &_sizey);
    double _datax[_sizex], _datay[_sizey];
    double data[_sizex*_sizey];
    status = H5LTread_dataset_double(file_id,"/x",_datax);
    status = H5LTread_dataset_double(file_id,"/y",_datay);
    status = H5LTread_dataset_double(file_id,"/data",data);
    _dataz = new double*[_sizex];
    for (int i=0;i<_sizex;i++){
        _dataz[i] = new double[_sizey];
        for (int j = 0; j<_sizey; j++){
            _dataz[i][j] = data[i*_sizey + j];
        }
    }
    status = H5Fclose(file_id);
}

#endif
