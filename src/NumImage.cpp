/*!
  \brief
  Implements numerical images.
*/
#include"Function.h"
#include"Interpolator.h"

// Default constructor, everything to NULL.
NumFunction::NumFunction()
{
    _datax = NULL;    
    _datay = NULL;
    _size = 0;
}

// Constructor with a size input.
NumFunction::NumFunction(int size): Function(0), _size(size)
{
    _datax = NULL;
    _datay = NULL;
    _size = 0;
}

// Constructor with a given array.
NumFunction::NumFunction(int size, double* x, double* y): Function(0), _size(size)
{
    double avg = 0;		// symmetrize the given array. Center them at 0.
    for(int i=0;i<_size;i++){avg += x[i];}
    avg /= _size;
    _datax = new double[_size];
    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax = x[i]-avg;	_datay = y[i];
    }
    _r = fabs(_datax[0]) > fabs(_datax[_size-1]) ? fabs(_datax[0]) : fabs(_datax[_size-1]);
}

// Constructor with a size, a range and a set of y-values.
NumFunction::NumFunction(int size, double r, double* y): Function(r), _size(size)
{
    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datay[i] = y[i];
        _datax[i] = -_r + i*(2*_r)/(_size-1);
    }
}

// Copy constructor that takes in the same type.
NumFunction::NumFunction(const NumFunction& f)
{
    _size = f._size;
    _datax = new double[_size];    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = f._datax[i];    
        _datay[i] = f._datay[i];	// Performs a deep copy.
    }
}

// Copy assignment, used when modifying existing objects, so have to take care of memories.
NumFunction& NumFunction::operator=(const NumFunction& f)
{
    if(_datax!=NULL) delete [] _datax;
    if(_datay!=NULL) delete [] _datay;	// free memory if previously contains objects.
    _size = f._size;
    _r = f._r;
    _datax = new double[_size];    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = f._datax[i];    
        _datay[i] = f._datay[i];	// Performs a deep copy.
    }
}

// Constructor with a size and a Function object. Use operator () to initialize.
NumFunction::NumFunction(int size, Function& f)
{
    _size = size;
    _r = f._r;
    _datax = new double[_size];    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = -_r + i*(2*_r)/(_size-1);        
        _datay[i] = f(_datax[i]);	// Evaluate at _datax{} and assign the value to the new obj.
    }
}

// Assignment operator for construction.
void NumFunction::Copy(int size, const Function&)
{
    if(_datax!=NULL) delete [] _datax;
    if(_datay!=NULL) delete [] _datay;	// free memory if previously contains objects.
    _size = size;
    _datax = new double[_size];    _datay = new double[_size];
    for(int i=0;i<_size;i++){
        _datax[i] = -_r + i*(2*_r)/(_size-1);        
        _datay[i] = f(_datax[i]);	// Evaluate at _datax{} and assign the value to the new obj.
    }
}

~NumFunction()
{
    if(_datax!=NULL) delete [] _datax;
    if(_datay!=NULL) delete [] _datay;
}

double operator(double x,Interpolator* intpl)
{
    // should implement the operator with an interpolation method. Have to check if the array is symmetric or not. A better approach is to first treat as symmetric, if returns wrong position, then performs a search algorithm to determine the position.
    return intpl->Interpolate1D(x,_datax,_datay,_size);
}

double& operator(int index)
{
    if(index<0 || index>size-1) printf("Index out of range!\n");
    return _datay[index];
}

void Print()
{
    for(int i=0; i<_size; i++) printf("%.9f\t%.9f\n",_datax[i],_datay[i]);
}

void Print(double xi, double xf ,int N)
{
    double d = (xf-xi)/N;
    for(double x=xi; x<xf; x+= d) printf("%.9f\t%.9f\n",x,(*this)(x,NULL));
}

