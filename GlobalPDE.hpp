//Abira Das and Patrick Sullivan
//GlobalPDE.hpp
//functions for generating the A & b matricies
//of Poisson's equation

#include "GlobalPDE.h"

using namespace std;

// HOW TO CALL::::
// approx = pdeApproxmate<DataType, MatrixType>(n, solver);

template <class DT, class MT, class ST>
Vector<DT> pdeApproximate(const int n, const ST& solver)
{
  const int size = (n-1) * (n-1);
  Vector<DT> approximations(size);
  
  Vector<DT> bVector = genBpdeVector<DT>(n);
  
  SymmMatrix<DT> aSymmMatrix = genApdeMatrix<DT>(n);
  MT aMatrix(aSymmMatrix);
  
  approximations = solver(aMatrix, bVector);
  
  return approximations;
}

template <class DT>
SymmMatrix<DT> genApdeMatrix(unsigned int n)
{
  const int size = (n-1)*(n-1);
  SymmMatrix<DT> aMatrix(size, size);
  
  const DT oneEle(1);
  const DT negQuarterEle( -1.0/4.0 );
  int col;
  
  for (int diag=0 ; diag<size ; diag++)
    aMatrix(diag,diag) = oneEle;
  
  const int skip = n-1 ;
  for (int row=1 ; row<size ; row++)
  {
    if ( row % skip == 0)
      continue;
    col = row - 1;
    aMatrix(row, col) = negQuarterEle;
  }
  
  for (int row=n-1 ; row<size ; row++)
  {
    col = row - (n-1);
    aMatrix(row,col) = negQuarterEle;
  }
  
  return aMatrix;
}

template <class DT>
Vector<DT> genBpdeVector(int n)
{
  Vector<DT> bVector((n-1) * (n-1));
  
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
        bVector[bIndex] += DT(poissonEdge(left, y));
      if (right == X_MAX)
        bVector[bIndex] += DT(poissonEdge(right, y));
      if (bot == Y_MIN)
        bVector[bIndex] += DT(poissonEdge(x, bot));
      if (top == Y_MAX)
        bVector[bIndex] += DT(poissonEdge(x, top));
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
  double answer = (1.0/sinh(M_PI)) *(sin(x)*sinh(M_PI-y) + sin(y)*sinh(M_PI-x));
  return answer;
}






