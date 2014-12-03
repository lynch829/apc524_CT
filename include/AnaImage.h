#ifndef ANAIMAGE
#define ANAIMAGE 1

#include"Image.h"

typedef double (*f1D)(double);
typedef double (*f2D)(double,double);
typedef double (*f3D)(double,double,double);
/*!
  Concrete 1D image class with analytical expressions.
*/
class AnaFunction : public Function {
public:
    AnaFunction( f1D, double x );//! Constructs with R->R. X is the range of this function.
    ~AnaFunction();	//! Destructor, does nothing.
    double& operator()(double);	//! Evaluate function value and returns by reference.
    
    void Print();	//! Print out image on default range with N=200.
    void Print(double, double, int);
private:
    f1D _f1d;	//! 1D function
    double var;	//! Temp variable to hold return value for double& operator()
};
/*!
  Concrete 2D image class with analytical expressions.
*/
class AnaImage2D : public Image2D {
public:
    AnaImage2D( f2D, double, double );	//! Constructs with R2->R.
    ~AnaImage2D();	//! Destructor, does nothing.
    double& operator()(double, double);	//! Evaluate function value.
    
    void Print();	//! Print out image, on default range with N=200.
    void Print(double, double, int, double, double, int);
private:
    f2D _f2d;	//! 2D function
    double var;	//! Temp variable to hold return value for double& operator()
};
/*!
  Concrete 3D image class with analytical expressions.
*/
class AnaImage3D : public Image3D {
public:
    AnaImage3D( f3D, double, double, double );	//! constructs with R3->R
    ~AnaImage3D();	//! destructor, does nothing.
    double& operator()(double, double, double);	//! evaluate function value.
    
    void Print();	//! Print out image, on default range with N=200;
    void Print(double, double, int, double, double, int, double z=0);
private:
    f3D _f3d;	//! 3D function
    double var;	//! temp variable to hold return value for double& operator()
};
#endif
