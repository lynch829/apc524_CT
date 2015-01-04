#include "FilteredBackProjection.h"
#include "globals.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

NumSurface* FilteredBackProjection( ImageArray& array, int Nres, double (*kernal)(int,double))
{
    // Nres is the resolution for the reconstructed surface.
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

NumVolume* FilteredBackProjection3D( ImageArray& array, int Nres,double (*kernal)(int,double))
{

}
