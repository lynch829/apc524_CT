
#include"MCIntegrator.h"
#include<stdlib.h>

MCIntegrator::MCIntegrator(){}

MCIntegrator::~MCIntegrator(){}

double MCIntegrator::Integrate(std::function<double (double)> f, double xmin, double xmax, double step){
    int N = 10*(xmax-xmin)/step;	//!< approximately equivalent number of required samples.
    double sum = 0;
    for(int i=0;i<N;i++){
	sum += f( xmin+1.0*rand()/RAND_MAX*(xmax-xmin));
    }
    return (xmax-xmin)*sum/N;
}
