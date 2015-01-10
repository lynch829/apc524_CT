#ifndef INTERPOLATOR
#define INTERPOLATOR
#include <vector>
//#include "NumSurface.h"
//#include "NumVolume.h"

using std::vector;

/*!
    Interpolator class.
*/
class Interpolator{

public:
    Interpolator(); //!< constructor
    ~Interpolator(); //!< destructor
    virtual void set_values(int,int,double*,double*,double**)=0;  //<! set values to relevant data for NumSurface
    virtual void set_values(int,int,int,double*,double*,double*,double***) =0; //<! set values to relevant data for NumVolume
    virtual double Interpolate(double, double) = 0; //!< Interpolate method for NumSurface
    virtual double Interpolate(double, double, double) = 0; //!< Interpolate method for NumVolume
protected:
    int _sizex; //<! size in x direction
    int _sizey; //<! size in y direction
    int _sizez; //<! size in z direction (for NumVolume)
    double* _xptr; //<! pointer to x-coordinates.
    double* _yptr; //<! pointer to y-coordinates.
    double* _zptr; //<! pointer to z-coordinates.
    double** _vptr; //<! pointer to values of NumSurface object.
    double*** _wptr; //<! pointer to values of NumVolume object.
};

#endif
