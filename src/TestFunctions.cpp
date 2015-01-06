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

double Heart(double x, double y, double z){
    return (pow((x*x+9*y*y/4+z*z-1),3)-x*x*z*z*z-9*y*y*z*z*z/80 >0)?0:1;
}

double Circle(double x, double y){
    return (x*x+y*y > 16)?0:1;
}

double Sphere(double x, double y, double z){
    return (x*x+y*y+z*z> 1)?0:1;
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

double Batman(double x, double y)
{
    double w=3*sqrt(1-x*x/49);
    double l=0.5*(x+3)-3.0/7*sqrt(40-40*(x+1)*(x+1))+6.0/7*sqrt(10);
    double h=0.5*(fabs(x+0.5)+fabs(x-0.5)+6-11*(x+3.0/4)+fabs(x-3.0/4));
    double r=0.5*(3-x)-3.0/7*sqrt(40-10*(x-1)*(x-1))+6.0/7*sqrt(10);

    double top = (h-l)*Heaviside(x+1)+(r-h)*Heaviside(x-1)+(l-w)*Heaviside(x+3)+(w-r)*Heaviside(x-3)+w;
    double bottom = 0.5*(fabs(x/2)+sqrt(1-(fabs(x-2)-1)*(fabs(x-2)-1))-1./112*(2*sqrt(33)-7)*x*x+3*sqrt(1-x*x/49)-3)*((x+4)/fabs(x+4)-(x-4)/fabs(x-4)-3*sqrt(1-x*x/49));
    if(isnan(top)) return 2;
    else if(isnan(bottom)) return 0;
    else if(y<top && y> bottom) return 1;
    else return -1;
}

double Heaviside(double x){
    return x>0?1.0:0.0;
}
