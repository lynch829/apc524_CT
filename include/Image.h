/*! \file
    \brief Abstract Image class for CT
*/

#ifndef IMAGE_ABSTRACT
#define IMAGE_ABSTRACT 1

/*!
    enum Dimension. 0, 1, 2, 3 are all possible dimension.
*/
enum Dimension{Dim0 = 0, Dim1, Dim2, Dim3};

/*!
    An abstract Image class should contain the following abstract virtual methods:
    return dimensionality.
    an interpolation method that returns value at x.

*/

class Image{

public:
    Image(Dimension dim=Dim0);
			//! constructor. dimension by default 0.
    virtual ~Image();
			//! virtual destructor, in case someone calls delete derived.
    virtual double& operator()(double x=0, double y=0, double z=0) = 0;
			//! returns image value at that integer point.
    virtual void Print() = 0;
			//! will print out the matrix.
    Dimension GetDimension();
			//! returns the dimension of the image.
protected:
    Dimension _dim;	//! dimension of the problem, will be 1D, 2D, or 3D.
    int _lenx;	//! length in x-direction.
    int _leny;	//! length in y-direction.
    int _lenz;	//! length in z-direction.
};

#endif
