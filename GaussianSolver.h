/// Programmer: Abira Das
/// Class: CS 5201 (Price)
/// File: GaussianSolver.h
/// Purpose: Substitution solver class for Upper and Lower
/// Triangular Matrices


#ifndef GAUSSIAN_SOLVER_H
#define GAUSSIAN_SOLVER_H

#include "SolverBase.h"
#include "FullMatrix.h"


template <class DT>
class GaussianSolver : public virtual GaussianSolver<FullMatrix<DT>, DT> 
{
  public:
    GaussianSolver() {}
    Vector<DT> operator()(FullMatrix<DT>& a, Vector<DT>& b);
};


#include "GaussianSolver.hpp"
#endif