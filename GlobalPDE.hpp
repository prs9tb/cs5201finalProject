//Abira Das and Patrick Sullivan
//GlobalPDE.cpp
//functions for generating the A & b matricies
//of Poisson's equation


#include <iostream>
#include <cmath>
#include <cstdlib>

#include "RangeError.h"
#include "Vector.h"
#include "FullMatrix.h"
#include "SymmMatrix.h"

using namespace std;


template <class DT>
Vector<DT> pdeApproximate(const int n);
template <class DT>
SymmMatrix<DT> genApdeMatrix(unsigned int n);
double poissonAnalytical(double x, double y);
double poissonEdge(double x, double y);
Vector<double> genBpdeVector(int n);


template <class DT>
Vector<DT> pdeApproximate(const int n)
{
  Vector<DT> approximations(n);
  
  
  return approximations;
}



// template < Vector<DT> axbsolver(FullMatrix<DT>, Vector<DT>)>
// FullMatrix<DT> pdeApproximate(int n, int iterations)
// {
  // FullMatrix<DT> newM(n, n);

  // // -------------------insert function here------------------//
  
	// return NULL;
// }


const double X_MIN = 0;
const double Y_MIN = 0;
const double X_MAX = M_PI;
const double Y_MAX = M_PI;

template <class DT>
SymmMatrix<DT> genApdeMatrix(unsigned int n)
{
  SymmMatrix<DT> aMatrix(n, n);
  
  //-------------------insert function here------------------//
  
  return (aMatrix);
}

Vector<double> genBpdeVector(int n)
{
  Vector<double> bVector((n-1) * (n-1));
  
  double deltaX = (X_MAX - X_MIN) / n;
  double deltaY = (Y_MAX - Y_MIN) / n;
  int bIndex = 0;
  
  double left, right, top, bot;
  double x, y;
  
  for (int i=1 ; i<n ; i++)
  {
    y = Y_MIN + deltaY * i;
    for (int j=1 ; j<n ; j++)
    {
      x = X_MIN + deltaX * j;
      left = x - deltaX;
      right = x + deltaX;
      top = y + deltaY;
      bot = y - deltaY;
      
      if (left == X_MIN)
        bVector[bIndex] += poissonEdge(left, y);
      if (right == X_MAX)
        bVector[bIndex] += poissonEdge(right, y);
      if (bot == Y_MIN)
        bVector[bIndex] += poissonEdge(x, bot);
      if (top == Y_MAX)
        bVector[bIndex] += poissonEdge(x, top);
      bIndex++;
    }
  }
  
  return bVector;
}

double poissonEdge(double x, double y)
{
	if (x == X_MIN)
		return sin(y);
	if (x == X_MAX)
		return 0;
	if (y == Y_MIN)
		return sin(x);
	if (y == Y_MAX)
		return 0;
	throw RangeError("x,y is not on poisson edge");
	return 0;
}

double poissonAnalytical(double x, double y)
{
  double answer = (1/sinh(M_PI)) *(sin(x)*sinh(M_PI-y) + sin(y)*sinh(M_PI-x));
  return answer;
}






