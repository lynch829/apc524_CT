#include"Romberg.h"
#include"math.h"

Romberg::Romberg(){}

Romberg::~Romberg(){}

double Romberg::Integrate(std::function<double(double)> f, double xmin, double xmax, double epsilon){
    double h = (xmax - xmin) / 2;
    int k=1;
    int n=1;
    int m;
    double **T;
    T = new double*[50];
    for(int j=0 ; j<50 ; j++){
        T[j] = new double[100];
    }
    T[0][0] = h * (f(xmin) + f(xmax));
    do{
        double F = 0.0;
        for(int i=1; i<=n; i++){
            F += f(xmin + (2.0*i-1)*h);
        }
        double temp = T[0][k-1];
        T[0][k] = temp/2.0 + h*F;

        for(m=1; m<=k; m++){
            double temp1 = T[m-1][k-m+1];
            double temp2 = T[m-1][k-m];
            T[m][k-m] = (pow(4.0,(double)m)*temp1 - temp2) / (pow(4.0,(double)m) - 1.0);
        }
        h /= 2.0;
        n *= 2;
        k++;
        
    }while(fabs(T[m-1][0]-T[m-2][0]) > epsilon);
    
    double I = T[m-1][0];
    
    for(int j=0; j<50; j++){
        delete[] T[j];
    }
    delete[] T;
    
    return I;
}