/// Programmer: Abira Das & Patrick Sullivan
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
		// \pre:  none
		// \post: solver 
		// \desc: constructor that does nothing.  
		GaussianSolver() {}
		
		// \pre: 0 < a dimensions === b length 
		// \post: a is identity matrix, b is vector of solution
		// \desc: solves matrix a using gaussian elimination and member functions of 
		//        GaussianSolver
		virtual Vector<DT> operator()(FullMatrix<DT>& a, Vector<DT>& b) const;
		
	private:
		int getPivotRow (const FullMatrix<DT> &a, const unsigned int diag) const;

		// \desc: swaps indexes of rows of matrix a
		void rowSwap(FullMatrix<DT>& aMatrix , const int row1, const int row2) const
		{
			aMatrix(row1).swap(aMatrix(row2));
		}
		
		// \desc: multiplies row index of a by scalar
		void rowMulti(FullMatrix<DT>& aMatrix , const int row, const DT& scalar) const
		{
			aMatrix(row) *= scalar;
		}
		
		// \desc: adds to another row another row mulitplied by a scalar
		void rowMultiAdd(FullMatrix<DT>& aMatrix , const int row1, const DT& scalar, const int row2) const
		{
			aMatrix(row2) += aMatrix(row1) * scalar;
		}
		
		//\desc: checks tolerance level of value, changes it to center or other based on member variables
		void tolCheck (DT &num, const DT &center = 0) const;
		
		const double tolerance = .000001;
		const bool forceCenter = true;
		const bool outputNonZeros = false;
};

#include "GaussianSolver.hpp"
#endif