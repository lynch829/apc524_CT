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

    int GetSize();
    double& GetAngle(int);
    double GetRange();

    NumCurve& GetCurve(int);
    NumCurve& GetFilteredCurve(int);
    void PushBack(double, const NumCurve& );
    void ConvolveWithKernal(double (*kernal)(int,double)=Hamming);
    

    void Print();
    void PrintFiltered();
    void PrintSinogram(double spacing = 0.01);

private:
    std::vector<NumCurve> _curve;
    std::vector<NumCurve> _filtered;
    std::vector<double> _angle;
    int _size;
};

#endif
