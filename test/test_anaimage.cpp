#include"Image.h"
#include"AnaImage.h"
#include<math.h>
#include<stdlib.h>
#include<stdio.h>

double gauss_1D(double x){
    return exp(-x*x/6);
}

double gauss_2D(double x, double y){
    return sin(x)*sin(y)*exp(-x*x/6 -y*y/3 + x*y/4);
}

int main(int argc, char* argv[]){
    if(argc!=3){
        printf("\n./test N-array N-index-to-print\n");
        return 0;
    }

    int N = atoi(argv[1]);
    int n = atoi(argv[2])-1;
    int n_ini = 0;

    Image** gauss = new Image*[N];
    gauss[0] = new AnaFunction( gauss_1D); n_ini++;
    if(N > 1) gauss[1] = new AnaImage2D( gauss_2D); n_ini++;

    static_cast<AnaImage2D*>(gauss[1])->Print(-10,10,200,-10,10,200);

//    for(int i=0;i<n_ini;n++)
  //      delete gauss[i];
    delete [] gauss;

    return 0;
}
