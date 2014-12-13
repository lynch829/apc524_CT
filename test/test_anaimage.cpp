#include "Image.h"
#include "AnaImage.h"
#include "NumImage.h"
#include "Trapezoid.h"
#include "MCIntegrator.h"
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

//  creates a nonsymmetric gaussian on 20 x 20 region.
    Image* gauss  = new AnaSurface( gauss_2D, 10, 10);

// creates a numerical line using gauss_1D.
    Image* gauss1 = new AnaCurve( gauss_1D,10);
    //Image* NumGauss = new NumCurve(100,gauss1);
// defines trapezoid integration rule.
    LineIntegral* l=new Trapezoid();

//  since Projection is defined

    switch(argc)
    {
        case 1 : {gauss1->Print(); delete gauss1; return 0;}
        case 2 : {
		 Surface* ptr = (Surface*)gauss; //Image has no GetProjection, must downcast.
                 NumCurve a; a = ptr->GetProjection(l,atof(argv[1]),0.01);
                 a.Print();
                 delete gauss; return 0;
		 }
        default: {delete gauss; break;}
    }

    return 0;
}
