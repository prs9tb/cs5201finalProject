//Abira Das and Patrick Sullivan
//GlobalPDE.cpp
//functions for generating the A & b matricies
//of Poisson's equation


#include <iostream>
#include <cmath>
#include <stdlib>

using namespace std;


template < Vector<DT> axbsolver(FullMatrix<DT>, Vector<DT>)>
FullMatrix<DT> pdeApproximate(int n, int iterations)
{
  FullMatrix<DT> newM(n, n);
  
  //-------------------insert function here------------------//
  
  return (newM);

}


SymmMatrix<DT> genApdeMatrix(unsigned int n)
{
  SymmMatrix<DT> aMatrix(n, n);
  
  //-------------------insert function here------------------//
  
  return (aMatrix);
}

Vector<DT> genBpdeVector(unsigned int n)
{
  SymmMatrix<DT> bVector(n, n);
  
  //-------------------insert function here------------------//
  
  return (bVector);



}

double poissonEdge(double x, double y)
{
  
  return x;
}

double poissonAnalytical(double x, double y)
{

  return x;
}






