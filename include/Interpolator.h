#ifndef INTERPOLATOR
#define INTERPOLATOR
#include <vector>
//#include "NumSurface.h"
//#include "NumVolume.h"

using std::vector;

/*!
    Interpolator class.
*/
class Interpolator{

public:
    Interpolator();
    ~Interpolator();
    void set_values(int,int,double*,double*,double**);
    void set_values(int,int,int,double*,double*,double*,double***);
    virtual double Interpolate(double, double) = 0;
    virtual double Interpolate(double, double, double) = 0;

    int coord2index(int*, int*, int);

protected:
    int _sizex;
    int _sizey;
    int _sizez;
    double* _xptr;
    double* _yptr;
    double* _zptr;
    double** _vptr;
    double*** _wptr;
};

#endif
