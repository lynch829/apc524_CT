#ifndef FBP
#define FBP 1

#include "Image.h"
#include "Curve.h"
#include "NumSurface.h"
#include "NumVolume.h"
#include "ImageArray.h"
#include "globals.h"

NumSurface* FilteredBackProjection( ImageArray&, int Nres=100, double (*kernal)(int,double)=Hamming);
	//!< From input ImageArray, performs filtered back-projection to reconstruct. Nres is the resolution of the final image / number of point along one axis. kernal is used to convolve the projection image. By default it is the Hamming function.
NumVolume* FilteredBackProjection3D( ImageArray&, int Nres=100, double (*kernal)(int,double)=Hamming);
	//!< From input ImageArray, performs filtered back-projection in 3D to reconstruct. Nres is the resolution of the final image / number of point along one axis. kernal is used to convolve the projection image. By default it is the Hamming function. ImageArray should contain more than one horizontal slice.

#endif
