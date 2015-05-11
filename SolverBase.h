/// Programmer: Abira Das, Patrick Sullivan
/// Class: CS 5201 (Price)
/// File: SolverBase.h
/// Purpose: Interface Solver Base class


#ifndef SOLVER_BASE_H
#define SOLVER_BASE_H

#include "Vector.h"

template <class MT, class DT>
class SolverBase
{
  public:
    //Pre: Matrix must contain a linearly independent set of vectors
    //Post: For FullMatrix: Uses Gaussian elimination, partialPivoting, and backSubstitution to solve a linearly independent system
    //For Upper and Lower, use backSubstitution or forward substitution methods
    //For Symmetric uses Cholesky decompotition
    //Description: Solves a matrix with Gaussian elimination, Partial Pivoting, and/or back substitution, forward substitution
    //or Cholesky. Uses the most efficient algorithm for the type of Matrix passed in
    virtual Vector<DT> operator()(MT& a, Vector<DT>& b) const = 0;
};

#endif