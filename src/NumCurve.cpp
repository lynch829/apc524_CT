/*!
  \brief
  Implements numerical curve.
*/
#include "NumCurve.h"
#include <stdio.h>

// Default constructor, everything to NULL.
NumCurve::NumCurve() : Curve(0)
{
    _datax = 0;    
    _datay = 0;
    _size = 0;
}

// Constructor with a size input.
NumCurve::NumCurve(int size): Curve(0), _size(size)
{
    _datax = new double[_size];
    _datay = new double[_size];
    for(int i=0;i<size;i++){
        _datax[i]=0; _datay[i]=0;
    }
}
// Constructor with a size and a range.
NumCurve::NumCurve(int size, double r): Curve(r), _size(size)
{
    _datax = new double[_size];
    _datay = new double[_size];
    for(int i=0;i<size;i++){
        _datax[i]=-r+i*(2*r)/size;
        _datay[i]=0;
    }
}

// Constructor with a given array.
NumCurve::NumCurve(int size, double* x, double* y): Curve(0), _size(size)
{
        double avg = 0;		// symmetrize the given array. Center them at 0.
    for(int i=0;i<_size;i++){avg += x[i];}
    avg /= _size;
    _datax = new double[_size];
    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = x[i]-avg;	_datay[i] = y[i];
    }
    _r = fabs(_datax[0]) > fabs(_datax[_size-1]) ? fabs(_datax[0]) : fabs(_datax[_size-1]);
}

// Constructor with a size, a range and a set of y-values.
NumCurve::NumCurve(int size, double r, double* y): Curve(r), _size(size)
{
    _datax = new double[_size];
    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datay[i] = y[i];
        _datax[i] = -_r + i*(2.0*_r)/(_size-1);	// convention: 0th point is -r, (n-1)th point is r. Includes both end-points.
    }
}

// Copy constructor that takes in the same type.
NumCurve::NumCurve(const NumCurve& f) : Curve(f._r)
{
    _size = f._size;
    _datax = new double[_size];    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = f._datax[i];    
        _datay[i] = f._datay[i];	// Performs a deep copy.
    }
}

// Copy assignment, used when modifying existing objects, so have to take care of memories.
NumCurve& NumCurve::operator=(const NumCurve& f)
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;	// free memory if previously contains objects.
    _size = f._size;
    _r = f._r;
    _datax = new double[_size];    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = f._datax[i];    
        _datay[i] = f._datay[i];	// Performs a deep copy.
    }
    return (*this);
}

// Constructor with a size and a Curve object. Use operator () to initialize.
NumCurve::NumCurve(int size, const Curve& f) : Curve(0)
{
    _size = size;
    _r = f.GetRange();
    _datax = new double[_size];    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = -_r + i*(2*_r)/(_size-1);        
        _datay[i] = f(_datax[i],0);	// Evaluate at _datax{} and assign the value to the new obj.
    }
}

// Assignment operator for construction.
void NumCurve::Copy(int size, const Curve& f)
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;	// free memory if previously contains objects.
    _size = size; _r = f.GetRange();
    _datax = new double[_size];    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = -_r + i*(2*_r)/(_size-1);        
        _datay[i] = f(_datax[i]);	// Evaluate at _datax{} and assign the value to the new obj.
    }
}

NumCurve::~NumCurve()
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;
}

double NumCurve::operator()(double x, Interpolator* intpl) const
{

    if(intpl==0){
        double d = 2*_r/(_size-1);
        int i0 = int((x+_r)/d);	// recall An = A0 + i*d
        int i1 = i0 +1;
        while ( i1 < _size && x > _datax[i1] ) {i0++;i1++;}
        while ( i0>=0 && x < _datax[i0]) {i0--;i1--;}	// move interval to match with given point.
        if ( i1>_size-1 || i0 < 0 ) return 0;
        else return _datay[i0]+(_datay[i1]-_datay[i0])*(x-_datax[i0])/d;
    }

    else{
        int dim=1; //dimension is 1
        vector<double> x_in(dim,x); //set coord. to be interpolated at
        double** datax_in; //set original coord. to be searched for
        datax_in = new double*[dim];
        for(int i=0;i<dim;i++){
            datax_in[i] = new double[_size];
        }
        for(int i=0;i<dim;i++){
            for(int j=0;j<_size;j++){
                datax_in[i][j] = _datax[j];
            }
        }
        double* fx_in; //set given values on original coord.
        fx_in = new double[_size];
        for(int i=0;i<_size;i++){
            fx_in[i] = _datay[i];
        }
        int* size_in; //set size of data in each dimension.
        size_in = new int[dim];
        for(int i=0;i<_size;i++){
            size_in[i] =_size;
        }
        double ret = intpl->Interpolate(x_in,datax_in,fx_in,size_in,dim); //return interpolated result
    
        delete [] fx_in; //delete memory allocation
        delete [] size_in;
        for (int i=0;i<dim;i++){
            for (int j=0;j<_size;j++){
                 delete [] datax_in[i];
            }
        }
        delete [] datax_in;
        return ret;
    }
}

double& NumCurve::operator[](int index)
{
    if(index<0 || index>_size-1){
        fprintf(stderr,"Error: NumCurve::operator[] index %d out of range (%d,%d)\n",index,0,_size-1);
        index = 0;
    }
    return _datay[index];
}

double& NumCurve::operator()(int index)
{
    if(index<0 || index>_size-1){
        fprintf(stderr,"Error: NumCurve::operator[] index %d out of range (%d,%d)\n",index,0,_size-1);
        index = 0;
    }
    return _datay[index];
}

double* NumCurve::GetXPtr()
{
    return _datax;
}

double* NumCurve::GetYPtr()
{
    return _datay;
}

void NumCurve::Print()
{
    for(int i=0; i<_size; i++) printf("%.9f %.9f\n",_datax[i],_datay[i]);
}
#ifdef USE_HDF
void NumCurve::ExportHDF(const char* file)
{
    hid_t file_id;
    hsize_t dims[Dim1];
    dims[0] = _size;
    herr_t status;
    file_id = H5Fcreate(file, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    status = H5LTmake_dataset_double(file_id,"/x",Dim1,dims,_datax);
    status = H5LTset_attribute_int(file_id,"/x","size of x",&_size,1);
    status = H5LTmake_dataset_double(file_id,"/data",Dim1,dims,_datay);
    status = H5Fclose(file_id);
}
// Constructor from a HDF5 file.
NumCurve::NumCurve(const char* file): Curve(0)
{
    hid_t file_id;
    herr_t status;
    file_id = H5Fopen(file, H5F_ACC_RDONLY, H5P_DEFAULT);
    status = H5LTget_attribute_int(file_id, "/x", "size of x", &_size);
    _datax = new double[_size];
    _datay = new double[_size];
    status = H5LTread_dataset_double(file_id,"/x",_datax);
    status = H5LTread_dataset_double(file_id,"/data",_datay);
    status = H5Fclose(file_id);
}
    
#endif
int NumCurve::GetSize()
{
    return _size;
}
