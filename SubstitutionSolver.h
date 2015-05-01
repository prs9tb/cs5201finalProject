/// Programmer: Abira Das
/// Class: CS 5201 (Price)
/// File: SubstitutionSolver.h
/// Purpose: Substitution solver class for Upper and Lower
/// Triangular Matrices


#ifndef SUBSTITUTIONSOLVER_H
#define SUBSTITUTIONSOLVER_H

#include <iostream>

#include "SolverBase.h"
#include "Vector.h"
#include "UpperTriMatrix.h"
#include "LowerTriMatrix.h"


template <class DT>
class SubstitutionSolver : public virtual SolverBase<LowerTriMatrix<DT>, DT> ,
                           public virtual SolverBase<UpperTriMatrix<DT>, DT>
{
  public:
    SubstitutionSolver() {}
    virtual Vector<DT> operator()(LowerTriMatrix<DT>& a, Vector<DT>& b) const;
    virtual Vector<DT> operator()(UpperTriMatrix<DT>& a, Vector<DT>& b) const;
};


#include "SubstitutionSolver.hpp"
#endif