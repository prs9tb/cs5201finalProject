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

template <class DT>
Vector<DT> genBpdeVector(unsigned int n)
{
  Vector<DT> bVector(n);
  
  //-------------------insert function here------------------//
  
  return (bVector);



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






