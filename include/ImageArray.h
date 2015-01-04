#ifndef IMAGEARRAY
#define IMAGEARRAY 1

#include <vector>
#include "globals.h"
#include "NumCurve.h"
#include <stdio.h>
#include <iostream>

class ImageArray{
public:
    ImageArray();
    ~ImageArray();

    int GetSize();		//!< Return the total number of elem in the vector. Number of view
    double GetAngle(int);	//!< Get the angle for ith projection.
    double GetHeight(int);	//!< Return the height for ith projection.
    double GetRange();		//!< Get the maximum range of the curve

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
    int _size;
};

#endif
