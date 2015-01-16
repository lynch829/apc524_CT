#include "AnaImage.h"
#include "FilteredBackProjection.h"
#include "Trapezoid.h"
#include "TestFunctions.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

//! demoAna2D is a demo for 2D Analytical functions to do X-ray simulation and reconstruction. Five analytical functions can be chosen. They are "Batman", Gauss2D, Rectangle, Circle and Triangle. USAGE: ./bin/demoAna2D (number)
//! number is 0~5 0: Batman, 1: Gauss2D, 2: Circle, 3: Rectangle, 4: Triangle
int main(int argc, char* argv[]){
    
    int choice = -1;
    if (argc > 1) choice = atoi(argv[1]);
			// choice of geometry for later input from user    
    double range = 8;
			//!< range of the geometry
    const int size=100;
			//!< number of view
    const int Nres=400;
			//!< resolution/ N of point in the projected curve.
    double angle[size];
			//!< array containing angles of different projection directions.
    
    ImageArray array;
			// Create ImageArray for later storing projection data.
    for(int i=0;i<size;i++) angle[i] = 0 + i*pi/size;
			//!<  since 180 symmetry, do not include endpoint.

    AnaSurface* gauss;
    if(choice < 0 || choice > 4){
        printf("USAGE: %s (number)\n number is 0~4\n 0: Batman, 1: Gauss2D, 2: Circle, 3: Rectangle, 4: Triangle\n",argv[0]);
        return -1;
    }
			// if no choice is specified, or invalid range, gracefully exit.

    if(choice == 0) gauss = new AnaSurface (Batman, range, range);
    if(choice == 1) gauss = new AnaSurface (Gauss2D, range, range);
    if(choice == 2) gauss = new AnaSurface (Circle, range, range);
    if(choice == 3) gauss = new AnaSurface (Rectangle, range, range);
    if(choice == 4) gauss = new AnaSurface (Triangle, range, range);
			//!< a 2D function.
    LineIntegral* l;	
    Trapezoid t; l = &t;
			//!< secify integration methos
    NumSurface *sf;
			//!< Num Surf to contain reconstructed final result.
    
    for(int i=0; i<size; i++){
        cerr<<"Projecting at angle "<< angle[i]<<endl;
        array.PushBack(angle[i], gauss->GetProjection(l,angle[i],0.1));
			//!< Fill the ImageArray with projections from different angles.
    }

    sf = (FilteredBackProjection(array,Nres,Hamming));
			//!< Performing backprojection with Nres points and Hamming kernal.

#ifdef USE_HDF
    sf->ExportHDF("outAna2D.h5");
			//!< If HDF5 is defined, export it to file.
#endif
    delete sf;
    delete gauss;
			// free allocated memory on heap
    return 0;
}
