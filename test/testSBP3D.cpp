#include "Image.h"
#include "AnaImage.h"
#include "NumCurve.h"
#include "NumSurface.h"
#include "NumVolume.h"
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

    double range = 2;	// range of the geometry
    const int size=5;	// number of view per slice
    const int slice=5; // number of projected horizontal slice
    const int sizeT = size*slice; // total number of view
    const int Nres=100;// resolution/ N of point in the projected curve.
    double angle[sizeT]; // array containing sizeT angles.
    double height[slice]; // array containing height.
    double spacingz; // distance between each projected horizontal slice.
    ImageArray array;
    array.SetSlice(slice); // set the number of projected horizontal slice in array.
    spacingz = 2*range/slice; // set the spacing in z to obtain projection.
    for(int k=0;k<slice;k++){
        height[k] = -range+spacingz*k;
        for(int i=0;i<size;i++) {
	    angle[i+k*slice] = 0 + i*pi/size;
	}
} //  since 180 symmetry, do not include endpoint.

    Volume* gauss = new AnaVolume (Gauss3D, range, range, range);
			 // a 3D function.
    LineIntegral* l;
    Trapezoid t; l = &t;	// integ. method
    NumVolume sf;	// Num Surf to contain reconstructed result.

    for(int k=0;k<slice;k++){
        cerr<<"Projecting at height "<<height[k]<<endl;
        for(int i=0; i<size; i++){
            cerr<<"Projecting at angle "<< angle[i+k*slice]<<endl;
            NumSurface gauss_tmp;
            NumSurface* gauss_tmp_ptr;
    //gauss_tmp = gauss->GetProjection(l,0.2,0.1,spacingz);
            gauss_tmp = gauss->GetProjection(l,angle[i+k*slice],0.1,spacingz); //spacingr =0.1
            gauss_tmp_ptr = &(gauss_tmp);
            //Use a method of NumSurface to turn surface into numcurve;
            NumCurve curve_tmp=gauss_tmp_ptr->Surface2Curve();
            //cerr<<"r" << curve_tmp.GetRange()<<endl;
            //array.PushBack(0.1, -range+0.5*spacingz, curve_tmp);
            array.PushBack(angle[i+k*slice], height[k], curve_tmp);
            //cerr<<"runPushBack"<<endl;
        }
    }

    //cerr<<"range="<<array.GetRange()<<endl;
    //cerr<<"rangez="<<array.GetRangeZ()<<endl;
    //cerr<<"slice="<<array.GetSlice()<<endl;
    //cerr<<"size="<<array.GetSize()<<endl;
    cerr<<"running FBP3D"<<endl;
    sf = *(FilteredBackProjection3D(array,Nres,Hamming));
    cerr<<"Done running FBP3D"<<endl;
    //cerr << "sf(3,3,3) = " << sf(3,3,3) << endl;
			// filtered 3D back-projection
    //array.PrintFiltered();
   //sf.Print();	// print out the result.
//#ifdef USE_HDF
//    sf.ExportHDF("output/test.h5");
//#endif
    delete gauss;
    return 0;
}
