#include "AnaImage.h"
#include "Trapezoid.h"
#include "TestFunctions.h"
#include "FilteredBackProjection.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

//! demoAna3D is a demo for 3D analytical functions to do X-ray simulation and reconstruction. Four analytical functions can be chosen. They are Gauss3D, heart, sphere, cube. USAGE: ./bin/demoAna3D (number)
//! number is 0~3 0: Gauss3D, 1: Heart, 2: Sphere, 3: Cube
int main(int argc, char* argv[]){
    int choice = -1;
    if(argc > 1) choice = atoi(argv[1]);
    
    double range = 2;
			//!< range of the geometry
    const int size= 30;
			//!< number of view per slice
    const int slice=50;
			//!< number of projected horizontal slice
    const int sizeT = size*slice;
			//!< total number of view
    const int Nres=50;
			//!< resolution/ N of point in the projected curve.
    double angle[sizeT];
			//!< array containing sizeT angles.
    double height[slice];
			//!< array containing height.
    double spacingz;
			//!< distance between each projected horizontal slice.
    ImageArray array;
			// ImageArray for storage.
    array.SetSlice(slice);
			//!< set the number of projected horizontal slice in array.
    spacingz = 2*range/slice;
			//!< set the spacing in z to obtain projection.

    for(int k=0;k<slice;k++){
        height[k] = -range+spacingz*k;
        for(int i=0;i<size;i++) {
            angle[i+k*size] = 0 + i*pi/size;
        }
    }
			//!<  since 180 symmetry, do not include endpoint.
    Volume* gauss;
    if(choice < 0 || choice >4){
        printf("USAGE: %s (number)\n number is 0~3\n 0: Gauss3D, 1: Heart, 2: Sphere, 3: Cube\n", argv[0]);
        return -1;
    }
			// if invalid choice, gracefully exit.

    if(choice == 0) gauss = new AnaVolume (Gauss3D, range, range, range);
    if(choice == 1) gauss = new AnaVolume (Heart, range, range, range);
    if(choice == 2) gauss = new AnaVolume (Sphere, range, range, range);
    if(choice == 3) gauss = new AnaVolume (Cube, range, range, range);
			 //!< create a 3D function depending on the choice.
    LineIntegral* l;
    Trapezoid t; l = &t;
			//!< specify integ. method
    NumVolume *sf;
			//!< Num Surf to contain reconstructed result.
    
    for(int k=0;k<slice;k++){
        cerr<<"Projecting at height "<<height[k]<<endl;
        for(int i=0; i<size; i++){
            cerr<<"Projecting at angle "<< angle[i+k*size]<<endl;
            array.PushBack(angle[i+k*size], height[k], gauss->GetProjection(l,angle[i+k*size],0.05,height[k]));
			// push the projections into the image container.
        }
    }

    sf = (FilteredBackProjection3D(array,Nres,Hamming));
			// calling filtered backprojection on ImageArray.
    cerr<<"Done running FBP3D"<<endl;

#ifdef USE_HDF
    sf->ExportHDF("outAna3D.h5");
#endif
    delete sf;
    delete gauss;
    return 0;
}
