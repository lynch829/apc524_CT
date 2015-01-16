/*!
  \brief
  Implements numerical curve.
*/
#include "NumCurve.h"
#include <stdio.h>
#include <string.h>

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
    intpl->set_values(_size,_datax,_datay);
    return intpl->Interpolate(x);
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
// DO NOT include 'output/' in string 'file'.
void NumCurve::ExportHDF(const char* file)
{
    char fname[strlen(file)+7];
    strcpy(fname, "output/"); // Automatically export to directory 'output/'
    strcat(fname, file);
// Create file and save data
    hid_t file_id;
    hsize_t dims[Dim1];
    dims[0] = _size;
    herr_t status;
    file_id = H5Fcreate(fname, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
// Number of grids is saved as an attribute, coordinates and data saved as 1D arrays.
    status = H5LTmake_dataset_double(file_id,"/x",Dim1,dims,_datax);
    status = H5LTset_attribute_int(file_id,"/x","size of x",&_size,1); 
    status = H5LTmake_dataset_double(file_id,"/data",Dim1,dims,_datay);
    status = H5Fclose(file_id);
}
// Constructor from a HDF5 file.
NumCurve::NumCurve(const char* file): Curve(0)
{
// Open target file, which needs to be in consistent format as the exported .h5 file: Number of grids as attribute. Coodrinates and data as 1D arrays. 
    hid_t file_id;
    herr_t status;
    file_id = H5Fopen(file, H5F_ACC_RDONLY, H5P_DEFAULT);
// Read in number of grids
    status = H5LTget_attribute_int(file_id, "/x", "size of x", &_size);
// Allocate memory
    _datax = new double[_size];
    _datay = new double[_size];
// Read in data
    status = H5LTread_dataset_double(file_id,"/x",_datax);
    status = H5LTread_dataset_double(file_id,"/data",_datay);
    status = H5Fclose(file_id);
// Initialize range. 
    _r = -_datax[0];
}
    
#endif
int NumCurve::GetSize()
{
    return _size;
}
