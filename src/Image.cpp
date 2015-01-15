#include"Image.h"

Image::Image(Dimension dim){ _dim = dim; }

Image::~Image(){}

Dimension Image::GetDimension(){ return _dim;}
