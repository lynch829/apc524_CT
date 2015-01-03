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
    for(int i=0;i<_sizey;i++){avgy += x[i];}
    avgy /= _sizey;
    _datay = new double[_sizey];
    for(int i=0;i<_sizey;i++){
        _datay[i] = x[i]-avgy;
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
    for(int i=0;i<_sizex;i++)
        for(int j=0;j<_sizey;j++)
            _dataz[i][j] = 0;
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
    //printf("%.8f\n%.8f\n",x,y);
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
        printf("Index out of range"); return _dataz[0][0];
    }
    return _dataz[indexX][indexY];
}
    
    
void NumSurface::Print()
{
    for(int j=_sizey-1;j>=0;j--){
        for(int i=0;i<_sizex;i++)
            printf("%.9f\t",_dataz[i][j]);
        printf("\n");
    }
}
void NumSurface::Print(double xi, double xf, int Nx, double yi, double yf, int Ny){}
