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
                (*rec)(i,j) += (array.GetFilteredCurve(ll))(t,0)*pi/Nangle; // superpose the value, assuming uniform grid.
            }
        }
    }
    return rec;
}

NumVolume* FilteredBackProjection3D( ImageArray& array, int Nres,double (*kernal)(int,double))
{
    const double range = array.GetRange(); //this is the same as 2D since we are considering slice by slice
    const double rangeZ = array.GetRangeZ(); // this is the maximum domain height.
    //std::cerr << "range is " << range <<std::endl;
    //std::cerr << "rangeZ is " << rangeZ<<std::endl;

    int Nslice = array.GetSlice(); //Nslice is the slice number of horizontal slice
    std::cerr << "Nslice is " << Nslice<<std::endl;
    array.ConvolveWithKernal(kernal); //filtered
    std::cerr << "convolution done" << std::endl;
    double*** w;
    w = new double**[Nres];
    for(int i=0;i<Nres;i++){
        w[i] = new double*[Nres];
        for(int j=0;j<Nres;j++){
            w[i][j] = new double[Nslice];
        }
    }
    int Nangle = array.GetSize(); //Nangle is slice*size number of angle views
    int NviewPerslice = Nangle/Nslice; // NviewPerslice is the total number of angle view per slice. Assuming each slice has the same number of angle view for now.
    for(int k=0;k<Nslice;k++){ //iterate over number of horizontal slice
        for(int ll=0; ll<NviewPerslice; ll++){ // iterate over angle of view per slice
            double angle = array.GetAngle(ll+k*NviewPerslice);
            for( int i=0; i<Nres; i++){	// loop over X-coordinate
                double x = -range + i*2*range/(Nres-1);
                for( int j=0; j<Nres; j++){	// loop over y-coordinate
                    double y = -range + j*2*range/(Nres-1);
                    double t = x*cos(angle) + y*sin(angle);	// distance to origin for angle ll.
                    w[i][j][k] += (array.GetFilteredCurve(ll))(t,0)*pi/Nangle; // superpose the value, assuming uniform grid.
                }
            }
        }
    }
   NumVolume* rec = new NumVolume(Nres,range,Nres,range,Nslice,rangeZ,w);
   for (int i = 0; i < Nres; ++i) {
        for (int j = 0; j < Nres; ++j)
            delete [] w[i][j];
        delete [] w[i];
    }
    delete [] w;
    return rec;
}
