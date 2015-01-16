#include "FilteredBackProjection.h"
#include "Bilinear.h"
#include "globals.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

NumSurface* FilteredBackProjection( ImageArray& array, int Nres, double (*kernal)(int,double))
{
    //! Nres is the resolution for the reconstructed surface.
    const double range = array.GetRange();
    Bilinear bilin;
    array.ConvolveWithKernal(kernal);	// Array filters each curve with the kernal.
    std::cerr<<"FBP: Convolution done."<<std::endl;
    NumSurface* rec = new NumSurface(Nres,range,Nres,range);	// NumSurface to store the reconstructed obj.
    int Nangle = array.GetSize();
    std::cerr<<"Size is."<< Nangle <<std::endl;
    for(int ll=0; ll<Nangle; ll++){	// Iterate over all angle of view
        double angle = array.GetAngle(ll);
        std::cerr<<"Angle is."<< angle <<std::endl;
        for( int i=0; i<Nres; i++){	// Loop over X-coordinates of final surface.
            double x = -range + i*2*range/(Nres-1);
            for( int j=0; j<Nres; j++){	// Loop over y-coordinate of final surface.
                double y = -range + j*2*range/(Nres-1);
                double t = x*cos(angle) + y*sin(angle);	// Distance from (x,y) to origin at angle ll.
                //std::cerr<<"t is."<< t <<" "<<i<<" "<<j<< "range is "<< range<<std::endl;
                (*rec)(i,j) += (array.GetFilteredCurve(ll))(t,&bilin)*pi/Nangle; // Superpose all values, assuming uniform grid.
            }
        }
        std::cerr<<"running" <<std::endl;
//        #ifdef USE_HDF
//        char file[100]; sprintf(file,"output/batman_rec%d.h5",ll);
//        rec->ExportHDF(file);
//        #endif
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

    NumVolume* rec = new NumVolume(Nres,range,Nres,range,Nslice,rangeZ);
    double*** w = rec->GetWPtr();
    std::cerr << "run1" <<std::endl;
    int Nangle = array.GetSize(); // Nangle is slice*size number of angle views
    std::cerr <<"Nangle" << Nangle << std::endl;
    int NviewPerslice = Nangle/Nslice; // NviewPerslice is the total number of angle view per slice. Assuming each slice has the same number of angle view for now.
    std::cerr <<"Nviewperslice" << NviewPerslice << std::endl;
    double sum[Nres][Nres];
    for(int k=0;k<Nslice;k++){ //iterate over number of horizontal slice
        for(int i=0;i<Nres;i++){
            for(int j=0;j<Nres;j++){
                sum[i][j] =0;
            }
        }
        for(int ll=0; ll<NviewPerslice; ll++){ // iterate over angle of view per slice
            double angle = array.GetAngle(ll+k*NviewPerslice);
            for( int i=0; i<Nres; i++){	// loop over x-coordinate
                double x = -range + i*2*range/(Nres-1);
                for( int j=0; j<Nres; j++){	// Loop over y-coordinate
                    double y = -range + j*2*range/(Nres-1);
                    double t = x*cos(angle) + y*sin(angle);	// distance to origin for angle ll.
                    NumCurve temp_Curve = (array.GetFilteredCurve(ll+k*NviewPerslice));
                    sum[i][j] += (temp_Curve)(t,0)*pi/NviewPerslice;
                } // i loop
            }// j loop
        }    // ll loop
        for( int ii=0; ii<Nres; ii++){	// loop over x-coordinate
            for( int jj=0; jj<Nres; jj++){	// loop over y-coordinate
                w[ii][jj][k] = sum[ii][jj]/Nslice;
            }
        }
    }// k loop
    return rec;
}
