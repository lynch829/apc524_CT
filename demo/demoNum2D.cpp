#include "Image.h"
#include "AnaImage.h"
#include "NumCurve.h"
#include "NumSurface.h"
#include "Surface.h"
#include "Trapezoid.h"
#include "Romberg.h"
#include "MCIntegrator.h"
#include "FilteredBackProjection.h"
#include "TestFunctions.h"
#include "globals.h"
#include "Interpolator.h"
#include "NearestNeighborIntpl.h"
#include "Bilinear.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
#ifdef USE_HDF
    double range = .5;	// range of the geometry
    const int size=100;	// number of view
    const int Nres=400;// resolution/ N of point in the projected curve.
    double angle[size];	// array containing size angles.
    
    ImageArray array;
    for(int i=0;i<size;i++) angle[i] = 0 + i*pi/size;
			 //  since 180 symmetry, do not include endpoint.
    NumSurface object;
    if (argc == 1){
        object=NumSurface("./input/spine.h5");
    }
    else{
        object=NumSurface(argv[1]);    //argv[1] is the path of the input file. e.g. argv[1]="./input/spine.h5"
    }
    
    NumSurface* gauss = &object;
    LineIntegral* l;
    Trapezoid t; l = &t;	// integ. method
    NumSurface *sf;	// Num Surf to contain reconstructed result.
    
    Bilinear intpl_nnb;
    Interpolator* intpl = &intpl_nnb;
    for(int i=0; i<size; i++){
        cerr<<"Projecting at angle "<< angle[i]<<endl;
        array.PushBack(angle[i], gauss->GetProjection(l,angle[i],0.01,intpl));
    }
    sf = (FilteredBackProjection(array,Nres,Hamming));
    // filtered back-projection
// The file will automatically be stored in the output directory
    sf->ExportHDF("out2D.h5");
    delete sf;
#else
    fprintf(stderr,"This demo requires HDF5 libraries. Please enable them by\n");
    fprintf(stderr,"\n\t\tmake USE_HDF=1\n\n");
#endif
    return 0;
}

