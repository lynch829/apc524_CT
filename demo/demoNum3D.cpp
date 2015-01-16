#include "Image.h"
#include "AnaImage.h"
#include "NumCurve.h"
#include "NumSurface.h"
#include "NumVolume.h"
#include "Surface.h"
#include "Trapezoid.h"
#include "Romberg.h"
#include "MCIntegrator.h"
#include "FilteredBackProjection.h"
#include "TestFunctions.h"
#include "globals.h"
#include "NearestNeighborIntpl.h"
#include "Bilinear.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
#ifdef USE_HDF  
    double range = 0.5;	// range of the geometry
    const int size= 30;	// number of view per slice
    const int slice=27; // number of projected horizontal slice
    const int sizeT = size*slice; // total number of view
    const int Nres=128;// resolution/ N of point in the projected curve.
    double angle[sizeT]; // array containing sizeT angles.
    double height[slice]; // array containing height.
    double spacingz; // distance between each projected horizontal slice.
    ImageArray array;
    array.SetSlice(slice); // set the number of projected horizontal slice in array.
    spacingz = 2*range/slice; // set the spacing in z to obtain projection.
    for(int k=0;k<slice;k++){
        height[k] = -range+spacingz*k;
        for(int i=0;i<size;i++) {
            angle[i+k*size] = 0 + i*pi/size;
        }
    } //  since 180 symmetry, do not include endpoint.
    
    NumVolume object;
    if (argc == 1){
        object=NumVolume("./input/brain.h5");
    }
    else{
        object=NumVolume(argv[1]);    //argv[1] is the path of the input file. e.g. argv[1]="./input/brain.h5"
    }
    NumVolume* gauss = &object;
    Bilinear intpl_nnb;
    Interpolator* intpl = &intpl_nnb;
    
    LineIntegral* l;
    Trapezoid t; l = &t;	// integ. method
    NumVolume *sf;	// Num Surf to contain reconstructed result.
    
    for(int k=0;k<slice;k++){
        cerr<<"Projecting at height "<<height[k]<<endl;
        for(int i=0; i<size; i++){
            cerr<<"Projecting at angle "<< angle[i+k*size]<<endl;
            NumCurve gauss_tmp;
            gauss_tmp = gauss->GetProjection(l,angle[i+k*size],0.01,height[k],intpl); //spacingr =0.1
            array.PushBack(angle[i+k*size], height[k], gauss_tmp);
        }
    }
    cerr<<"running FBP3D"<<endl;
    sf = (FilteredBackProjection3D(array,Nres,Hamming));
    cerr<<"Done running FBP3D"<<endl;
// File will automatically be stored in output directory
    sf->ExportHDF("out3D.h5");
    cerr<<"doneHDF"<<endl;
#else
    fprintf(stderr,"This demo requires HDF5 libraries. Please enable them by\n");
    fprintf(stderr,"\n\t\tmake USE_HDF=1\n\n");
#endif
    delete sf;
    return 0;
}

