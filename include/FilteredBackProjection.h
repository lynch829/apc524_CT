#ifndef FBP
#define FBP 1

#include "Image.h"
#include "Curve.h"
#include "NumSurface.h"
#include "ImageArray.h"
#include "globals.h"

NumSurface* FilteredBackProjection( ImageArray&, int Nres=100, double (*kernal)(int,double)=Hamming);

#endif
