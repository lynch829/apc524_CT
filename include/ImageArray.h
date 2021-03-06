#ifndef IMAGEARRAY
#define IMAGEARRAY 1

#include <vector>
#include "globals.h"
#include "NumCurve.h"
#include <stdio.h>
#include <iostream>

/*!
    This is a container class that contains objects of type NumCurve. The curves can be projections taken at various angles and heights, stored as vectors in the class. This object will be passed on to reconstructor such as FilteredBackProjection.
*/

class ImageArray{
public:
    ImageArray();
    ~ImageArray();

    int GetSize();		//!< Return the total number of elem in the vector. Number of view
    void SetSlice(int); //!< Set the total number of horizontal slice.
    int GetSlice(); //!< Get the total number of horizontal slice.
    double GetAngle(int);	//!< Get the angle for ith projection.
    double GetHeight(int);	//!< Return the height for ith projection.
    double GetRange();		//!< Get the maximum range of the curve.
    double GetRangeZ(); //!< Get the maximum range in z direction.
    NumCurve& GetCurve(int);	//!< Return ith curve.
    NumCurve& GetFilteredCurve(int);	//!< Return filtered curve.
    void PushBack(double, const NumCurve& );	//!< PushBack for 2D reconstruction.
    void PushBack(double, double, const NumCurve& );	//!< PushBack for 3D reconstruction.
    void ConvolveWithKernal(double (*kernal)(int,double)=Hamming);
					//!< Convole all elements with kernal
    void Print();			//!< Default print method.
    void PrintFiltered();		//!< Print all filtered curve.
    void PrintSinogram(double spacing = 0.01);	//!< Print out the sinogram.

private:
    std::vector<NumCurve> _curve;	//!< Stores the projection.
    std::vector<NumCurve> _filtered;	//!< Stores the projection after convolution.
    std::vector<double> _angle;		//!< Each angle at which projection is taken.
    std::vector<double> _height;	//!< Each height at which projection is taken.
    int _size; //!< Total number of view
    int _slice; //!< Total number of horizontal slice
};

#endif
