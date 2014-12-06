#include"Trapezoid.h"

Trapezoid::Trapezoid(){}

Trapezoid::~Trapezoid(){}

double Trapezoid::Integrate(std::function<double (double)> f, double xmin, double xmax, double step){
    double sum = 0;
    for(double i=xmin;i<xmax;i+=step){
        sum += step*(f(i)+f(i+step))/2;
    }
    return sum;
}
