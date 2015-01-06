/*!
  \brief This file defines numerical images whose data points are defined by discrete points.
*/
#ifndef NUMVOLUME
#define NUMVOLUME 1

#include"Interpolator.h"
#include"Volume.h"

/*!
  This class implements the Surface abstract class with numerical points. The values are obtained by interpolation.
*/

class NumVolume: public Volume{

public:
    NumVolume();		//!< Default constructor, everything null and 0.
    NumVolume(int sizex, int sizey, int sizez);	//!< Default constructor, _size set and everything else null and 0.
    NumVolume(int sizex, double* x, int sizey, double* y, int sizez, double*z, double*** w);	//!< Initialize with a given x,y,z array.
    NumVolume(int sizex, double rx, int sizey, double ry, int sizez, double rz, double*** w);	//!< Initialize with a radius and an array.
    NumVolume(int sizex, double rx, int sizey, double ry, int sizez, double rz);		//!< Initialize with a radius. W unknown.

    NumVolume(const NumVolume&);		//!< Copy constructor, same type as NumVolume.
    NumVolume& operator=(const NumVolume&);	//!< Assignment constructor for same type.

    NumVolume(int sizex, int sizey, int sizez, const Volume&);	//!< Copy constr. for general Surface obj. Needs size info.
    void Copy(int sizex, int sizey, int sizez, const Volume&);	//!< Copy operator for general Surface, will use previous size information.
    
    ~NumVolume();		//!< Destructor, has to delete stored data.
    
    double operator()(double, double, double, Interpolator*) const;
				//!< Operator () to access lvalues, argument double will be rounded to nearest intger and be used to access.
    double& operator()(int,int,int);	//!< This method can be used to set values at the integer nodes.
    
    void Print();	//!< Default method, print out everything as three columns.
    void Print(double,double,int,double,double,int);	//!< Print out image in the specified range.

    double* GetXPtr();	//!< Return a pointer to x coordinates.
    double* GetYPtr();	//!< Return a pointer to y coordinates.
    double* GetZPtr();	//!< Return a pointer to z coordinates.
    double*** GetWPtr();	//!< Return a pointer containing the data.

#ifdef USE_HDF    
    void ExportHDF(const char*);//!< Default, export everything as three columns.
    void ExportHDF(const char*, double,double,int,double,double,int);//!< Export data in the range.
#endif
    
protected:
    double* _datax;	//!< X-Coordinates of the points.
    double* _datay;	//!< Y-Coordinates of the points.
    double* _dataz;	//!< Z-Coordinates of the points.
    double*** _dataw;	//!< dataw is a 3D array.
    int _sizex;	//!< size of the array in x direction.
    int _sizey; //!< size of the array in y direction.
    int _sizez; //!< size of the array in z direction.
};
#endif
