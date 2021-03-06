#include "Trapezoid.h"
#include "FilteredBackProjection.h"
#include "TestFunctions.h"
#include "Bilinear.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
//! This demo loads a hdf5 file from external sources and output a numerical volume that is the reconstructed image of the origin one. If input from command line is 1, then the default image brain.h5 will be loaded. If input from command line is the path of a hdf5 file specified by the user, then the user-specified file will be loaded. File name of output of this demo is outNum3D.h5.

int main(int argc, char* argv[]){
					// This demo required installation of HDF5.
#ifdef USE_HDF  
    double range = 0.5;			//!< range of the geometry
    const int size= 100;		//!< number of view per slice
    const int slice=30; 		//!< number of projected horizontal slice
    const int sizeT = size*slice;	//!< total number of view
    const int Nres=128;			//!< resolution/ N of point in the projected curve.
    double angle[sizeT]; 		//!< array containing sizeT angles.
    double height[slice]; 		//!< array containing height.
    double spacingz; 			//!< distance between each projected horizontal slice.

    ImageArray array;			// ImageArray container
    array.SetSlice(slice); 		//!< set the number of projected horizontal slice in array.
    spacingz = 2*range/slice; 		//!< set the spacing in z to obtain projection.
    for(int k=0;k<slice;k++){
        height[k] = -range+spacingz*k;
        for(int i=0;i<size;i++) {
            angle[i+k*size] = 0 + i*pi/size;
        }
    } 					//!<  since 180 symmetry, do not include endpoint.
    
    NumVolume object;
    if (argc == 1){
        object=NumVolume("./input/brain.h5");
    }
					// load numerical data from external file.
    else{
        object=NumVolume(argv[1]);   	//!< argv[1] is the path of the input file. e.g. argv[1]="./input/brain.h5"
    }

    Bilinear intpl_nnb;			// using bilinear interpolation method.
    Interpolator* intpl = &intpl_nnb;
    
    LineIntegral* l;
    Trapezoid t; l = &t;		//!< specify integ. method
    NumVolume *sf;			//!< Num Surf to contain reconstructed result.
    
    for(int k=0;k<slice;k++){
        cerr<<"Projecting at height "<<height[k]<<endl;
        for(int i=0; i<size; i++){
            cerr<<"Projecting at angle "<< angle[i+k*size]<<endl;
            NumCurve obj_tmp;
            obj_tmp = object.GetProjection(l,angle[i+k*size],0.01,height[k],intpl);
            array.PushBack(angle[i+k*size], height[k], obj_tmp);
					// performing projection and storing the result in the container
        }
    }

    cerr<<"running FBP3D"<<endl;
    sf = (FilteredBackProjection3D(array,Nres,Hamming));
					// 3D version of filtered backprojection.
    cerr<<"Done running FBP3D"<<endl;
					//!< File will automatically be stored in output directory
    sf->ExportHDF("outNum3D.h5");
    cerr<<"doneHDF"<<endl;
    delete sf;

#else
    fprintf(stderr,"This demo requires HDF5 libraries. Please enable them by\n");
    fprintf(stderr,"\n\t\tmake USE_HDF=1\n\n");
					// If no HDF, give a warning/reminder message.
#endif

    return 0;
}
