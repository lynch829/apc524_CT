#include "Image.h"
#include "AnaImage.h"
#include "NumCurve.h"
#include "NumSurface.h"
#include "Surface.h"
#include "Trapezoid.h"
#include "MCIntegrator.h"
#include "SimpleBackProjection.h"
#include "FilteredBackProjection.h"
#include "TestFunctions.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){

    double range = 10;
    const int size=64;
    const int Nres=100;
    double angle[size];

    NumCurve* container = new NumCurve[size];
    for(int i=0;i<size;i++) angle[i] = 0 + i*pi/(size-1); //  since 180 symmetry, do not include endpoint.

    Surface* gauss = new AnaSurface (Circle, range, range);
    LineIntegral* l = new Trapezoid();
    NumSurface* sf;

    for(int i=0; i<1; i++){
        NumCurve a = gauss->GetProjection(l,angle[i],0.1);
        container[i] = a;
    }

    sf = FilteredSymmetricBackProjection(angle,container,size,Nres);
    sf->Print();

    delete sf;
    delete l;
    delete gauss;
    delete [] container;
    return 0;
}
