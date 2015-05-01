// Programmer: Abira Das
// Class: CS 5201 (Price)
//SubstitutionSolver.hpp
//implementations for the SubstitutionSolver.h file

//#include "SubstitutionSolver.h"


template <class DT>
Vector<DT> SubstitutionSolver<DT>::operator()(LowerTriMatrix<DT>& a, Vector<DT>& b)
{
Vector<DT> result(b.size());
DT sum;
result[0] = b[0] / a.getValue(0,0);

int a_row = a.rows();
// forward substitution
for (int row=1 ; row< a_row ; row++)
{
  sum = 0;
  for (int col=0 ; col<=row ; col++)
    sum += a.getValue(row,col) * result[col];
  
  result[row] = (b[row] - sum) / a.getValue(row, row);
}
return result;

}

template <class DT>
Vector<DT> SubstitutionSolver<DT>::operator()(UpperTriMatrix<DT>& a, Vector<DT>& b)
{
Vector<DT> result(b.size());
int a_row = a.rows();
const int end = a_row - 1;
// back substitution
DT sum;
result[end] = (b[end])/a.getValue(end,end);


for (int row=end-1 ; row >=0 ; row--)
{
  sum = 0;
  for (int col=row+1 ; col < a_row ; col++)
    sum += a.getValue(row, col) * result[col];
  
  result[row] = (b[row] - sum) / a.getValue(row,row);
}
return result;

}