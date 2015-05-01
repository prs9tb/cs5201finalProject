/// Programmer: Abira Das
/// Class: CS 5201 (Price)
/// File: GaussianSolver.h
/// Purpose: Substitution solver class for Upper and Lower
/// Triangular Matrices


#ifndef GAUSSIAN_SOLVER_H
#define GAUSSIAN_SOLVER_H

#include <iostream>

#include "SolverBase.h"
#include "Vector.h"
#include "FullMatrix.h"


template <class DT>
class GaussianSolver : public virtual GaussianSolver<FullMatrix<DT>, DT> 
{
  public:
    GaussianSolver() {}
    Vector<DT> operator()(FullMatrix<DT>& a, Vector<DT>& b);
    
  private:
    void rowSwap(FullMatrix<DT>& aMatrix , const int row1, const int row2)
    {
      aMatrix(row1).swap(aMatrix(row2))
    }
    
    void rowMulti(FullMatrix<DT>& aMatrix , const int row, const DT& scalar)
    {
      aMatrix(row) *= scalar;
    }
    
    void rowMultiAdd(FullMatrix<DT>& aMatrix , const int row1, const DT& scalar, const int row2)
    {
      aMatrix(row2) += aMatrix(row1) * scalar;
    }
};

#include "GaussianSolver.hpp"
#endif