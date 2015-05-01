// Programmer: Abira Das & Patrick Sullivan
// Class: CS 5201 (Price)
//GaussianSolver.hpp
//implementations for the SubstitutionSolver.h file

#include "GaussianSolver.h"

#define DEBUG false

using std::cout;
using std::endl;
using std::abs;

template <class DT>
Vector<DT> GaussianSolver<DT>::operator()(FullMatrix<DT>& a, Vector<DT>& b) const
{
  const DT zero (0);
  const DT one (1);
  Vector<DT> result = b;
  
  
  if (a.rows () != b.size ())
    throw SizeError("FullMatrix and Vector cannot combine into augmented FullMatrix");
  if (DEBUG)
    cout << "&&&&&&&&&&&& Start: &&&&&&&&&&&&&&" << endl << a << endl;
  for (int diag = 0 ; diag < a.rows () ; diag++)
  {
    int pivotRow = getPivotRow (a, diag);
    rowSwap(a, diag, pivotRow);
    result.swapEle (diag, pivotRow);
    if (DEBUG)
      cout<<"******* Pivoted :"<<endl<<a<<endl;
    //scalar multiply row to make diag = 1
    DT scalar = 1.0 / a (diag, diag);
    rowMulti(a, diag, scalar);
    // a.row_multi (diag, scalar);
    result[diag] *= scalar;
    tolCheck (a (diag, diag), one);
    for (int clrR = diag + 1 ; clrR < a.rows () ; clrR++)
    {
      //scale row and add to others to zero column below
      scalar = -a (clrR, diag);
      rowMultiAdd(a, diag, scalar, clrR);
      // a.row_multi_add (diag, scalar, clrR);
      result[clrR] += scalar * result[diag];
      tolCheck (a (clrR, diag), zero);
    }
    if (DEBUG)
    {
      cout << "\t\t\t\t Pivot:" << pivotRow << "   Scalar:" << scalar << "  %%%%%%%%%%%%" << endl;
      cout << a << endl;
    }
  }
  if (DEBUG)
    cout << "&&&&&&&&&&&& Middle: &&&&&&&&&&&&&&" << endl << a << endl;
  // back substitution
  for (int diag = a.rows () - 1 ; diag >= 0 ; diag--)
  {
    for (int clrR = diag - 1 ; clrR >= 0 ; clrR--)
    {
      DT scalar = -a (clrR, diag);
      rowMultiAdd(a, diag, scalar, clrR);
      // a.row_multi_add (diag, scalar, clrR);
      result[clrR] += result[diag] * scalar;
      tolCheck (a (clrR, diag), zero);
    }
  }
  if (DEBUG)
    cout << "&&&&&&&&&&&& End: &&&&&&&&&&&&&&" << endl << a << endl;
    
  cout<<a<<endl;
  return result;
}


template <class DT>
int GaussianSolver<DT>::getPivotRow (const FullMatrix<DT> &a, const unsigned int diag) const
{
		int maxRow = diag;
		DT maxEle = abs (a (diag, diag));
		for (int r = diag + 1; r < a.rows () ; r++)
		{
				if (maxEle < abs (a (r, diag)))
				{
						maxRow = r;
						maxEle = abs (a (r, diag));
				}
		}
		return maxRow;
}  
