#include "FilteredBackProjection.h"
#include "globals.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

NumSurface* FilteredBackProjection( ImageArray& array, int Nres, double (*kernal)(int,double))
{
    const double range = array.GetRange();

    array.ConvolveWithKernal(kernal);	// filtered
    NumSurface* rec = new NumSurface(Nres,range,Nres,range);
    int Nangle = array.GetSize();
    for(int ll=0; ll<Nangle; ll++){	// iterate over all angle of view
        double angle = array.GetAngle(ll);
        for( int i=0; i<Nres; i++){	// loop over X-coordinate
            double x = -range + i*2*range/(Nres-1);
            for( int j=0; j<Nres; j++){	// loop over y-coordinate
                double y = -range + j*2*range/(Nres-1);
                double t = x*cos(angle) + y*sin(angle);	// distance to origin for angle ll.
                (*rec)(i,j) += (array.GetFilteredCurve(ll))(t,0)*pi/Nangle; // superpose the value.
            }
        }
    }
    return rec;
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
                z[i][j] += (curves)[0](t,0)/size;
            }
    }
    NumSurface* recon = new NumSurface(Nres,range,Nres,range,z);
    for(int i=0;i<Nres;i++) delete [] z[i];
    delete [] z;
    return recon;
}

