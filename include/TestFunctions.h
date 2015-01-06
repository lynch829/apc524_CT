/*! \file
    \brief Contains frequently used functions and features.
*/
#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H 1

#include <math.h>
#include <stdio.h>
#include "NumCurve.h"

double Gauss1D(double x);	//!< 1D Gauss function
double Gauss2D(double x, double y);	//!< 2D Gauss
double Gauss3D(double x, double y, double z);	//!< 3D Gauss

double Sphere(double x, double y, double z);
double Circle(double x, double y);	//!< Circle. Returns 1 or 0.
double Rectangle(double x, double y);	//!< Rectangle Returns 1 or 0.
double Triangle(double x, double y);	//!< Triangle. Returns 1 or 0.

bool assertArrayEqual(double *, double *, int, double precision = 1e-8);
	//!< Check if two arrays agree within the precision.
bool assertEqual(NumCurve, NumCurve, double precision=1e-8);
	//!< Check if two NumCurve agrees with each other.
bool assertEqual(NumCurve*, NumCurve*, double precision=1e-8);
	//!< Check if two NumCurves pointed by the pointer agrees with each other.

double Batman(double,double);
	//!< If a point lies in a batman symbol return 1, else return 0.
double Heaviside(double x);
#endif
