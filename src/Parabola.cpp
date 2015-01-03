#include"Parabola.h"

Parabola::Parabola(){}

Parabola::~Parabola(){}

double Parabola::Integrate(std::function<double (double)> f, double xmin, double xmax, double step){
    double sum = 0;
    for (double i=xmin; i<xmax ; i += step){
        sum += step*(f(i)+4*f(i+step/2)+f(i+step))/6;
    }
    return sum;
}