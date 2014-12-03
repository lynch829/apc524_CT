#include"Image.h"
#include"AnaImage.h"
#include<math.h>
#include<stdlib.h>
#include<stdio.h>

double gauss_1D(double x){
    return exp(-x*x/6);
}

double gauss_2D(double x, double y){
    return exp(-x*x/6 -y*y/3 + x*y/4);
}

int main(int argc, char* argv[]){
    if(argc!=3){
        printf("./test N-array N-index-to-print");
        return 0;
    }

    int N = atoi(argv[1]);
    int n = atoi(argv[2])-1;
    int n_ini = 0;

    Image** gauss = new Image*[N];
    gauss[0] = new AnaImage( Dim1, gauss_1D); n_ini++;
    if(N > 1) gauss[1] = new AnaImage( Dim2, gauss_2D); n_ini++;

    gauss[n] -> Print();

//    for(int i=0;i<n_ini;n++)
  //      delete gauss[i];
    delete [] gauss;

    return 0;
}
