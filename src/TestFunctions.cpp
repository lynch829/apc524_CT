#include "TestFunctions.h"

double Gauss1D(double x){
    return exp(-x*x);
}

double Gauss2D(double x, double y){
    return exp(-x*x/3-y*y/5)*sin(x);
}

double Gauss3D(double x, double y, double z){
    return exp(-x*x/6 -y*y/3 + x*y/4 - z*z/3 + z*y/4);
}

double Circle(double x, double y){
    return (x*x+y*y > 16)?0:1;
}

double Rectangle(double x, double y){
    double val = 0;
    if(fabs(x)<3 && fabs(y)<3) val = 1;
    return val;
}

double Triangle(double x, double y){
    if(y<-1) return 0;
    if(2*x+y>1) return 0;
    if(2*x-y<-1) return 0;
    return sin(x);
}

bool assertArrayEqual(double *x, double *y, int n, double precision){

    for(int i=0;i<n;i++){
        double diff=fabs(x[i]-y[i]);
        if(diff>precision){
            fprintf(stderr,"Test failed: array didn't match at index %d by %.5f\n",i,diff);
            return false;
        }
    }
    return true;
}

bool assertEqual(NumCurve a, NumCurve b, double precision){

    if(a.GetXPtr()==b.GetXPtr()){
        fprintf(stderr,"Test warning: the two have the same X pointer address.\n");
    }
    if(a.GetYPtr()==b.GetYPtr()){
        fprintf(stderr,"Test warning: the two have the same Y pointer address.\n");
    }

    if(a.GetSize()!=b.GetSize()){
        fprintf(stderr,"Test failed: different size.\n");
        return false;
    }
    double size = a.GetSize();
    double diff=fabs(a.GetRange()-b.GetRange());
    if(diff>precision){
        fprintf(stderr,"Test failed: range difference %.10f greater than precision %.10f\n",diff,precision);
        return false;
    }

    if(!assertArrayEqual(a.GetXPtr(),b.GetXPtr(),size,precision)) return false;
    if(!assertArrayEqual(a.GetYPtr(),b.GetYPtr(),size,precision)) return false;

    return true;
}

bool assertEqual(NumCurve *a, NumCurve *b, double precision){
    return assertEqual(*a,*b,precision);
}

