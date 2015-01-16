#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;

int main(){
    srand(time(NULL));
//    First test array index searching method.
    int N = 200000;
    int size = N;
    double begin = -100;
    double end = 100;
    double* array = new double[N];
    for(int i=0;i<N;i++)
        array[i] = begin + i*(end-begin)/(N-1);

    for(int i=0;i<1000000;i++){
        double rnd = begin + (end-begin)*rand()/RAND_MAX;
        int index = ArryIndexFloor(rnd,array,N);
        if(index<0) return -1;
        if(index != size-1)
          if(rnd<array[index] || rnd>array[index+1]){
            fprintf(stderr,"Test Failed at run %d: %.5f index %d is not in %.5f %.5f\n",i,rnd,index,array[index],array[index+1]);
        }
    }
    delete [] array;
    fprintf(stderr,"Test Passed.\n");
    return 0;
}
