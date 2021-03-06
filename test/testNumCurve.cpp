#include "AnaImage.h"
#include "NumCurve.h"
#include "Trapezoid.h"
#include "TestFunctions.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    int choice = -1;
    if(argc>1) choice = atoi(argv[1]);

// default ctor()
    NumCurve a;
    NumCurve* aptr = &a;
    if(!assertEqual(a,*aptr)) return -1;

// ctor with a size;
    NumCurve b(100);
    NumCurve* bptr = &b;

    double range = 20;
    const int N = 500;
    double datax[N] = {0};
    double datay[N] = {0};
    for(int i=0;i<N;i++){
        datax[i] = -range + i*2.0*range/(N-1);
        datay[i] = exp(-fabs(datax[i]/(0.5*range)))*sin(datax[i]);
    }

// ctor with data points
    NumCurve* c = new NumCurve(N,range,datay);
    Curve* cptr = c;
// copy ctor
    NumCurve d(*c);
    if(!assertEqual(c,&d)) return -1;

// test assignment
    if(choice==0)aptr->Print();
    if(choice==1)bptr->Print(); 
    if(choice==2)c->Print();
    if(choice==3)d.Print();
    if(choice==4) {
        cptr->Print(-2*range,2*range,100000);
#ifdef USE_HDF
        cptr->ExportHDF("curve.h5");
#endif 
    }
// test assignment
    a = *c;
    b = d;
    if(!assertEqual(a,*c)) return -1;
    if(!assertEqual(b,d)) return -1;

    delete c;
    return 0;
}
