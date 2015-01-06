#include "Image.h"
#include "AnaImage.h"
#include "NumCurve.h"
#include "NumSurface.h"
#include "Surface.h"
#include "Romberg.h"
#include "Trapezoid.h"
#include "FilteredBackProjection.h"
#include "TestFunctions.h"
#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    if(argc<3){
        printf("usage: %s N-projection output-name\n",argv[0]);
        return -1;
    }
    double range = 8;			// range of the geometry
    int size=atof(argv[1]);		// number of view
    int Nres=500;	// resolution/ N of point in the projected curve.

    double* angle = new double[size];	// array containing size angles.
    for(int i=0;i<size;i++) angle[i] = 0 + i*pi/size;
			//  since 180 symmetry, do not include endpoint.
    ImageArray array;
			// Image container
    AnaSurface joker (Batman, range, range);
			// a 2D Batman function.
    LineIntegral* l; Trapezoid t; l = &t;	
			// integ. method
    for(int i=0; i<size; i++){
        cerr<<"Projecting at angle "<< angle[i]<<endl;
        array.PushBack(angle[i], joker.GetProjection(l,angle[i],0.1));
    }
//    array.Print();		// inspect array if necessary.
//    array.PrintSinogram();	// print out the sinogram if necessary.
    NumSurface sf = *(FilteredBackProjection(array,Nres,Hamming));
			// performs filtered back-projection.
//    sf.Print();		// print out the result.
#ifdef USE_HDF
    sf.ExportHDF(argv[2]);
#endif
    delete angle;
    return 0;
}
