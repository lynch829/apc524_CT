#include"Image.h"
#include"AnaImage.h"
#include"Trapezoid.h"
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
    if(argc<3){
        printf("\n./test N-array N-index-to-print\n\n");
        return 0;
    }

    int N = atoi(argv[1]);
    int n = atoi(argv[2])-1;
    int n_ini = 0;

    Image** gauss = new Image*[N];
    gauss[0] = new AnaFunction( gauss_1D, 10); n_ini++;
    if(N>1) gauss[1] = new AnaImage2D( gauss_2D, 10, 10); n_ini++;
    if(N>2) gauss[2] = new AnaImage3D( gauss_3D, 10, 10, 10); n_ini++;

    if(n==2){
        AnaImage3D* ptr = (AnaImage3D*)gauss[n];
//        for(double i=-5;i<=5;i+=0.1) ptr -> Print(-10,10,200,-10,10,200,i);
    }
    else;// gauss[n]->Print();

    LineIntegral* l = new Trapezoid();
    AnaImage2D* ptr2 = (AnaImage2D*) gauss[1];
    ptr2->GetProjection(0.5,0.01,l);

    delete [] gauss;

    return 0;
}
