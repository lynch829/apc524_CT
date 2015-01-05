#include "FilteredBackProjection.h"
#include "globals.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

NumSurface* FilteredBackProjection( ImageArray& array, int Nres, double (*kernal)(int,double))
{
    //! Nres is the resolution for the reconstructed surface.
    const double range = array.GetRange();

    array.ConvolveWithKernal(kernal);	// Array filters each curve with the kernal.
    std::cerr<<"FBP: Convolution done."<<std::endl;
    NumSurface* rec = new NumSurface(Nres,range,Nres,range);	// NumSurface to store the reconstructed obj.
    int Nangle = array.GetSize();
    for(int ll=0; ll<Nangle; ll++){	// Iterate over all angle of view
        double angle = array.GetAngle(ll);
        for( int i=0; i<Nres; i++){	// Loop over X-coordinates of final surface.
            double x = -range + i*2*range/(Nres-1);
            for( int j=0; j<Nres; j++){	// Loop over y-coordinate of final surface.
                double y = -range + j*2*range/(Nres-1);
                double t = x*cos(angle) + y*sin(angle);	// Distance from (x,y) to origin at angle ll.
                (*rec)(i,j) += (array.GetFilteredCurve(ll))(t,0)*pi/Nangle; // Superpose all values, assuming uniform grid.
            }
        }
    }
    return rec;
}

NumVolume* FilteredBackProjection3D( ImageArray& array, int Nres,double (*kernal)(int,double))
{
    const double range = array.GetRange(); // This is the same as 2D since we are considering slice by slice.
    const double rangeZ = array.GetRangeZ(); // This is the maximum domain height.
    //std::cerr << "range is " << range <<std::endl;
    //std::cerr << "rangeZ is " << rangeZ<<std::endl;

    int Nslice = array.GetSlice(); // Nslice is the slice number of horizontal slice.
    std::cerr << "FBP: Nslice is " << Nslice<<std::endl;
    array.ConvolveWithKernal(kernal); // Filter each projection with kernal.
    std::cerr << "FBP: Convolution done" << std::endl;

    NumVolume* rec = new NumVolume(Nres,range,Nres,range,Nslice,rangeZ,w);
    double*** w = rec->GetWPtr();

    int Nangle = array.GetSize(); // Nangle is slice*size number of angle views
    int NviewPerslice = Nangle/Nslice; // NviewPerslice is the total number of angle view per slice. Assuming each slice has the same number of angle view for now.
    for(int k=0;k<Nslice;k++){ // Iterate over number of horizontal slice
        for(int ll=0; ll<NviewPerslice; ll++){ // Iterate over angle of view per slice
            double angle = array.GetAngle(ll+k*NviewPerslice);
            for( int i=0; i<Nres; i++){	// Loop over X-coordinate
                double x = -range + i*2*range/(Nres-1);
                for( int j=0; j<Nres; j++){	// Loop over y-coordinate
                    double y = -range + j*2*range/(Nres-1);
                    double t = x*cos(angle) + y*sin(angle);	// distance to origin for angle ll.
                    w[i][j][k] += (array.GetFilteredCurve(ll))(t,0)*pi/Nangle; // superpose the value, assuming uniform grid.
                }
            }
        }
    } 
    return rec;
}
