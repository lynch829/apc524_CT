#include "Image.h"
#include "AnaImage.h"
#include "NumCurve.h"
#include "NumSurface.h"
#include "NumVolume.h"
#include "Volume.h"
#include "Surface.h"
#include "Trapezoid.h"
#include "Romberg.h"
#include "MCIntegrator.h"
#include "NearestNeighborIntpl.h"
#include "TestFunctions.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


double gauss_1D(double x){
    return exp(-x*x/6);
}

double gauss_2D(double x, double y){
    //    return exp(-x*x/6 -y*y/3 + x*y/4)+ x*y/100;
    return exp(-x*x/3-y*y/15);
}

double gauss_3D(double x, double y, double z){
    return exp(-x*x/6 -y*y/3 + x*y/4 - z*z/3 + z*y/4);
}

double cylinder(double x, double y){
    return (x*x+y*y > 4)?0:1;
}

double box(double x, double y){
    double val = 0;
    if(fabs(x)<2 && fabs(y)<2) val = 1;
    return val;
}

int main(int argc, char* argv[]){
    if(argc<2){
        printf("usage: ./testVolume angle\n"); 
        return -1;
    }
    //  creates a nonsymmetric gaussian on 20 x 20 region.
    Image* gauss  = new AnaVolume(Heart, 2, 1.5, 2);
   // Interpolator* intpl = new NearestNeighborIntpl();
    // creates a numerical line using gauss_1D.
    //    Curve* gauss1 = new AnaCurve( gauss_1D,10);
    //    Image* num_gauss1 = new NumCurve(100,*gauss1);
    
    // creates a numerical surface using gass_3D.
    //Volume* gauss3 = new AnaVolume( gauss_3D,2,2,1);
    //NumVolume* num_gauss3 = new NumVolume(50,50,25,*gauss3);
    // defines trapezoid integration rule.
/*    LineIntegral* l=new Romberg();
    
    //  since Projection is defined
    
    Volume* ptr = (Volume*)gauss; //Image has no GetProjection, must downcast.
    NumSurface a;
    ptr->SetIntegralStep(0.0001);
<<<<<<< HEAD
    a = ptr->GetProjection3D(l,atof(argv[1]),0.01,0.01);
    //a.Print();
=======
    a = ptr->GetProjection(l,atof(argv[1]),0.01,0.01);
*/    //a.Print();
>>>>>>> 60b81c440c43e588b4b9d00baeb9cd692c739557
#ifdef USE_HDF
    gauss->ExportHDF("test.h5");
#endif
    delete gauss;
 //   delete gauss3;
 //   delete num_gauss3;
    return 0;
}
