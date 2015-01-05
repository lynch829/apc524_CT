#ifndef INTERPOLATOR
#define INTERPOLATOR
#include <vector>
using std::vector;

/*!
    Interpolator class.
*/
class Interpolator{

public:
    Interpolator();
    ~Interpolator();
    virtual double Interpolate(vector<double>&, double**, double*, int*, int) = 0;
    int coord2index(int*, int*, int);
};

#endif
