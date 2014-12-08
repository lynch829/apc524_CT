#ifndef INTERPOLATOR
#define INTERPOLATOR 1

class Interpolator{

public:
    Interpolator();
    virtual ~Interpolator();
    virtual double Interpolate(double,int,double*,double*,double*);
};

#endif
