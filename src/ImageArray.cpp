#include "ImageArray.h"
#include "globals.h"

ImageArray::ImageArray():_size(0){}
ImageArray::~ImageArray()
{
    _angle.clear();
    _filtered.clear();
    _curve.clear();
    _height.clear();
}

int ImageArray::GetSize()
{
    return _size;
}

void ImageArray::SetSlice(int slice)
{
    _slice = slice;
}

int ImageArray::GetSlice()
{
    return _slice;
}

double ImageArray::GetAngle(int i)
{
    return _angle[i];
}

double ImageArray::GetHeight(int i)
{
    return _height[i];
}

NumCurve& ImageArray::GetCurve(int i)
{
    return _curve[i];
}

void ImageArray::PushBack(double a, const NumCurve& c)
{
    _curve.push_back(c);
    _filtered.push_back(c);
    _angle.push_back(a);
    _size++;
}

void ImageArray::PushBack(double a, double h, const NumCurve& c) //PushBack method for 3D objects.Note that _size will be the total number of NumCurves in the whole 3D domain.
{
    _curve.push_back(c);
    _filtered.push_back(c);
    _angle.push_back(a);
    _height.push_back(h);
    _size++;
}

void ImageArray::Print()
{
    for(int i=0;i<_size;i++){
        _curve[i].Print();

    }
}

void ImageArray::PrintFiltered()
{
    for(int i=0;i<_size;i++){
        _filtered[i].Print();
        printf("\n");
    }
}

void ImageArray::PrintSinogram(double spacing)
{
    bool same_size = true;
    for(int i=0;i<_size-1;i++)
        if(_curve[i].GetSize()!=_curve[i+1].GetSize()) {same_size = false; break;}
    if(same_size)
    for(int i=_size-1;i>=0;i--){
         for(int j=0;j<_curve[i].GetSize();j++)
             printf("%.8f ",(_curve[i])[j]);
         printf("\n");
    }
    else
    for(int i=_size-1;i>=0;i++){
         for(double j=-_curve[i].GetRange();j<_curve[i].GetRange();j+=spacing)
             printf("%.8f ",(_curve[i])(j,0));
         printf("\n");
    }
}

double ImageArray::GetRange()
{
    double r = 0;
    for(int i=0;i<_size;i++) r = max<double>(r,_curve[i].GetRange());
    return r;
}

double ImageArray::GetRangeZ()
{
    double r = 0;
    for(int i=0;i<_size;i++) r = max<double>(r,_height[i]);
    return r;
}

void ImageArray::ConvolveWithKernal(double (*kernal)(int,double))
{
    double _ran = this->GetRange();
    for(int i=0;i<_size;i++){
        int Npt = _curve[i].GetSize();
        double tau = 2*_ran/(Npt-1);			// Nyquist frequency
        for(int j=0;j<Npt;j++){		// beginning convolution.
            _filtered[i][j] = 0;
            for(int k=j-Npt+1;k<j+1;k++)
                _filtered[i][j] += tau * kernal(k,tau)*(_curve[i])[j-k];
        }
    }
}

NumCurve& ImageArray::GetFilteredCurve(int i)
{
    return _filtered[i];
}
