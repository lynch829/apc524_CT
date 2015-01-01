#ifndef FBP
#define FBP 1

#include "Image.h"
#include "Curve.h"
#include "NumSurface.h"
#include "globals.h"

NumSurface* FilteredBackProjection(double*, Curve*,int size, int Nres=100);

NumSurface* FilteredSymmetricBackProjection(double*, Curve*,int size, int Nres=100);

#endif
