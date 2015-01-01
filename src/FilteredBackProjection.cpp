#include "FilteredBackProjection.h"
#include "globals.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

NumSurface* FilteredBackProjection( double* angle, Curve* curve, int size, int Nres)
{
    NumCurve* curves = (NumCurve*) curve;
    double range = 0;
    for(int i = 0; i<size; i++) range = max<double>((curves)[i].GetRange(),range);

//---------------convolute with ramp filter--------------------------------------
    for(int i = 0; i<size; i++){
        double tau = 2*range/(curves[i].GetSize()-1);
        NumCurve conv = curves[i];
        for(int j=0;j<curves[i].GetSize();j++){
            conv[j] = 0;
            for(int k=j-curves[i].GetSize()+1;k<j+1;k++)
                conv[j] +=tau*Hamming(k,tau)*(curves[i])[j-k];
        }
        curves[i]=conv;
    }

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
                z[i][j] += (curves)[ll](t,0);
            }
    }
    NumSurface* recon = new NumSurface(Nres,range,Nres,range,z);
    for(int i=0;i<Nres;i++) delete [] z[i];
    delete [] z;
    return recon;
}

NumSurface* FilteredSymmetricBackProjection( double* angle, Curve* curve, int size, int Nres)
{
    NumCurve* curves = (NumCurve*) curve;
    double range = curves[0].GetRange();
    
//---------------convolute with ramp filter--------------------------------------

        double tau = 2*range/(curves[0].GetSize()-1);
        NumCurve conv = curves[0];
        for(int j=0;j<curves[0].GetSize();j++){
            conv[j] = 0;
            for(int k=j-curves[0].GetSize()+1;k<j+1;k++)
                conv[j] +=tau*Hamming(k,tau)*(curves[0])[j-k];
        }
        curves[0]=conv;

    double **z = new double*[Nres];
    for(int i=0;i<Nres;i++){
        z[i] = new double[Nres];
        for(int j=0;j<Nres;j++) z[i][j] = 0;
    }

    for(int ll=0; ll<size; ll++){
        double angl = 0 + ll*pi/(size-1);
        for( int i=0; i<Nres; i++)
            for( int j=0; j<Nres; j++){
                double x = -range + i*2*range/(Nres-1);
                double y = -range + j*2*range/(Nres-1);
                double t = x*cos(angl) - y*sin(angl);
                z[i][j] += (curves)[0](t,0);
            }
    }
    NumSurface* recon = new NumSurface(Nres,range,Nres,range,z);
    for(int i=0;i<Nres;i++) delete [] z[i];
    delete [] z;
    return recon;
}

