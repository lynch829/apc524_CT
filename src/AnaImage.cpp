
#include"AnaImage.h"
#include<iostream>
#include<stdio.h>

AnaCurve::AnaCurve( f1D f, double x) : Curve(x)
{ _f1d = f; }

AnaCurve::~AnaCurve()
{}

AnaSurface::AnaSurface( f2D f, double x, double y):Surface(x,y)
{ _f2d = f; }

AnaSurface::~AnaSurface()
{ }

AnaVolume::AnaVolume( f3D f, double x, double y, double z):Volume(x,y,z)
{ _f3d = f; }

AnaVolume::~AnaVolume()
{ }

//================================================================

double AnaCurve::operator()(double x, Interpolator* intp) const
{ return _f1d(x); }

//================================================================

double AnaSurface::operator()(double x, double y, Interpolator* intp) const
{ return _f2d(x,y); }

//================================================================

double AnaVolume::operator()(double x, double y, double z, Interpolator* intp) const
{ return _f3d(x,y,z); }
