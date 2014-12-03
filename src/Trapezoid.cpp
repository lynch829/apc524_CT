#include"Trapezoid.h"

Trapezoid::Trapezoid(){}

Trapezoid::~Trapezoid(){}

double Trapezoid::Integrate(std::function<double (double)> f, double xmin, double xmax, int N){
    double sum = 0;
    double d = (xmax-xmin)/N;
    for(int i=0;i<N;i++){
        double x0 = xmin + i*(xmax-xmin)/N;
        double x1 = xmin + (i+1)*(xmax-xmin)/N;
        sum += d*(f(x0)+f(x1))/2;
    }
    return sum;
}
