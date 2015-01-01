#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H 1

#include <math.h>
#include <stdio.h>
#include "NumCurve.h"

double Gauss1D(double x);

double Gauss2D(double x, double y);

double Gauss3D(double x, double y, double z);

double Circle(double x, double y);

double Rectangle(double x, double y);

bool assertArrayEqual(double *, double *, int, double precision = 1e-8);

bool assertEqual(NumCurve, NumCurve, double precision=1e-8);

bool assertEqual(NumCurve*, NumCurve*, double precision=1e-8);

#endif
