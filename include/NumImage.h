/*!
  \brief This file defines numerical images whose data points are defined by discrete points.
*/
#ifndef NUMIMAGE
#define NUMIMAGE 1

#include"Function.h"
#include"Image2D.h"
#include"Image3D.h"
#include"Interpolator.h"

class NumFunction : public Function{

public:
	NumFunction();		//!< Default constructor, everything null and 0.
	NumFunction(int size, double* x, double* y);	//!< Initialize with a given array.
	NumFunction(&Function);	//!< Initializes with a given Function object.
	~NumFunction();		//!< Destructor, has to delete stored data.

	NumFunction& operator=(&Function);	//!< Assignment operator.
	double& operator(double);	//!< Operator () to access values.

	void Print();	//!< Default method, print out everything as two columns.
	void Print(double,double,int);	//!< Print for a given range.

private:
	double* _datax;	//!< Y-Coordinates of the points.
	double* _datay;	//!< Y-Coordinates of the points.
	int _size;	//!< size of the array.
};

class NumImage2D : public Image2D{

};

class NumImage3D : public Image3D{

};

#endif
