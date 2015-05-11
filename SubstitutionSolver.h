/// Programmer: Abira Das, Patrick Sullivan
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
    //Pre: LowerTri must contain a linearly independent set of vectors, cannot have negative values
    //in the diagonal, passed in augmented Array must be the same size as m_rows
    //Post: Uses backSubstitution to solve a linearly independent system and outputs the result
    //Description: Solves a matrix with back substitution for the SolverBase class
    
    virtual Vector<DT> operator()(LowerTriMatrix<DT>& a, Vector<DT>& b) const;
    //Pre: UpperTri must contain a linearly independent set of vectors,  
    //passed in augmented Array must be the same size as m_rows
    //Post: Uses backSubstitution to solve a linearly independent system and outputs the result
    //Description: Solves a matrix with back substitution for the SolverBase class
    virtual Vector<DT> operator()(UpperTriMatrix<DT>& a, Vector<DT>& b) const;
};


#include "SubstitutionSolver.hpp"
#endif