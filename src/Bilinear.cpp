#include "Bilinear.h"
#include "globals.h"

Bilinear::Bilinear(){}	//!< Constructor for bilinear Interpolator.
Bilinear::~Bilinear(){}	//!< Destructor for bilinear Interpolator. Free memory.

double Bilinear::Interpolate(double x)
{
    int i0 = ArryIndexFloor(x,_xptr,_sizex);
    if(i0<0) return 0;
    int i1 = i0 +1;
    return _yptr[i0]+(_yptr[i1]-_yptr[i0])*(x-_xptr[i0])/(_xptr[_sizex-1]-_xptr[0]);
}

double Bilinear::Interpolate(double x, double y)
{
    int i0x = ArryIndexFloor(x,_xptr,_sizex);
    int i1x = i0x+1;
    int i0y = ArryIndexFloor(y,_yptr,_sizey);
    int i1y = i0y+1;

    if ( i0x<0 || i0y < 0){return 0;}

    double Q11 = _zzptr[i0x][i0y];
    double Q21 = _zzptr[i1x][i0y];
    double Q12 = _zzptr[i0x][i1y];
    double Q22 = _zzptr[i1x][i1y];
    double s1 = Q11*(_xptr[i1x]-x)*(_yptr[i1y]-y);
    double s2 = Q21*(x-_xptr[i0x])*(_yptr[i1y]-y);
    double s3 = Q12*(_xptr[i1x]-x)*(y-_yptr[i0y]);
    double s4 = Q22*(x-_xptr[i0x])*(y-_yptr[i0y]);
    return 1./((_xptr[i1x]-_xptr[i0x])*(_yptr[i1y]-_yptr[i0y]))*(s1+s2+s3+s4);
}

double Bilinear::Interpolate(double x, double y, double z)
{
    int i0x = ArryIndexFloor(x,_xptr,_sizex);
    int i1x = i0x+1;
    int i0y = ArryIndexFloor(y,_yptr,_sizey);
    int i1y = i0y+1;
    int i0z = ArryIndexFloor(z,_zptr,_sizez);
    int i1z = i0z+1;
    if(i0x<0 || i0y<0 || i0z<0) return 0;

    double dx = (_xptr[_sizex-1]-_xptr[0])/(_sizex-1);
    double dy = (_yptr[_sizez-1]-_yptr[0])/(_sizey-1);
    double dz = (_yptr[_sizez-1]-_zptr[0])/(_sizez-1);

    double xd = (x-_xptr[i0x])/dx;
    double yd = (y-_yptr[i0y])/dy;
    double zd = (z-_zptr[i0z])/dz;
    double w1 = _wptr[i0x][i0y][i0z];
    double w2 = _wptr[i1x][i0y][i0z];
    double w3 = _wptr[i0x][i1y][i0z];
    double w4 = _wptr[i1x][i1y][i0z];
    double w5 = _wptr[i0x][i0y][i1z];
    double w6 = _wptr[i1x][i0y][i1z];
    double w7 = _wptr[i0x][i1y][i1z];
    double w8 = _wptr[i1x][i1y][i1z];
    double c00 = w1*(1-xd)+w2*xd;
    double c10 = w3*(1-xd)+w4*xd;
    double c01 = w5*(1-xd)+w6*xd;
    double c11 = w7*(1-xd)+w8*xd;
    double c0 = c00*(1-yd)+c10*yd;
    double c1 = c01*(1-yd)+c11*yd;
    return c0*(1-zd)+c1*zd;
}
