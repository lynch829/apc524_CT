/*! \file
    \brief Abstract Image class for CT images. S
*/
#ifndef FUNCTION
#define FUNCTION 1

#include"Image.h"
#include"Interpolator.h"

/*!
Curve is an Image with dimension 1. A few further functions to consider, such as integration.
Class derived from this class should add more functionalities, such as integration, and interpolation for numetical functions. Derived class could include analytical functions and numerical functions.
This class is still an abstract class and there is no need for implementing copy constructors.
*/

class Curve : public Image{

public:

    Curve(double rx);//!< Constructor. Argument is the radial size of the function. S
    virtual ~Curve();//!< Virtual destructor, in case someone calls delete derived. S

    virtual double operator()(double x, Interpolator* intpl = 0) const = 0;
                        //!< Returns image value at the argument point. S
    virtual void Print(); //!< Implements Image::Print
    virtual void Print(double xmin, double xmax, int N=100, Interpolator* intpl = 0);
                        //!< Output the function values in the range. S

    void SetRange(double rx);   //!< Set symmetrized range of independent variable. S

    double GetRange() const;          //!< Returns the symmetrized range. S

protected:

    double _r;	//!< Range of the function, same as the radius. S

};

#endif
