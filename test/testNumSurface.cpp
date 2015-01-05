#include "Image.h"
#include "AnaImage.h"
#include "NumCurve.h"
#include "NumSurface.h"
#include "Surface.h"
#include "Trapezoid.h"
#include "MCIntegrator.h"
#include "TestFunctions.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    int choice = -1;
    if(argc>1) choice = atoi(argv[1]);

// default ctor()
    NumSurface a;
    NumSurface* aptr = &a;
//    if(!assertEqual(a,*aptr)) return -1;

// ctor with a size;
    Surface *b_temp = new AnaSurface(Gauss2D,10,10);
    NumSurface b(10,10,*b_temp);
    NumSurface* bptr = &b;

    double range = 20;
    const int N = 500;
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
    Surface* cptr = c;
// copy ctor
    NumSurface d(*c);
//    if(!assertEqual(c,&d)) return -1;

// test assignment
    if(choice==0)aptr->Print();
    if(choice==1){bptr->Print();
#ifdef USE_HDF
        bptr->ExportHDF("output/test.h5");
#endif
    }
    if(choice==2)c->Print();
    if(choice==3)d.Print();
    if(choice==4)cptr->Print(-range,range,200,-range,range,200);
#ifdef USE_HDF
    if(choice==5){
        NumSurface* e = new NumSurface("output/test.h5");
        e->ExportHDF("output/repeat.h5");
    }
#endif
    

// test assignment
    a = *c;
    b = d;
//    if(!assertEqual(a,*c)) return -1;
//    if(!assertEqual(b,d)) return -1;

    delete c;
    return 0;
}
