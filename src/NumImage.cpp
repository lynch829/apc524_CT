/*!
  \brief
  Implements numerical images.
*/

#include"Function.h"
#include"Interpolator.h"

NumFunction::NumFunction()
{
    
    _datay = NULL;
    _size = 0;
}

NumFunction::NumFunction(int size, double* y): _size(size)
{
    _datay = new double[_size];
    for(int i=0;i<_size;i++)
}

NumFunction::NumFunction(&Function f)
{
    _size = f._size;
    for(int i=0;i<_size;i++){
        _x = new double[_size];
        _y = new double[_size];
    }
}
        ~NumFunction();

        NumFunction& operator=(&NumFunction);
        double& operator(double);

        void Print();
        void Print(double,double,int);

private:
        double* _datax; //!< X-coordinates of the points.
        double* _datay; //!< Y-Coordinates of the points.
        int _size;      //!< size of the array.
};

