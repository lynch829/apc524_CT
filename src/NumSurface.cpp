/*!
  \brief
  Implements numerical images.
*/

#include "NumSurface.h"

//! Default constructor, everything to Null
NumSurface::NumSurface() : Surface(0,0)
{
    _datax = 0;
    _datay = 0;
    _dataz = 0;
    _sizex = 0;
    _sizey = 0;
}

//! Constructor with a size input.
NumSurface::NumSurface(int sizex, int sizey): Surface(0,0), _sizex(sizex), _sizey(sizey)
{
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double*[_sizex];
    for(int i=0;i<_sizex;i++) _dataz[i] = new double[_sizey];
}

NumSurface::~NumSurface(){}
void NumSurface::Print(){}
void NumSurface::Print(double xi, double xf, int Nx, double yi, double yf, int Ny){}
