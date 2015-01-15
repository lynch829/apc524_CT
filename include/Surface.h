/*! \file
    \brief Abstract Image class for Two-dimensional CT images called surface.
*/

#ifndef SURFACE
#define SURFACE 1
#include "LineIntegral.h"
#include "Image.h"
#include "Interpolator.h"
#include "NumCurve.h"

/*!
Surface is an Image with dimension 2. GetProjection() method would return either a double as the result of one particular line integral, or a reference to Curve class as the integrations along all the parallel lines.
*/

class Interpolator;	//!< Forward declaration.

class Surface : public Image{

public:
    Surface(double,double);
			//!< Constructor. Argument is the HALF-length in X and Y direction.
    Surface(double,double,double);
			//!< Constructor for Romberg Integration Method. Last argument is epsilon.
    virtual ~Surface();
			//!< Virtual destructor, in case someone calls delete derived.
    virtual double operator() (double x, double y, Interpolator* intpl=0) const = 0;
                        //!< Returns image value at the argument point.
    virtual void Print();
			//!< Implement Image::Print. Note it is another virtual function.
    virtual void Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, Interpolator* intpl = 0);
                        //!< Print out the field in the specified range.
#ifdef USE_HDF
    virtual void ExportHDF(const char*);
			//!< Implement Image::ExportHDF, though it is another virtual function.
    virtual void ExportHDF(const char*,double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, Interpolator* intpl = 0);
                        //!< Export the surface to an HDF file.
#endif

    void SetRange(double rx, double ry);
			//!< Sets symmetrized range in X and Y direction.
    double GetRangeX() const;
			//!< Returns symmetrized range in X direction.
    double GetRangeY() const;
			//!< Returns symmetrized range in Y direction.
    double GetRadius() const;
			//!< Returns the smallest radius that would enclose the figure.
    void SetIntegralStep(double epsilon);
			//!< Sets the stepsize to be used in the line integral.
    double GetIntegralStep() const;
			//!< Returns the step length of line integral.
    NumCurve GetProjection(LineIntegral* l, double angle=0, double spacing=0.01,Interpolator* intpl=0);
                        //!< Given angle, spacing of lines and an integration method, performs line integral. LineIntegral method is mandatory, and angle and spacing has default parameters. Angle starts from X-axis and moves counter-clockwise.

    double GetProjectionAtAngle(LineIntegral* l, double angle=0, double distance=0,Interpolator* intpl=0);
                        //!< Given angle, performs line integral. LineIntegral method is mandatory.Angle starts from X-axis and moves counter-clockwise.

protected:
    double _rx;
			//!< Range in X-direction.
    double _ry;
			//!< Range in Y-direction.
    double _r;
			//!< Smallest radius that would enclose the XY cross-section.
    double _step;
			//!< Integration step size in obtaining the projection.
};

#endif
