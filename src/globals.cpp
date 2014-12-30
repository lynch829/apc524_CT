#include "globals.h"

double Hamming(int n, double tau){ // Hamming window function, tau is real space spacing.
    double t = tau*tau;
    if (n==0) return 1.0/(4*t);
    else if (abs(n)%2==0) return 0;
    else return -1.0/(n*n*pi*pi*t);
}
