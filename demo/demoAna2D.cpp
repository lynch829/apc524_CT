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
    
    int choice = -1;
    if (argc > 1) choice = atoi(argv[1]);
    
    double range = 8;	// range of the geometry
    const int size=100;	// number of view
    const int Nres=400;// resolution/ N of point in the projected curve.
    double angle[size];	// array containing size angles.
    
    ImageArray array;
    for(int i=0;i<size;i++) angle[i] = 0 + i*pi/size;
			 //  since 180 symmetry, do not include endpoint.
    AnaSurface* gauss;
    if(choice < 0 || choice > 4){
        printf("USAGE: %s (number)\n number is 0~4\n 0: Batman, 1: Gauss2D, 2: Circle, 3: Rectangle, 4: Triangle\n",argv[0]);
        return -1;
    }

    if(choice == 0) gauss = new AnaSurface (Batman, range, range);
    if(choice == 1) gauss = new AnaSurface (Gauss2D, range, range);
    if(choice == 2) gauss = new AnaSurface (Circle, range, range);
    if(choice == 3) gauss = new AnaSurface (Rectangle, range, range);
    if(choice == 4) gauss = new AnaSurface (Triangle, range, range);
			 // a 2D function.
    LineIntegral* l;
    Trapezoid t; l = &t;	// integ. method
    NumSurface *sf;	// Num Surf to contain reconstructed result.
    
    for(int i=0; i<size; i++){
        cerr<<"Projecting at angle "<< angle[i]<<endl;
        array.PushBack(angle[i], gauss->GetProjection(l,angle[i],0.1));
    }
    sf = (FilteredBackProjection(array,Nres,Hamming));
#ifdef USE_HDF
    sf->ExportHDF("out2D.h5");
#endif
    delete sf;
    delete gauss;
    return 0;
}
