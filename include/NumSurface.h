/*!
  \brief This file defines numerical images whose data points are defined by discrete points.
*/
#ifndef NUMSURFACE
#define NUMSURFACE 1

#include"Interpolator.h"
#include"Surface.h"

/*!
  This class implements the Surface abstract class with numerical points. The values are obtained by interpolation.
*/

class NumSurface : public Surface{

public:
    NumSurface();		//!< Default constructor, everything null and 0.
    NumSurface(int sizex, int sizey);	//!< Default constructor, _size set and everything else null and 0.
    NumSurface(int sizex, double* x, int sizey, double* y, double** z);	//!< Initialize with a given x,y,z array.
    NumSurface(int sizex, double rx, int sizey, double ry, double** z);	//!< Initialize with a radius and an array.
    NumSurface(int sizex, double rx, int sizey, double ry);	//!< Initialize with a radius and range.
    NumSurface(const NumSurface&);		//!< Copy constructor, same type as NumSurface.
    NumSurface& operator=(const NumSurface&);	//!< Assignment constructor for same type.
    NumSurface(int sizex, int sizey, const Surface&);	//!< Copy constr. for general Surface obj. Needs size info.
    NumSurface(const char* file); //!< constructor from hdf5 file.
    void Copy(int sizex, int sizey, const Surface&);	//!< Copy operator for general Surface, will use previous size information.
    
    ~NumSurface();		//!< Destructor, has to delete stored data.
    
    NumCurve Surface2Curve(); //!< Turn NumSurface to NumCurve. To be used in turning results of GetProjection for 3D objects to ImageArray PushBack method.
    
    double operator()(double, double, Interpolator*) const;
				//!< Operator () to access lvalues, argument double will be rounded to nearest intger and be used to access.
    double& operator()(int,int);	//!< This method can be used to set values at the integer nodes.
    
    void Print();	//!< Default method, print out everything as three columns.
    void Print(double,double,int,double,double,int);	//!< Print out image.

    double* GetXPtr();
    double* GetYPtr();
    double** GetZPtr();
#ifdef USE_HDF    
    void ExportHDF(const char*);//!< Default, export everything as three columns.
    void ExportHDF(const char*, double,double,int,double,double,int);//!< Export data in the range.
#endif
protected:
    double* _datax;	//!< X-Coordinates of the points.
    double* _datay;	//!< Y-Coordinates of the points.
    double** _dataz; //!< Z-Coordinates of the points. Since dataz will be like dataz[][], it will be double** instead of double*
    int _sizex;	//!< size of the array in x direction.
    int _sizey; //!< size of the array in y direction.
};

#endif
