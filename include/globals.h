/*! \file
    \brief Definitions for some constants.
*/
#ifndef GLOBAL
#define GLOBAL 1

#define pi 3.14159265357
#include <stdlib.h>

enum Dimension{Dim0=0, Dim1, Dim2, Dim3};

typedef double (*f1D)(double);			//!< 1-D function pointer.
typedef double (*f2D)(double,double);		//!< 2-D function pointer.
typedef double (*f3D)(double,double,double);	//!< 3-D function pointer.

template<typename T>
T max(T a, T b){return a>b?a:b;}

template<typename T>
T min(T a, T b){return a<b?a:b;}

double Hamming(int , double);		//!< Default convolution kernal used by filtered back-projection.

int ArryIndexFloor(double x, double* array, int size);
				//!< Find the floor index number of the double in the given array.
int ArryIndexRoof(double x, double* array, int size);
				//!< Find the roof index number of the double in the given array.
#endif
