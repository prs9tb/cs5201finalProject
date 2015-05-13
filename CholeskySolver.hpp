// Programmer: Abira Das, Patrick Sullivan
// Class: CS 5201 (Price)
//CholeskySolver.hpp
//implementations for the CholeskySolver.h file

#include "CholeskySolver.h"
#include "SubstitutionSolver.h"
using std::sqrt;
using std::pow;


template <class DT>
inline Vector<DT> CholeskySolver<DT>::operator()(SymmMatrix<DT>& a, Vector<DT>& b) const
{
	const int dim = b.size();
	Vector<DT> result(dim);
	SubstitutionSolver<DT> solver;
	
	LowerTriMatrix<DT> lower(dim, dim);
	
	//cholesky decomp
	for (int kRow = 0 ; kRow < dim ; kRow ++)
	{
		for (int iCol = 0 ; iCol <= kRow ; iCol++)
		{
			if (kRow == iCol)
			{
				//// Fig 11.4
				DT ele = a.getValue(kRow, kRow);
				for (int jCol = 0 ; jCol < kRow ; jCol++)
					ele -= pow (lower (kRow, jCol) , 2.0);
				ele = sqrt (ele);
				lower (kRow, kRow) = ele;
			}
			else
			{
				//// Fig 11.3
				DT ele = a.getValue(kRow, iCol);
				for (int jCol = 0 ; jCol < iCol ; jCol++)
					ele -= lower (iCol, jCol) * lower (kRow, jCol);
				ele = ele / lower(iCol, iCol);
				lower (kRow, iCol) = ele;
			}
		}
	}
	
	// std::cout<<lower<<std::endl;
	
	// do lower Tri forward sub with b
	Vector<DT> forwardSubVector(dim);
	forwardSubVector = solver(lower, b);

	// do upper tri backward sub with new vector
	UpperTriMatrix<DT> upper(dim, dim);
	upper = lower.transpose();
	result = solver(upper, forwardSubVector);  
	
	return result;
}