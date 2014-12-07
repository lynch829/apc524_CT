/*!
    \brief Abstract class for 3-dimensional image. S
*/
#ifndef IMAGE3D
#define IMAGE3D 1

#include"Image.h"
#include"Interpolator.h"

/*!
Volume is an Image with dimension 3. A few further functions to consider, such as projections. S
*/
class Volume : public Image{
public:
    Volume(double,double,double);      //! Constructor. Argument is the symmetrical range of each dim. S
    virtual ~Volume(); //! Virtual destructor, in case someone calls delete derived. S
    virtual double operator()(double x, double y, double z,Interpolator* intpl) = 0;
                        //! Returns image value at that integer point. S
    virtual void Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double z) = 0;
                        //! Print the cross-section at z. S
    void SetRange(double rx, double ry, double rz);//! Sets symmetrized range in X direction. S
    double GetRangeX(); //! Returns symmetrized range in X direction. S
    double GetRangeY(); //! Returns symmetrized range in Y direction. S
    double GetRangeZ(); //! Returns symmetrized range in Z direction. S
    double GetRadius(); //! Returns smallest radius that would enclose the X-Y cross-section. S
protected:
    double _rx, _ry, _rz, _r;
};
#endif

