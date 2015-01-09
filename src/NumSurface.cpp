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
    _r = sqrt(_rx*_rx+_ry*_ry);
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
    _rx = f.GetRangeX(); _ry = f.GetRangeY(); _r = sqrt(_rx*_rx+_ry*_ry);
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
    double *y = this->GetYPtr(); double **z= this->GetZPtr();
    int size = _sizex * _sizey; //size of NumCurve is _sizex * _sizey
    double* datax;double* datay; //datax is x coordinate of NumCurve datay is the values of NumCurve
    datax = new double[size]; datay = new double[size];
    for(int i=0;i<this->_sizex;i++){
        for(int j=0;j<_sizey;j++){
            datay[j+i*_sizey] = z[i][j]; //put the y dimension of z in datay
            datax[j+i*_sizey] = y[j]; //spacingr information is given in datax
            //std::cerr << "y[j] is " <<j<<" "<< y[j] <<std::endl;
        }
     }
    NumCurve ret(size, datax, datay); //construct NumCurve that is equivalent to NumSurface
    double r = fabs(y[0]) > fabs(y[_sizey-1]) ? fabs(y[0]) : fabs(y[_sizey-1]);
    ret.SetRange(r);
    std::cerr << "r is " << r <<std::endl;
    std::cerr << "size is " << size <<std::endl;
    std::cerr << "ydimension is " <<_sizey << std::endl;
    return ret;
    delete [] datax; delete [] datay;
}
        
double NumSurface::operator()(double x, double y, Interpolator* intpl) const
{
    if(intpl==0){
        //std::cerr << "run1 "<<std::endl;
        double ret;
        int dim=2; //dimmension is 2
        double dx = 2*_rx/(_sizex-1);
        int i0x = int((x+_rx)/dx);
        int i1x = i0x+1;
        double dy = 2*_ry/(_sizey-1);
        int i0y = int((y+_ry)/dy);
        int i1y = i0y+1;
        while ( i1x < _sizex && x > _datax[i1x] ) {i0x++;i1x++;}
        while ( i1y < _sizey && y > _datay[i1y] ) {i0y++;i1y++;}
        while ( i0x>=0 && x < _datax[i0x]) {i0x--;i1x--;}	// move interval to match with given point.
        while ( i0y>=0 && y < _datay[i0y]) {i0y--;i1y--;}	// move interval to match with given point.
        if ( i1x>_sizex-1 || i0x < 0 || i1y>_sizey-1 || i0y < 0) {return 0;}
        else {
            double Q11 = _dataz[i0x][i0y];
            double Q21 = _dataz[i1x][i0y];
            double Q12 = _dataz[i0x][i1y];
            double Q22 = _dataz[i1x][i1y];
            double s1 = Q11*(_datax[i1x]-x)*(_datay[i1y]-y);
            double s2 = Q21*(x-_datax[i0x])*(_datay[i1y]-y);
            double s3 = Q12*(_datax[i1x]-x)*(y-_datay[i0y]);
            double s4 = Q22*(x-_datax[i0x])*(y-_datay[i0y]);
            ret = 1/((_datax[i1x]-_datax[i0x])*(_datay[i1y]-_datay[i0y]))*(s1+s2+s3+s4);
            return ret;
        }
    }
    else {
	    return 0;
}
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
int NumSurface::GetSizeX(){
    return _sizex;
}
int NumSurface::GetSizeY(){
    return _sizey;
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
    file_id = H5Fopen(file, H5F_ACC_RDONLY, H5P_DEFAULT);
    status = H5LTget_attribute_int(file_id, "/x", "size of x", &_sizex);
    status = H5LTget_attribute_int(file_id, "/y", "size of y", &_sizey);
    _datax = new double[_sizex];
    _datay = new double[_sizey];
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
    _rx = -_datax[0];
    _ry = -_datay[0];
    _r = sqrt(_rx*_rx+_ry*_ry);
}

#endif
