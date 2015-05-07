/// Programmer: Abira Das
/// Class: CS 5201 (Price)
/// File: GaussianSolver.h
/// Purpose: Substitution solver class for Upper and Lower
/// Triangular Matrices

#ifndef GAUSSIAN_SOLVER_H
#define GAUSSIAN_SOLVER_H

#include <iostream>

#include "Vector.h"
#include "RangeError.h"
#include "SolverBase.h"
#include "FullMatrix.h"

template <class DT>
class GaussianSolver : public virtual SolverBase<FullMatrix<DT>, DT> 
{
  public:
    GaussianSolver() {}
    virtual Vector<DT> operator()(FullMatrix<DT>& a, Vector<DT>& b) const;
    
  private:
    int getPivotRow (const FullMatrix<DT> &a, const unsigned int diag) const;

  
    void rowSwap(FullMatrix<DT>& aMatrix , const int row1, const int row2) const
    {
      aMatrix(row1).swap(aMatrix(row2));
    }
    
    void rowMulti(FullMatrix<DT>& aMatrix , const int row, const DT& scalar) const
    {
      aMatrix(row) *= scalar;
    }
    
    void rowMultiAdd(FullMatrix<DT>& aMatrix , const int row1, const DT& scalar, const int row2) const
    {
      aMatrix(row2) += aMatrix(row1) * scalar;
    }
    
    void tolCheck (DT &num, const DT &center = 0) const;
    
    const double tolerance = .000001;
    const bool forceCenter = true;
    const bool outputNonZeros = false;
};

#include "GaussianSolver.hpp"
#endif