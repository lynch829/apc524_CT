#include"Image.h"

Image::Image(Dimension dim){
    _dim = dim;
    _lenx = _leny = _lenz = 0;
}

Image::~Image(){}

Dimension Image::GetDimension(){ return _dim;}

