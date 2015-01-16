#include"MCIntegrator.h"
#include"Parabola.h"
#include"Romberg.h"
#include"Trapezoid.h"
#include<stdio.h>
#include<stdlib.h>

double f(double x){
    return 3*x*x;
}

int main(int argc, char* argv[]){
  /*
    int choice = -1;
    if (argc > 1) choice = atoi(argv[1]);
    
    LineIntegral* l;
    double step;
    
    if(choice == -1){
        printf("USAGE: %s (number)\n number is 0~3\n 0: MCIntegrator, 1: Parabola, 2: Romberg, 3: Trapezoid\n",argv[0]);
        return -1;
    }
    if(choice == 0){ MCIntegrator t; l = &t; step = 0.001;}
    if(choice == 1){ Parabola t; l = &t; step = 0.001;}
    if(choice == 2){ Romberg t; l = &t; step = 0.00001;}
    if(choice == 3){ Trapezoid t; l = &t; step = 0.001;}
    
    printf("The result of integration is %f\n",l->Integrate(f, 0, 3, step));
 */
    LineIntegral* l1;
    LineIntegral* l2;
    LineIntegral* l3;
    LineIntegral* l4;
    MCIntegrator t1;
    Parabola t2;
    Romberg t3;
    Trapezoid t4;
    double step1 = 0.001;
    double step2 = 0.00001;
    l1 = &t1;
    l2 = &t2;
    l3 = &t3;
    l4 = &t4;
    printf("The result of MCIntegraor Method is %f\n",l1->Integrate(f, 0, 3, step1));
    printf("The result of Parabola Method is %f\n",l2->Integrate(f, 0, 3, step1));
    printf("The result of Romberg Method is %f\n",l3->Integrate(f, 0, 3, step2));
    printf("The result of Trapezoid Method is %f\n",l4->Integrate(f, 0, 3, step1));
    
}
