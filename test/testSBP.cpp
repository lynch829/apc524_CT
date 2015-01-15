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
    double range = 8;	// range of the geometry
    const int size=100;	// number of view
    const int Nres=400;// resolution/ N of point in the projected curve.
    double angle[size];	// array containing size angles.

    ImageArray array;
    for(int i=0;i<size;i++) angle[i] = 0 + i*pi/size;
			 //  since 180 symmetry, do not include endpoint.

    //AnaSurface* gauss = new AnaSurface (Batman, range, range);
			 // a 2D function.
    //Surface *b_temp = new AnaSurface(Gauss2D,2,2);
   // NumSurface* gauss = new NumSurface(500,500,*b_temp);
   // NumSurface a = *gauss;
    //cerr<<"range "<< gauss->GetRangeX()<<endl;
    //NumSurface* gauss = &b;
    
    NumSurface Baltimore=NumSurface("./output/Spine.h5");
    NumSurface* gauss = &Baltimore;
    NumSurface a = *gauss;
    LineIntegral* l;
    Trapezoid t; l = &t;	// integ. method
    NumSurface sf;	// Num Surf to contain reconstructed result.

    Bilinear intpl_nnb;
    intpl_nnb.set_values(a.GetSizeX(),a.GetSizeY(),a.GetXPtr(),a.GetYPtr(),a.GetZPtr());
    Interpolator* intpl = &intpl_nnb; 
    //    gauss->Print(); return 0;
    for(int i=0; i<size; i++){
        cerr<<"Projecting at angle "<< angle[i]<<endl;
	//Interpolator* intpl = new Bilinear();
        //gauss->SetIntegralStep(0.0001);
       array.PushBack(angle[i], gauss->GetProjection(l,angle[i],0.1,intpl));
    }
    //NumCurve a = array.GetFilteredCurve(0);
    //a.Print();
    //array.PrintSinogram();
     sf = *(FilteredBackProjection(array,Nres,Hamming));
			// filtered back-projection
//    array.PrintFiltered();
//    sf.Print();	// print out the result.
    sf.ExportHDF("Spine_rctr.h5");
#endif
    //delete gauss;
    return 0;
}

