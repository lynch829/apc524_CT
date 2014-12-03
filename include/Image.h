/*! \file
    \brief Abstract Image class for CT
*/
#ifndef IMAGE_ABSTRACT
#define IMAGE_ABSTRACT 1
/*!
    enum Dimension. 0, 1, 2, 3 are all possible dimensions.
*/
enum Dimension{Dim0 = 0, Dim1, Dim2, Dim3};
/*!
An abstract Image class should contain the following abstract virtual methods:
a function to return dimensionality.
an interpolation method that returns value at x.\\
An Image is further classified into 1D (Function), 2D and 3D.
Object in each dimension will have to implement operator()
*/
class Image{
public:
    Image(Dimension dim = Dim0);
			//! constructor. dimension by default 0.
    virtual ~Image();
			//! virtual destructor, in case someone calls delete derived.
    virtual void Print() = 0;
			//! will print out the matrix.
    Dimension GetDimension();
			//! returns the dimension of the image.
protected:
    Dimension _dim;	//! dimension of the problem, will be 1D, 2D, or 3D.
};
/*!
Function is an Image with dimension 1. A few further functions to consider, such as integration.
Class derived from this class should add more functionalities, such as integration, and interpolation for numetical functions.
*/
class Function : public Image{
public:
    Function();		//! constructor. dimension by default 0.
    virtual ~Function();//! virtual destructor, in case someone calls delete derived.
    virtual double& operator()(double x) = 0;
			//! returns image value at that integer point.
    virtual void Print(double xmin, double xmax, int N) = 0;
			//! output the function values in the range.
};
/*!
Image2D is an Image with dimension 2. A few further functions to consider, such as integration along a line and get projections in different angles.
*/
class Image2D : public Image{
public:
    Image2D();		//! constructor. dimension by default 0.
    virtual ~Image2D();	//! virtual destructor, in case someone calls delete derived.
    virtual double& operator()(double x, double y) = 0;
			//! returns image value at that integer point.
    virtual void Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny) = 0;
			//! print out the field.
};
/*!
Image3D is an Image with dimension 3. A few further functions to consider, such as projections.
*/
class Image3D : public Image{
public:
    Image3D();		//! constructor. dimension by default 0.
    virtual ~Image3D();	//! virtual destructor, in case someone calls delete derived.
    virtual double& operator()(double x, double y, double z) = 0;
			//! returns image value at that integer point.
    virtual void Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double z) = 0;
			//! print the cross-section at z
};
#endif
