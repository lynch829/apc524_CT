#include"Image.h"

Image::Image(Dimension dim){ _dim = dim; }

Image::~Image(){}

Dimension Image::GetDimension(){ return _dim;}


Function::Function():Image(Dim1){}
Function::~Function(){}


Image2D::Image2D():Image(Dim2){}
Image2D::~Image2D(){}


Image3D::Image3D():Image(Dim2){}
Image3D::~Image3D(){}

