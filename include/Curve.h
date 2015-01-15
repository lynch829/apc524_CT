/*! \file
    \brief Curves represent the projection of surfaces along some direction.
*/
#ifndef FUNCTION
#define FUNCTION 1

#include"Image.h"
#include"Interpolator.h"

/*!
Curve is an Image with dimension 1. This class will be used to store projection profile of surfaces/scalar fields. Such projection is defined by line integral of the scalar field along certain direction. 
A few further functions to consider, such as integration. 
Class derived from this class should add more functionalities, such as integration, and interpolation for numetical functions. Derived class could include analytical functions and numerical functions. This class is still an abstract class and there is no need for implementing copy constructors.
*/

class Interpolator;
class Curve : public Image{

public:
    Curve(double rx);//!< Constructor. Argument is the radial size of the function.
    virtual ~Curve();//!< Virtual destructor, in case someone calls delete derived.

    virtual double operator()(double x, Interpolator* intpl = 0) const = 0;
                        //!< Returns image value at the place speficied by the argument.
    virtual void Print();
			//!< Implements Image::Print. It should print the function as two columns.
    virtual void Print(double xmin, double xmax, int N=100, Interpolator* intpl = 0);
                        //!< Output the function values in the range specified.

#ifdef USE_HDF
    virtual void ExportHDF(const char*);
			//!< Implements Image::ExportHDF
    virtual void ExportHDF(const char*, double xmin, double xmax, int N=100, Interpolator* intpl = 0);
                        //!< Output the function values to a HDF5 file for later process.
#endif
    void SetRange(double rx);   //!< Set symmetrized range of independent variable. S

    double GetRange() const;          //!< Returns the symmetrized range. S

protected:
    double _r;	//!< Range of the function, same as the radius. S
};

#endif
