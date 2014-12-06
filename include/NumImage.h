/*!
  \brief This file defines numerical images whose data points are defined by discrete points.
*/
#ifndef NUMIMAGE
#define NUMIMAGE 1

#include"Function.h"
#include"Image2D.h"
#include"Image3D.h"
#include"Interpolator.h"

/*!
  This class implements the Function abstract class with numerical points. The values are obtained by interpolation.
*/

class NumFunction : public Function{

public:
	NumFunction();		//!< Default constructor, everything null and 0.
	NumFunction(int size);	//!< Default constructor, _size set and everything else null and 0.
	NumFunction(int size, double* x, double* y);	//!< Initialize with a given x and y array.
	NumFunction(int size, double r, double* y);	//!< Initialize with a radius and an array.
	NumFunction(const NumFunction&);		//!< Copy constructor, same type as NumFunction.
	NumFunction& operator=(const Function&);	//!< Assignment constructor for same type.
	NumFunction(int size, const Function&);	//!< Copy constr. for general Function obj. Needs size info.
	void Copy(int size, const Function&);	//!< Copy operator for general Function, will use previous size information.

	~NumFunction();		//!< Destructor, has to delete stored data.

	double operator(double, Interpolator*);
				//!< Operator () to access lvalues, argument double will be rounded to nearest intger and be used to access.
	double& operator(int);	//!< This method can be used to set values at the integer nodes.

	void Print();	//!< Default method, print out everything as two columns.
	void Print(double,double,int);	//!< Print for a given range.

protected:
	double* _datax;	//!< Y-Coordinates of the points.
	double* _datay;	//!< Y-Coordinates of the points.
	int _size;	//!< size of the array.
};

class NumImage2D : public Image2D{

};

class NumImage3D : public Image3D{

};

#endif
