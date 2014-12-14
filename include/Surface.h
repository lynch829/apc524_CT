/*! \file
    \brief Abstract Image class for Two-dimensional CT images. S
*/

#ifndef SURFACE
#define SURFACE 1
#include "NumImage.h"
#include "LineIntegral.h"
#include "Image.h"
#include "Interpolator.h"
/*!
Surface is an Image with dimension 2. GetProjection method would return either a double as the result of one particular line integral, or a reference to Curve class as the integrations along all the parallel lines. S
*/

class Surface : public Image{

public:

    Surface(double,double);     //!< Constructor. Argument is the HALF-length in X and Y direction. S
    virtual ~Surface(); //!< Virtual destructor, in case someone calls delete derived. S

    virtual double operator() (double x, double y, Interpolator* intpl=0) const = 0;
                        //!< Returns image value at the argument point. S
    virtual void Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny) = 0;
                        //!< Print out the field. S
    void SetRange(double rx, double ry); //!< Sets symmetrized range in X and Y direction. S
    double GetRangeX() const; //!< Returns symmetrized range in X direction. S
    double GetRangeY() const; //!< Returns symmetrized range in Y direction. S
    double GetRadius() const; //!< Returns the smallest radius that would enclose the figure. S

    void SetIntegralStep(); 	//!< Sets the stepsize in the line integral. S
    double GetIntegralStep() const;	//!< Returns the step length of line integral. S

    NumCurve GetProjection(LineIntegral* l, double angle=0, double spacing=0.01,Interpolator* intpl=0);
                        //!< Given angle, spacing of lines and an integration method, performs line integral. LineIntegral method is mandatory, and angle and spacing has default parameters. Angle starts from X-axis and moves counter-clockwise. S

    double GetProjectionAtAngle(LineIntegral* l, double angle=0, double distance=0,Interpolator* intpl=0);
                        //!< Given angle, performs line integral. LineIntegral method is mandatory.Angle starts from X-axis and moves counter-clockwise. S
    

protected:

    double _rx;	//!< Range in X-direction. S
    double _ry; //!< Range in Y-direction. S
    double _r;	//!< Smallest radius that would enclose the XY cross-section. S
    double _step;	//!< Integration step size in obtaining the projection. S
};

#endif
