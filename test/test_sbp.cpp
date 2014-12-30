#include "Image.h"
#include "AnaImage.h"
#include "NumCurve.h"
#include "NumSurface.h"
#include "Surface.h"
#include "Trapezoid.h"
#include "MCIntegrator.h"
#include "SimpleBackProjection.h"
#include "FilteredBackProjection.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

double gauss_1D(double x){
      return x>4?0:1;
//    return exp(-x*x/6);
}

double gauss_2D(double x, double y){
//    return exp(-x*x/6 -y*y/3 + x*y/4)+ x*y/100;
    return x*x/4+y*y/9<1 ? 1 : 0;
//	return exp(-x*x/3-y*y/15);
}

double gauss_3D(double x, double y, double z){
    return exp(-x*x/6 -y*y/3 + x*y/4 - z*z/3 + z*y/4);
}

double cylinder(double x, double y){
//    return (x*x+y*y > 4)?0:1;
    return fabs(x)<3&&fabs(y)<3 ? 1 : 0;
}

double box(double x, double y){
    double val = 0;
    if(fabs(x)<2 && fabs(y)<2) val = 1;
    return val;
}

int main(int argc, char* argv[]){
    double range = 10;
    const int size=256;
    const int Nres=200;
    double angle[size];
    NumCurve* container = new NumCurve[size];
    for(int i=0;i<size;i++) angle[i] = 0 + i*pi/size; //  since 180 symmetry, do not include endpoint.

    Surface* gauss = new AnaSurface (gauss_2D, range, range);
    LineIntegral* l = new Trapezoid();
    NumSurface* sf;

    for(int i=0; i<size; i++){
        NumCurve a = gauss->GetProjection(l,angle[i],0.1);
        container[i] = a;
    }

    sf = FilteredBackProjection(angle,container,size,Nres);
    sf->Print();
//    gauss->Print();

    delete sf;
    delete l;
    delete gauss;
    delete [] container;
    return 0;
}
