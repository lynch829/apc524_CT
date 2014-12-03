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
			//! Constructor. Dimension by default 0.
    virtual ~Image();
			//! Virtual destructor, in case someone calls delete derived.
    virtual void Print() = 0;
			//! This method will print out the matrix.
    Dimension GetDimension();
			//! Returns the dimension of the image.
protected:
    Dimension _dim;	//! Dimension of the problem, will be 1D, 2D, or 3D.
};
/*!
Function is an Image with dimension 1. A few further functions to consider, such as integration.
Class derived from this class should add more functionalities, such as integration, and interpolation for numetical functions.
*/
class Function : public Image{
public:
    Function(double rx);//! Constructor. Argument is the radial size of the function
    virtual ~Function();//! Virtual destructor, in case someone calls delete derived.
    virtual double& operator()(double x) = 0;
			//! Returns image value at that integer point.
    virtual void Print(double xmin, double xmax, int N) = 0;
			//! Output the function values in the range.
    void SetRange(double rx);	//! Set symmetrized range of independent variable.
    double GetRange();		//! Returns the symmetrized range.
protected:
    double _rx;
};
/*!
Image2D is an Image with dimension 2. A few further functions to consider, such as integration along a line and get projections in different angles.
*/
class Image2D : public Image{
public:
    Image2D(double,double);	//! Constructor. Argument is the length in X and Y direction.
    virtual ~Image2D();	//! Virtual destructor, in case someone calls delete derived.
    virtual double& operator()(double x, double y) = 0;
			//! Returns image value at that integer point.
    virtual void Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny) = 0;
			//! Print out the field.
    void SetRange(double rx, double ry); //! Sets symmetrized range in X and Y direction.
    double GetRangeX();	//! Returns symmetrized range in X direction.
    double GetRangeY();	//! Returns symmetrized range in Y direction.
    double GetRadius();	//! Returns the smallest radius that would enclose the figure.
protected:
    double _rx, _ry;
};
/*!
Image3D is an Image with dimension 3. A few further functions to consider, such as projections.
*/
class Image3D : public Image{
public:
    Image3D(double,double,double);	//! Constructor. Argument is the symmetrical range of each dim.
    virtual ~Image3D();	//! Virtual destructor, in case someone calls delete derived.
    virtual double& operator()(double x, double y, double z) = 0;
			//! Returns image value at that integer point.
    virtual void Print(double xmin, double xmax, int Nx, double ymin, double ymax, int Ny, double z) = 0;
			//! Print the cross-section at z
    void SetRange(double rx, double ry, double rz);//! Sets symmetrized range in X direction.
    double GetRangeX();	//! Returns symmetrized range in X direction.
    double GetRangeY();	//! Returns symmetrized range in Y direction.
    double GetRangeZ();	//! Returns symmetrized range in Z direction.
    double GetRadius();	//! Returns smallest radius that would enclose the X-Y cross-section.
protected:
    double _rx, _ry, _rz;
};
#endif
