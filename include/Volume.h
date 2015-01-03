/*!
    \brief Abstract class for 3-dimensional image. S
*/
#ifndef IMAGE3D
#define IMAGE3D 1

#include"Image.h"
#include"Interpolator.h"
#include"NumSurface.h"
#include"LineIntegral.h"

/*!
Volume is an Image with dimension 3. A few further functions to consider, such as projections. S
*/
class Volume : public Image{
public:
    Volume(double,double,double);      //! Constructor. Argument is the symmetrical range of each dim. S
    Volume(double,double,double,double);//! Constructor for Romberg Integration Method. Last argument is epsilon.
    virtual ~Volume(); //! Virtual destructor, in case someone calls delete derived. S
    virtual double operator() (double x, double y, double z,Interpolator* intpl) const = 0;
                        //! Returns image value at that integer point. S
    virtual void Print(); //!< Implements Image::Print().
    virtual void Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double z, Interpolator* intpl=0);
                        //! Print the cross-section at z. S
    void SetRange(double rx, double ry, double rz);//! Sets symmetrized range in X direction. S
    double GetRangeX() const; //! Returns symmetrized range in X direction. S
    double GetRangeY() const; //! Returns symmetrized range in Y direction. S
    double GetRangeZ() const; //! Returns symmetrized range in Z direction. S
    double GetRadius() const; //! Returns smallest radius that would enclose the X-Y cross-section. S
    void SetIntegralStep(double epsilon);
    NumSurface GetProjection(LineIntegral* l, double angle=0, double spacingr=0.01, double spacingz=0.01, Interpolator* intpl=0);    //!< Given angle, spacing of lines and an integration method, performs line integral. LineIntegral method is mandatory, and angle and spacing has default parameters. Angle starts from X-axis and moves counter-clockwise. S
    double GetProjectionAtAngle(LineIntegral* l, double angle_arg=0, double d=0, double z=0, Interpolator* intpl=0);    //!< Given angle, performs line integral at height z. LineIntegral method is mandatory.Angle starts from X-axis and moves counter-clockwise. S
protected:
    double _rx, _ry, _rz, _r, _step;
};
#endif

