#include "Bilinear.h"
#include <math.h>

Bilinear::Bilinear() {}

Bilinear::~Bilinear() {}

double Bilinear::Interpolate(vector<double>& x, double** data_x, double* fx, int* size, int dim){
    vector<double> r; r.resize(dim);
    for(int i=0;i<dim;i++){
        r[i]=data_x[i][size[i]-1];
    }//get the range in x and y directions;
    vector<int> i0; i0.resize(dim);
    vector<int> i1; i1.resize(dim);
    vector<double> d; d.resize(dim);
    double ret;
    for(int i=1;i<dim+1;i++){
        d[i] = 2*r[i]/(size[i-1]-1);
        i0[i] = int((x[i]+r[i])/d[i]);
        i1[i] = i0[i]+1;
        while (x[i] > data_x[i][i1[i]] && i1[i] < size[i-1]){
            i0[i] = i0[i]+1;i1[i] = i1[1]+1;
        }
        
        while (x[i] < data_x[i][i0[i]] && i0[i] >=0){
            i0[i] = i0[i]-1;i1[i] = i1[1]-1;
        }
    }
    if (i1[1] >size[0]-1 || i1[2] >size[1]-1|| i0[1] < 0 || i0[2] <0) return 0;
    else {
        int* q11 = new int[2];q11[0]=i0[1];q11[1]=i0[2];
        int* q12 = new int[2];q12[0]=i0[1];q12[1]=i1[2];
        int* q21 = new int[2];q21[0]=i1[1];q21[1]=i0[2];
        int* q22 = new int[2];q22[0]=i1[1];q22[1]=i1[2];
        double Q11 =fx[coord2index(q11,size,dim)];
        double Q21 =fx[coord2index(q12,size,dim)];
        double Q12 =fx[coord2index(q21,size,dim)];
        double Q22 =fx[coord2index(q22,size,dim)];
        double s1 = Q11*(i1[1]-x[1])*(i1[0]-x[2]);
        double s2 = Q21*(x[1]-i0[1])*(i1[2]-x[2]);
        double s3 = Q12*(i1[1]-x[1])*(x[2]-i0[2]);
        double s4 = Q22*(x[1]-i0[1])*(x[2]-i0[1]);
        ret = 1/((i1[1]-i0[1])*(i1[2]-i0[2]))*(Q11*s1+Q21*s2+Q12*s3+Q22*s4);
        return ret;
    }
}
