/*!
  \brief
  Implements numerical images.
*/

#include "NumSurface.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

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

//Turn NumSurface into a NumCurve object.

NumCurve NumSurface::Surface2Curve()
{
    double *y = this->_datay; double **z= this->_dataz;
    int size = this->_sizex * this->_sizey; //size of NumCurve is _sizex * _sizey
    double* datax;double* datay; //datax is x coordinate of NumCurve datay is the values of NumCurve
    datax = new double[size]; datay = new double[size];
    for(int i=0;i<this->_sizex;i++){
        for(int j=0;j<this->_sizey;j++){
            datay[j+i*this->_sizey] = z[i][j]; //put the y dimension of z in datay
            datax[j+i*this->_sizey] = y[j]; //spacingr information is given in datax
            std::cerr << "y[j] is " <<j<<" "<< y[j] <<std::endl;
        }
     }
    NumCurve ret(size, datax, datay); //construct NumCurve that is equivalent to NumSurface
    double r = fabs(y[0]) > fabs(y[this->_sizey-1]) ? fabs(y[0]) : fabs(y[this->_sizey-1]);
    ret.SetRange(r);
    std::cerr << "r is " << r <<std::endl;
    std::cerr << "size is " << size <<std::endl;
    std::cerr << "ydimension is " <<this->_sizey << std::endl;
    return ret;
    delete [] datax; delete [] datay;
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
    status = H5LTmake_dataset(file_id,"/x",Dim1,dimx,H5T_NATIVE_DOUBLE,_datax);
    status = H5LTmake_dataset(file_id,"/y",Dim1,dimy,H5T_NATIVE_DOUBLE,_datay);
    status = H5LTmake_dataset(file_id,"/data",Dim2,dims,H5T_NATIVE_DOUBLE,data);
    status = H5Fclose(file_id);
}

void NumSurface::ExportHDF(const char* file, double xi, double xf, int Nx, double yi, double yf, int Ny){}
