/*! \file
    \brief Abstract Image class for Two-dimensional CT images. S
*/

#ifndef IMAGE2D
#define IMAGE2D 1

#include"LineIntegral.h"
#include"Image.h"

/*!
Image2D is an Image with dimension 2. A few further functions to implement, such as integration along a line and get projections in different angles. S
*/

class Image2D : public Image{

public:

    Image2D(double,double);     //! Constructor. Argument is the length in X and Y direction. S

    virtual ~Image2D(); //! Virtual destructor, in case someone calls delete derived. S

    virtual double& operator()(double x, double y) = 0;
                        //! Returns image value at the argument point. S

    virtual void Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny) = 0;
                        //! Print out the field. S

    void SetRange(double rx, double ry); //! Sets symmetrized range in X and Y direction. S

    double GetRangeX(); //! Returns symmetrized range in X direction. S

    double GetRangeY(); //! Returns symmetrized range in Y direction. S

    double GetRadius(); //! Returns the smallest radius that would enclose the figure. S

    void GetProjection(LineIntegral* l, double angle=0, double spacing=0.1);
                        //! Given angle, spacing of lines and an integration method, performs line integral. LineIntegral method is mandatory, and angle and spacing has default parameters. Angle starts from X-axis and moves counter-clockwise. S

protected:

    double _rx;	//!< Range in X-direction. S
    double _ry; //!< Range in Y-direction. S
    double _r;	//!< Smallest radius that would enclose the XY cross-section. S
};

#endif
