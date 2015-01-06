#include "Image.h"
#include "AnaImage.h"
#include "NumCurve.h"
#include "NumSurface.h"
#include "Surface.h"
#include "Trapezoid.h"
#include "MCIntegrator.h"
#include "FilteredBackProjection.h"
#include "TestFunctions.h"
#include "NearestNeighborIntpl.h"
#include "globals.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){

    double range = 5;	// range of the geometry
    const int size=200;	// number of view
    const int Nres=100;// resolution/ N of point in the projected curve.
    double angle[size];	// array containing size angles.

    ImageArray array;
    for(int i=0;i<size;i++) angle[i] = 0 + i*pi/size;
			 //  since 180 symmetry, do not include endpoint.

    Surface* gauss = new AnaSurface (Rectangle, range, range);
			 // a 2D function.
    LineIntegral* l;
    Trapezoid t; l = &t;	// integ. method
    NumSurface sf;	// Num Surf to contain reconstructed result.
//    NumSurface* Baltimore = new NumSurface("output/BaltimoreDowntown.h5");

    const int N = 100;
    double datax[N] = {0};
    double datay[N] = {0};
    double** dataz = new double*[N];
    for(int i=0;i<N;i++){
        datax[i] = -range + i*2.0*range/(N-1);
        datay[i] = datax[i];
        dataz[i] = new double[N];
    }

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            dataz[i][j] = exp(-(datax[i])*(datax[i])-(datay[j])*(datay[j]))*sin(datax[i]);

// ctor with data points
    NumSurface* c = new NumSurface(N,datax,N,datay,dataz);


    Interpolator* intpl = new NearestNeighborIntpl();

    for(int i=0; i<size; i++){
        cerr<<"Projecting at angle "<< angle[i]<<endl;
        array.PushBack(angle[i], c->GetProjection(l,angle[i],0.1,intpl));
    }

    sf = *(FilteredBackProjection(array,Nres,Hamming));
			// filtered back-projection
//    array.PrintFiltered();
    sf.Print();	// print out the result.
#ifdef USE_HDF
    sf.ExportHDF("output/BaltimoreReconstructed.h5");
#endif
    delete c;
    delete gauss;
    return 0;
}
