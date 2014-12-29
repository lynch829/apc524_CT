#include "SimpleBackProjection.h"
#include "globals.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
template<typename T>
T max(T a, T b){return a>b?a:b;}
template<typename T>
T min(T a, T b){return a<b?a:b;}

NumSurface* SimpleBackProjection( double* angle, Curve* curve, int size, int Nres)
{
    NumCurve* curves = (NumCurve*) curve;
    double range = 0;
    for(int i = 0; i<size; i++) range = max<double>((curves)[i].GetRange(),range);

    double **z = new double*[Nres];
    for(int i=0;i<Nres;i++){
        z[i] = new double[Nres];
        for(int j=0;j<Nres;j++) z[i][j] = 0;
    }
    for(int ll=0; ll<size; ll++){
        for( int i=0; i<Nres; i++)
            for( int j=0; j<Nres; j++){
                double x = -range + i*2*range/(Nres-1);
                double y = -range + j*2*range/(Nres-1);
                double t = x*cos(angle[ll]) - y*sin(angle[ll]);
//		printf("t is:%.5f adding: %.5f\n",t,(curves)[ll](t,0));
                z[i][j] += (curves)[ll](t,0);
            }
    }
    NumSurface* recon = new NumSurface(Nres,range,Nres,range,z);
    return recon;
}

