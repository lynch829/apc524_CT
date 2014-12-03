#ifndef ANAIMAGE
#define ANAIMAGE 1

#include"Image.h"

typedef double (*f1D)(double);
typedef double (*f2D)(double,double);
typedef double (*f3D)(double,double,double);

/*!
  Concrete image class that uses analytical expression.
*/

class AnaImage : public Image {

public:
    AnaImage( Dimension dim, f1D);	//! constructs with R->R
    AnaImage( Dimension dim, f2D);	//! constructs with R2->R
    AnaImage( Dimension dim, f3D);	//! constructs with R3->R

    ~AnaImage();	//! destructor, does nothing.

    double& operator()(double, double, double);	//! evaluate function value.
    
    void Print();	//! Print out image, by default from -10 to 10 with spacing 0.2

private:
    f1D _f1d;	//! 1D function
    f2D _f2d;	//! 2D function
    f3D _f3d;	//! 3D function
    double var;	//! temp variable to hold return value for double& operator()
};


#endif
