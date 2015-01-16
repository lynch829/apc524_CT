#include "globals.h"
#include <stdio.h>

double Hamming(int n, double tau)
{
    // Hamming window function, tau is real space spacing.
    double t = tau*tau;
    if (n==0) return 1.0/(4*t);
    else if (abs(n)%2==0) return 0;
    else return -1.0/(n*n*pi*pi*t);
}

int ArryIndexFloor(double x, double* array, int size)
{

    int indx = int((size-1)*((x-array[0])/(array[size-1]-array[0])));
    if(indx>size-1){
        fprintf(stderr,"Error: index %d is already at the end.\n",indx);
        return -1;
    }
    else if(indx<0){
        fprintf(stderr,"Error: index %d is below 0.\n",indx);
        return -2;
    }
    if(indx==size-1)
        return indx;
    if(x>=array[indx] && x<array[indx+1]){
        return indx;
    }
    else{
//        while(indx>0 && x>array[indx+1]) indx--;
//        while(indx<size-1 && x<array[indx]) indx++;
        return -1;
    }
}

int ArryIndexRoof(double x, double* array, int size)
{
    int indx = ArryIndexFloor(x,array,size);
    if(indx<size-1) return indx+1;
}

