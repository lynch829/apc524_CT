/*! /file
    /brief Interpolator base class.
*/
#ifndef INTERPOLATOR
#define INTERPOLATOR
#include <vector>

using std::vector;

/*!
    Interpolator class.
*/
class Interpolator{

public:
    Interpolator();
	//!< constructor
    ~Interpolator();
	//!< destructor
    void set_values(int,double*,double*);
	//<! set values to relevant data for NumCurve
    void set_values(int,int,double*,double*,double**);
	//<! set values to relevant data for NumSurface
    void set_values(int,int,int,double*,double*,double*,double***);
	//<! set values to relevant data for NumVolume
    virtual double Interpolate(double) = 0;
	//!< Interpolate method for NumCurve
    virtual double Interpolate(double, double) = 0;
	//!< Interpolate method for NumSurface
    virtual double Interpolate(double, double, double) = 0;
	//!< Interpolate method for NumVolume

protected:
    int _sizex;
	//<! size in x direction
    int _sizey;
	//<! size in y direction
    int _sizez;
	//<! size in z direction (for NumVolume)
    double* _xptr;
	//<! pointer to x-coordinates.
    double* _yptr;
	//<! pointer to y-coordinates.
    double* _zptr;
	//<! pointer to z-coordinates.
    double** _zzptr;
	//<! pointer to values of NumSurface object.
    double*** _wptr;
	//<! pointer to values of NumVolume object.
};

#endif
