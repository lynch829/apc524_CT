
#include"MCIntegrator.h"
#include<stdlib.h>

MCIntegrator::MCIntegrator(){}

MCIntegrator::~MCIntegrator(){}

double MCIntegrator::Integrate(std::function<double (double)> f, double xmin, double xmax, int N){
    double sum = 0;
    for(int i=0;i<N;i++){
	sum += f( xmin+1.0*rand()/RAND_MAX*(xmax-xmin));
    }
    return sum/N;
}
