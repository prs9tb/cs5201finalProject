
#ifndef GLOBAL_PDE_H
#define GLOBAL_PDE_H

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "RangeError.h"
#include "Vector.h"
#include "FullMatrix.h"
#include "SymmMatrix.h"

const double X_MIN = 0;
const double Y_MIN = 0;
const double X_MAX = M_PI;
const double Y_MAX = M_PI;


template <class MT, class DT>
Vector<DT> pdeApproximate(const int n);


template <class DT>
SymmMatrix<DT> genApdeMatrix(unsigned int n);


template <class DT>
Vector<DT> genBpdeVector(int n);


double poissonAnalytical(double x, double y);


double poissonEdge(double x, double y);


#include "GlobalPDE.hpp"

#endif

