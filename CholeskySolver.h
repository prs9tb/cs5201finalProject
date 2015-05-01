/// Programmer: Abira Das, Patrick Sullivan
/// Class: CS 5201 (Price)
/// File: CholeskySolver.h
/// Purpose: Substitution solver class for Upper and Lower
/// Triangular Matrices


#ifndef CHOLESKY_SOLVER_H
#define CHOLESKY_SOLVER_H

#include <iostream>

#include "SolverBase.h"
#include "SymmMatrix.h"
#include "Vector.h"

template <class DT>
class CholeskySolver : public virtual SolverBase<SymmMatrix<DT>, DT>
{
  public:
    CholeskySolver() {}
    Vector<DT> operator()(SymmMatrix<DT>& a, Vector<DT>& b);
};

#include "CholeskySolver.hpp"

#endif