/*!
    enum Dimension. 0, 1, 2, 3 are all possible dimensions. Define this enum to avoid passing arbitrary number. S
*/
#ifndef GLOBAL
#define GLOBAL 1

#define pi 3.14159265357
#include <stdlib.h>
enum Dimension{Dim0=0, Dim1, Dim2, Dim3};

typedef double (*f1D)(double);
typedef double (*f2D)(double,double);
typedef double (*f3D)(double,double,double);

template<typename T>
T max(T a, T b){return a>b?a:b;}

template<typename T>
T min(T a, T b){return a<b?a:b;}

double Hamming(int , double);

#endif
