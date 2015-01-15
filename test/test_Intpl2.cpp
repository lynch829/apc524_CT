#include "Image.h"
#include "AnaImage.h"
#include "NumCurve.h"
#include "NumSurface.h"
#include "Surface.h"
#include "Trapezoid.h"
#include "Interpolator.h"
#include "NearestNeighborIntpl.h"
#include "Bilinear.h"
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
      //Curve* gauss1 = new AnaCurve( gauss_1D,10);
      //Image* num_gauss1 = new NumCurve(100,*gauss1);
    
// creates a numerical surface using gass_2D.
    Surface* gauss2 = new AnaSurface( gauss_2D,2,2);
    NumSurface* num_gauss2 = new NumSurface(5,10,*gauss2);
  //  NumSurface Baltimore=NumSurface("./output/BaltimoreDowntown.h5");
// defines trapezoid integration rule.
    //LineIntegral* l=new Trapezoid();
 //  Interpolator* intpl = new NearestNeighborIntpl();
//  since Projection is defined
   switch(argc)
    {
       case 1 : {num_gauss2->Print(); delete gauss2; delete num_gauss2;return 0;}
       //case 1 : {num_gauss1->Print(); delete gauss1; delete num_gauss1;return 0;}
       case 2 : {
           NumSurface a = *num_gauss2;
           //a.SetRange(2,2);
           //a.Print();
 //		 NumCurve* ptr = (NumCurve*)num_gauss1; //Image has no GetProjection, must downcast.
 //          NumCurve a = *ptr;  //double a;
         //printf("%.9f\n",a(-1.8,-1.8,0));
 //        printf("%.9f\n",a(0,0));
 //          double r = Baltimore.GetRange();
        Bilinear intpl_nnb;
        Interpolator* intpl = &intpl_nnb;
	double r = a.GetRange();
        for(double rx=-r;rx<r;rx+=0.5){
               for(double ry=-r;ry<r;ry+=0.5){
           //printf("%.9f\n",a(1.8,1.8,intpl));
           //printf("%.9f\n",a(0.8,0.8,intpl));
           //printf("%.9f\n",a(0.1,0.1,intpl));
               //NearestNeighborIntpl intpl_nnb;
	     //  Interpolator* intpl = new NearestNeighborIntpl();
	       //Interpolator* intpl = new Bilinear();
               //Interpolator* intpl = &intpl_nnb;
               printf("%.9f\n",a(rx,ry,intpl));
               }
           }
//         printf("done interpolation\n");
        delete num_gauss2; return 0;
		 }
        default: {delete gauss; break;}
    }
     delete gauss2;
    return 0;
}

