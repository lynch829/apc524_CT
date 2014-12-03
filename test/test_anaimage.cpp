#include"Image.h"
#include"AnaImage.h"
#include"Trapezoid.h"
#include"MCIntegrator.h"
#include<math.h>
#include<stdlib.h>
#include<stdio.h>

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

int main(int argc, char* argv[]){

    Image* gauss  = new AnaImage2D( gauss_2D, 10, 10);

    LineIntegral* l=new Trapezoid();
    AnaImage2D* ptr2 = (AnaImage2D*)gauss;

    if(argc<2){
	gauss->Print();
	return 0;
    }
    ptr2->GetProjection(l,atof(argv[1]),0.01);

    delete gauss;

    return 0;
}
