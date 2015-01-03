#include "Image.h"
#include "AnaImage.h"
#include "NumCurve.h"
#include "NumSurface.h"
#include "Surface.h"
#include "Trapezoid.h"
#include "MCIntegrator.h"
#include "FilteredBackProjection.h"
#include "TestFunctions.h"
#include "globals.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){

    double range = 5;	// range of the geometry
    const int size=20;	// number of view
    const int Nres=1000;// resolution/ N of point in the projected curve.
    double angle[size];	// array containing size angles.

    ImageArray array;
    for(int i=0;i<size;i++) angle[i] = 0 + i*pi/size;
			 //  since 180 symmetry, do not include endpoint.

    Surface* gauss = new AnaSurface (Rectangle, range, range);
			 // a 2D function.
    LineIntegral* l;
    Trapezoid t; l = &t;	// integ. method
    NumSurface sf;	// Num Surf to contain reconstructed result.

    for(int i=0; i<size; i++){
        cerr<<"Projecting at angle "<< angle[i]<<endl;
        array.PushBack(angle[i], gauss->GetProjection(l,angle[i],0.1));
    }

    sf = *(FilteredBackProjection(array,Nres,Hamming));
			// filtered back-projection
//    array.PrintFiltered();
    sf.Print();	// print out the result.
    sf.ExportHDF("output/test.h5");

    delete gauss;
    return 0;
}
