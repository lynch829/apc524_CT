#include "Trapezoid.h"
#include "FilteredBackProjection.h"
#include "TestFunctions.h"
#include "Bilinear.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

//! This demo loads a hdf5 file from external sources and output a numerical surface that is the reconstructed image of the origin one. If input from command line is 1, then the default image spine.h5 will be loaded. If input from command line is the path of a hdf5 file specified by the user, then the user-specified file will be loaded. File name of output of this demo is outNum2D.h5.

int main(int argc, char* argv[]){
				// compile only if DF5 is installed/enabled
#ifdef USE_HDF
    double range = .5;		//!< range of the geometry
    const int size=100;		//!< number of view
    const int Nres=400; 	//!< resolution/ N of point in the projected curve.
    double angle[size];		//!< array containing size angles.
    
    ImageArray array;		// at this point I guess you are not unfamiliar with this object
    for(int i=0;i<size;i++) angle[i] = 0 + i*pi/size;
				//!<  since 180 symmetry, do not include endpoint.
    NumSurface object;
    if (argc == 1){
        object=NumSurface("./input/spine.h5");
				// read input data from input directory.
    }
    else{
        object=NumSurface(argv[1]);
				//!< argv[1] is the path of the input file. e.g. argv[1]="./input/spine.h5"
    }
    
    LineIntegral* l;
    Trapezoid t; l = &t;	//!< integ. method
    NumSurface *sf;		//!<  Num Surf to contain reconstructed result.
    
    Bilinear intpl_nnb;		// Bilinear interpolation. Necessary for numerical objects.
    Interpolator* intpl = &intpl_nnb;

    for(int i=0; i<size; i++){
        cerr<<"Projecting at angle "<< angle[i]<<endl;
        array.PushBack(angle[i], object.GetProjection(l,angle[i],0.01,intpl));
				// filtered backprojeciton and storing.
    }
    sf = (FilteredBackProjection(array,Nres,Hamming));
				//!< filtered back-projection	
    sf->ExportHDF("outNum2D.h5");
				//!< The file will automatically be stored in the output directory
    delete sf;

#else
    fprintf(stderr,"This demo requires HDF5 libraries. Please enable them by\n");
    fprintf(stderr,"\n\t\tmake USE_HDF=1\n\n");
				// If HDF5 is not installed, give a warning.
#endif

    return 0;
}

