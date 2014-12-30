#ifndef IMAGECONTAINER
#define IMAGECONTAINER 1

#include "Image.h"
#include "Curve.h"
#include "NumSurface.h"
#include "globals.h"

NumSurface* SimpleBackProjection(double*, Curve*,int size, int Nres=100);

#endif
