/// Programmer: Abira Das
/// Class: CS 5201 (Price)
/// File: SubstitutionSolver.h
/// Purpose: Substitution solver class for Upper and Lower
/// Triangular Matrices


#ifndef SUBSTITUTIONSOLVER_H
#define SUBSTITUTIONSOLVER_H


#include "UpperTriMatrix.h"
#include "LowerTriMatrix.h"


template <class DT>
class SubstitutionSolver : public virtual SolverBase<LowerTriMatrix<DT>, DT> ,
                           public virtual SolverBase<UpperTriMatrix<DT>, DT>
{
  public:
    SubstitutionSolver() {}
    Vector<DT> operator()(LowerTriMatrix<DT>& a, Vector<DT>& b);
    Vector<DT> operator()(UpperTriMatrix<DT>& a, Vector<DT>& b);
};


#include "SubstitutionSolver.hpp"
#endif