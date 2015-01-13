#include "Bilinear.h"

Bilinear::Bilinear () {}

Bilinear::~Bilinear () {}


void Bilinear::set_values(int sizex, int sizey, double* xptr, double* yptr, double** vptr){

_xptr = new double[sizex];
for (int i = 0;i<sizex;i++){
    double temp = xptr[i];
    _xptr[i] = temp;
}

_yptr = new double[sizey];
for (int i = 0;i<sizey;i++){
     double temp = yptr[i];
    _yptr[i] = temp;
}
_sizex = sizex; _sizey = sizey;

_zzptr = new double*[sizex];
for (int i = 0;i<sizex;i++){
    _zzptr[i] = new double[sizey];
}

for (int i = 0;i<sizex;i++){
    for (int j=0;j<sizey;j++){
    double temp = vptr[i][j];
    _zzptr[i][j] = temp;
    }
}

//delete [] _xptr; delete [] _yptr;
//for(int i=0;i<_sizex;i++){
//   delete [] _zzptr[i];
//   }
//delete [] _zzptr;
}


void Bilinear::set_values(int sizex, int sizey,int sizez, double* xptr, double* yptr, double* zptr, double*** wptr){
_xptr = new double[sizex];
for (int i = 0;i<sizex;i++){
    _xptr[i] = xptr[i];
}
_yptr = new double[sizey];
for (int i = 0;i<sizey;i++){
    _yptr[i] = yptr[i];
}

_zptr = new double[sizez];
for (int i = 0;i<sizez;i++){
    _zptr[i] = zptr[i];
}

_sizex = sizex; _sizey = sizey; _sizez = sizez;

_wptr = new double**[sizex];
for (int i =0;i<sizex;i++){
    _wptr[i] = new double*[sizey];
    for (int j=0;j<sizey;j++){
        _wptr[i][j] = new double[sizez];
        }
    }

for (int i = 0;i<sizex;i++){
    for (int j=0;j<sizey;j++){
        for(int k=0;k<sizez;k++){
           _wptr[i][j][k] = wptr[i][j][k];
           }
    }
}

}



double Bilinear::Interpolate(double x, double y){
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
            double Q11 = _zzptr[i0x][i0y];
            double Q21 = _zzptr[i1x][i0y];
            double Q12 = _zzptr[i0x][i1y];
            double Q22 = _zzptr[i1x][i1y];
            double s1 = Q11*(_xptr[i1x]-x)*(_yptr[i1y]-y);
            double s2 = Q21*(x-_xptr[i0x])*(_yptr[i1y]-y);
            double s3 = Q12*(_xptr[i1x]-x)*(y-_yptr[i0y]);
            double s4 = Q22*(x-_xptr[i0x])*(y-_yptr[i0y]);
            ret = 1/((_xptr[i1x]-_xptr[i0x])*(_yptr[i1y]-_yptr[i0y]))*(s1+s2+s3+s4);
            return ret;
            }


}

double Bilinear::Interpolate(double x, double y, double z){

        double ret;
        const int dim=3; //dimmension is 3
        double _rx = - _xptr[0];
        double _ry = - _yptr[0];
	double _rz = - _zptr[0];
        double dx = 2*_rx/(_sizex-1);
        int i0x = int((x+_rx)/dx);
        int i1x = i0x+1;
        double dy = 2*_ry/(_sizey-1);
        int i0y = int((y+_ry)/dy);
        int i1y = i0y+1;
        double dz = 2*_rz/(_sizez-1);
        int i0z = int((z+_rz)/dz);
        int i1z = i0z+1;

        while ( i1x < _sizex && x > _xptr[i1x] ) {i0x++;i1x++;}
        while ( i1y < _sizey && y > _yptr[i1y] ) {i0y++;i1y++;}
        while ( i1z < _sizez && z > _zptr[i1z] ) {i0z++;i1z++;}

        while ( i0x>=0 && x < _xptr[i0x]) {i0x--;i1x--;}	// move interval to match with given point.
        while ( i0y>=0 && y < _yptr[i0y]) {i0y--;i1y--;}	// move interval to match with given point.
        while ( i0z>=0 && z < _zptr[i0z]) {i0z--;i1z--;}	// move interval to match with given point.

        if ( i1x>_sizex-1 || i0x < 0 || i1y>_sizey-1 || i0y < 0) {return 0;}
        else {
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
             ret = c0*(1-zd)+c1*zd;
            return ret;
            }




}
