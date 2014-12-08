#ifndef ANAIMAGE
#define ANAIMAGE 1

#include "Image.h"
#include "Curve.h"
#include "Surface.h"
#include "Volume.h"
#include "Interpolator.h"
#include "globals.h"

/*!
  Concrete 1D image class with analytical expressions. It is defined on a domain of radius given as the second argument of constructor.
*/
class AnaCurve : public Curve {
public:
    AnaCurve( f1D, double range );//!< Constructs with R->R. X is the range of this function.
    ~AnaCurve();	//!< Destructor, does nothing.

    double operator()(double, Interpolator*) const;	//!< Evaluate function value and returns by reference.    
    void Print();	//!< Print out image on default range with N=200.
    void Print(double, double, int);

private:
    f1D _f1d;	//!< 1D function
};

/*!
  Concrete 2D image class with analytical expressions.
*/
class AnaSurface : public Surface {
public:
    AnaSurface( f2D, double, double );	//! Constructs with R2->R.
    ~AnaSurface();	//! Destructor, does nothing.
    double operator()(double, double, Interpolator*) const;	//! Evaluate function value.
    
    void Print();	//! Print out image, on default range with N=200.
    void Print(double, double, int, double, double, int);
private:
    f2D _f2d;	//! 2D function
};

/*!
  Concrete 3D image class with analytical expressions.
*/
class AnaVolume : public Volume {
public:
    AnaVolume( f3D, double, double, double );	//! constructs with R3->R
    ~AnaVolume();	//! destructor, does nothing.
    double operator()(double, double, double, Interpolator*) const;	//! evaluate function value.
    
    void Print();	//! Print out image, on default range with N=200;
    void Print(double, double, int, double, double, int, double z=0);
private:
    f3D _f3d;	//! 3D function
};
#endif
