//Abira Das and Patrick Sullivan
//GlobalPDE.h
//header file for GlobalPDE.hpp

#ifndef GLOBAL_PDE_H
#define GLOBAL_PDE_H

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "RangeError.h"
#include "Vector.h"
#include "FullMatrix.h"
#include "SymmMatrix.h"

using namespace std;

//-----------------BOUNDARIES------------------//
const double X_MIN = 0;
const double Y_MIN = 0;
const double X_MAX = M_PI;
const double Y_MAX = M_PI;

//Pre: n must be positive
//Post: Returns a Vector<DT> of approximations based on the value of n
//Description: Generates the A matrix and b vector, then solves the system of equations
//to get the x vector. The method depends on the passed in solver.
template <class MT, class DT>
Vector<DT> pdeApproximate(const int n);

//Pre: n must be positive
//Post: Returns a Symmetric Matrix for Poisson's equation using the bounds of
//0 to pi for the Ax = b problem
//Description: Generates the A matrix for Poisson's equation
template <class DT>
SymmMatrix<DT> genApdeMatrix(unsigned int n);

//Pre: n must be positive, addition should be defined for type DT
//Post: Returns a Vector for Poisson's equation using the bounds of
//0 to pi for the Ax = b problem
//Description: Generates the b vector for Poisson's equation
template <class DT>
Vector<DT> genBpdeVector(int n);

//Pre: x and y must be on the given boundaries of Poisson's equation
//Post: Returns the analytical solution for Poisson's equation for the given x & y
//Description: function to get analytical solution values for Poisson's equation
inline double poissonAnalytical(double x, double y)
{	return (1/sinh(M_PI)) *(sin(x)*sinh(M_PI-y) + sin(y)*sinh(M_PI-x)); }


//Pre: x and y must be within the domain of Poisson's equation
//Post: If x or y is on the boundary, return the value for that boundary function
//otherwise, throw range error
//Description: Calculates values at the boundaries of Poisson's equation
double poissonEdge(double x, double y);

//Pre: approxMatrix must be a non-empty matrix of approximation values
//Post: Returns a matrix of error differences
//Description: Calculates the poissonAnalytical value and then subtracts it from the 
//corresponding approximation value to get an error value. Does this for every value in the matrix.
template <class MT, class DT>
FullMatrix<DT> getErrorMatrix(const MatrixBase<MT, DT>& approxMatrix);


//Pre: approx must be a non-empty vector of approximation values
//Post: Outputs analysis to screen
//Description: Prompts user and outputs error summary, times for calculation, and 
//solution matrices if user inputs "y"
void analyzeApproximation(const Vector<double>& approx);

#include "GlobalPDE.hpp"

#endif

