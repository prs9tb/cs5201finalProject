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
		
		//Pre: Symmetric must contain a linearly independent set of vectors
		//passed in augmented Array must be the same size 
		//Post: Uses the Cholesky decomposition, forward substitution, & back substitution 
		//()from SubstitutionSolver) to solve a linearly independent system and returns the result
		//Description: Solves a matrix with Cholesky decomposition for the Solver base class
		virtual Vector<DT> operator()(SymmMatrix<DT>& a, Vector<DT>& b) const;
};

#include "CholeskySolver.hpp"

#endif