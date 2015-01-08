#ifndef INTERPOLATOR
#define INTERPOLATOR
#include <vector>
using std::vector;

/*!
    Interpolator class.
*/
class NumSurface;
class NumVolume;

class Interpolator{

public:
    Interpolator();
    ~Interpolator();
    virtual double Interpolate(double, double, NumSurface& ) = 0;
    virtual double Interpolate(double, double, double, NumVolume& ) = 0;

    int coord2index(int*, int*, int);
};

#endif
