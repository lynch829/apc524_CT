/*! \file
    \brief Abstract class for 3-dimensional image called Volume.
*/
#ifndef IMAGE3D
#define IMAGE3D 1

#include"Image.h"
#include"Interpolator.h"
#include"NumSurface.h"
#include"NumCurve.h"
#include"LineIntegral.h"

/*!
Volume is an Image with dimension 3. A few further functions to consider, such as projections along different angles and creating a volume from surfaces.
*/

class Volume : public Image{
public:
    Volume(double,double,double);
		//! Constructor. Argument is the symmetrical range along each dim.
    virtual ~Volume();
		//! Virtual destructor, in case someone calls delete derived.
    virtual double operator() (double x, double y, double z,Interpolator* intpl) const = 0;
		//! Returns image value at that integer point. S
    virtual void Print();
		//!< Implements Image::Print().
    virtual void Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double z, Interpolator* intpl=0);
		//!< Print the cross-section at z.

#ifdef USE_HDF
    virtual void ExportHDF(const char*);
		//!< Implements Image::ExportHDF().
    virtual void ExportHDF(const char*,double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double zmin, double zmax, int Nz, Interpolator* intpl=0);
		//!< Export the cross-section at z to an HDF5 file.
#endif

    void SetRange(double rx, double ry, double rz);
		//!< Sets symmetrized range in X direction.
    double GetRangeX() const;
		//!< Returns symmetrized range in X direction.
    double GetRangeY() const;
		//!< Returns symmetrized range in Y direction.
    double GetRangeZ() const;
		//!< Returns symmetrized range in Z direction.
    double GetRadius() const;
		//!< Returns smallest radius that would enclose the X-Y cross-section. S
    void SetIntegralStep(double epsilon);
		//!< Sets integration stepsize.
    NumSurface GetProjection3D(LineIntegral* l, double angle=0, double spacingr=0.01, double spacingz=0.01, Interpolator* intpl=0);
		//!< Given angle, spacing of lines and an integration method, performs line integral. LineIntegral method is mandatory, and angle and spacing has default parameters. Angle starts from X-axis and moves counter-clockwise.
    NumCurve GetProjection(LineIntegral* l, double angle=0, double spacingr=0.01, double z=0, Interpolator* intpl=0);
		//!< Returns the projection along a particular angle and at a particular height.
    double GetProjectionAtAngle(LineIntegral* l, double angle_arg=0, double d=0, double z=0, Interpolator* intpl=0);
		//!< Given angle, performs line integral at height z. LineIntegral method is mandatory. Angle starts from X-axis and moves counter-clockwise.

protected:
    double _rx, _ry, _rz, _r, _step;
};

#endif
