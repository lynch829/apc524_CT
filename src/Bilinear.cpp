#include "Bilinear.h"

Bilinear::Bilinear () {}

Bilinear::~Bilinear () {}

double Bilinear::Interpolate(double x, double y){
        printf("run1");
        double ret;
        const int dim=2; //dimmension is 2
        double _rx = - _xptr[0];
        double _ry = - _yptr[0];
        double dx = 2*_rx/(_sizex-1);
        int i0x = int((x+_rx)/dx);
        int i1x = i0x+1;
        double dy = 2*_ry/(_sizey-1);
        int i0y = int((y+_ry)/dy);
        int i1y = i0y+1;
        while ( i1x < _sizex && x > _xptr[i1x] ) {i0x++;i1x++;}
        while ( i1y < _sizey && y > _yptr[i1y] ) {i0y++;i1y++;}
        while ( i0x>=0 && x < _xptr[i0x]) {i0x--;i1x--;}	// move interval to match with given point.
        while ( i0y>=0 && y < _yptr[i0y]) {i0y--;i1y--;}	// move interval to match with given point.
        if ( i1x>_sizex-1 || i0x < 0 || i1y>_sizey-1 || i0y < 0) {return 0;}
        else {
             printf("run1");
            double Q11 = _vptr[i0x][i0y];
            double Q21 = _vptr[i1x][i0y];
            double Q12 = _vptr[i0x][i1y];
            double Q22 = _vptr[i1x][i1y];
             printf("run1");
            double s1 = Q11*(_xptr[i1x]-x)*(_yptr[i1y]-y);
            double s2 = Q21*(x-_xptr[i0x])*(_yptr[i1y]-y);
            double s3 = Q12*(_xptr[i1x]-x)*(y-_yptr[i0y]);
            double s4 = Q22*(x-_xptr[i0x])*(y-_yptr[i0y]);
            ret = 1/((_xptr[i1x]-_xptr[i0x])*(_yptr[i1y]-_yptr[i0y]))*(s1+s2+s3+s4);
            return ret;
            }


}

double Bilinear::Interpolate(double x, double y, double z){
return 0;

}
