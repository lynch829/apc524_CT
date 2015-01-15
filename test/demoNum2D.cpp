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
    
    double range = 8;	// range of the geometry
    const int size=100;	// number of view
    const int Nres=400;// resolution/ N of point in the projected curve.
    double angle[size];	// array containing size angles.
    
    ImageArray array;
    for(int i=0;i<size;i++) angle[i] = 0 + i*pi/size;
			 //  since 180 symmetry, do not include endpoint.
    NumSurface object;
    if (argc == 1){
        object=NumSurface("./output/Spine.h5");
    }
    else{
        object=NumSurface(argv[1]);    //argv[1] is the path of the input file. e.g. argv[1]="./output/Spine.h5"
    }
    
    NumSurface* gauss = &object;
    NumSurface a = *gauss;
    LineIntegral* l;
    Trapezoid t; l = &t;	// integ. method
    NumSurface sf;	// Num Surf to contain reconstructed result.
    
    Bilinear intpl_nnb;
    intpl_nnb.set_values(a.GetSizeX(),a.GetSizeY(),a.GetXPtr(),a.GetYPtr(),a.GetZPtr());
    Interpolator* intpl = &intpl_nnb;
    for(int i=0; i<size; i++){
        cerr<<"Projecting at angle "<< angle[i]<<endl;
        array.PushBack(angle[i], gauss->GetProjection(l,angle[i],0.1,intpl));
    }
    sf = *(FilteredBackProjection(array,Nres,Hamming));
    // filtered back-projection
#ifdef USE_HDF
    sf.ExportHDF("out_rctr.h5");
#endif
    return 0;
}
