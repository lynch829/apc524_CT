/*! \file
    \brief Abstract Image class for CT images. S
*/

#ifndef IMAGE_ABSTRACT
#define IMAGE_ABSTRACT 1

#include "globals.h"
#include "LineIntegral.h"

#ifdef USE_HDF
#include "hdf5.h"
#include "hdf5_hl.h"
#endif
/*!
An abstract Image class should contain the following abstract virtual methods:
(1) A function to return dimensionality. 
(2) A method that returns value at x. 
An Image is further classified into 1D (Curve), 2D(Surface) and 3D(Volume).
Object in each dimension will have to implement operator(), which returns the image value at the argument point. S
*/

class Image{

public:
    Image(Dimension dim = Dim0);//!< Constructor. Dimension by default is 0. S
    virtual ~Image();		//!< Virtual destructor, in case someone calls delete derived. S

    virtual void Print() = 0;	//!< Default method for printing. S
#ifdef USE_HDF
    virtual void ExportHDF(const char*) = 0;	//!< Method to print to HDF5 file.
#endif
    Dimension GetDimension();	//!< Returns the dimension of the image. S

protected:
    Dimension _dim;		//! Dimension of the problem, will be 1D, 2D, or 3D.

};

#endif
