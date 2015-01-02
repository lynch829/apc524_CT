#include "Image.h"
#include "AnaImage.h"
#include "NumCurve.h"
#include "NumSurface.h"
#include "Surface.h"
#include "Trapezoid.h"
#include "MCIntegrator.h"
#include "SimpleBackProjection.h"
#include "FilteredBackProjection.h"
#include "TestFunctions.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){

    double range = 5;	// range of the geometry
    const int size=512;	// number of view
    const int Nres=1000;	// resolution/ N of point in the projected curve.
    double angle[size];	// array containing size angles.

    NumCurve* container = new NumCurve[size];
    for(int i=0;i<size;i++) angle[i] = 0 + i*pi/size; //  since 180 symmetry, do not include endpoint.

    Surface* gauss = new AnaSurface (Rectangle, range, range); // a circle defined on a 10 by 10 grid.
    LineIntegral* l = new Trapezoid();	// integ. method
    NumSurface* sf;	// numerical surface to contain the reconstructed result.

    for(int i=0; i<size; i++){
        cerr<<"Projecting at angle "<< angle[i]<<endl;
        container[i] = gauss->GetProjection(l,angle[i],0.1);
//        if(i==1) container[i].Print();
    }

//    sf = FilteredSymmetricBackProjection(angle,container,size,Nres);	// filtered back-projection
    sf = FilteredBackProjection(angle,container,size,Nres);	// filtered back-projection
    sf->Print();	// print out the result.
//    gauss->Print();
    delete sf;
    delete l;
    delete gauss;
    delete [] container;
    return 0;
}
