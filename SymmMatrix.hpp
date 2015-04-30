/// Programmer: Patrick Sullivan
/// Date: 3 - 15 - 2015
/// Class: CS 5201 (Price)
/// Assignment #4: Matrices and Gaussian Elimination
/// File: SymmMatrix.hpp
/// Purpose: SymmMatrix class function definitions / implementation

#include "Vector.h"

using std::logic_error;
using std::sqrt;
using std::pow;

template <class DT>
Vector<DT> SymmMatrix<DT>::solve(const Vector<DT>& b) const
{
  const int dim = b.size();
  Vector<DT> result(dim);
  
  LowerTriMatrix<DT> lower(dim, dim);
  
  for (int kRow = 0 ; kRow < dim ; kRow ++)
  {
    for (int iCol = 0 ; iCol <= kRow ; iCol++)
    {
      if (kRow == iCol)
      {
        //// Fig 11.4
        DT ele = getValue(kRow, kRow);
        for (int jCol = 0 ; jCol < kRow ; jCol++)
          ele -= pow (lower (kRow, jCol) , 2.0);
        ele = sqrt (ele);
        lower (kRow, kRow) = ele;
      }
      else
      {
        //// Fig 11.3
        DT ele = getValue(kRow, iCol);
        for (int jCol = 0 ; jCol < iCol ; jCol++)
          ele -= lower (iCol, jCol) * lower (kRow, jCol);
        ele = ele / lower(iCol, iCol);
        lower (kRow, iCol) = ele;
      }
    }
  }
  
  std::cout<<lower<<std::endl;
  
  
  // cholesky decomp
  // do lower Tri forward sub with b
  // do upper tri backward sub with b
  // return result
  
  
  
  
  return result;
}

template <class DT>
inline const DT& SymmMatrix<DT>::getValue(unsigned int r, unsigned int c) const
{ return operator()(r,c); }


template <class DT>
inline void SymmMatrix<DT>::setValue(unsigned int r, unsigned int c, const DT& value)
{  operator()(r,c) = value;  }


template <class DT>
template <class MT>
void SymmMatrix<DT>::construct(const MatrixBase<MT, DT>& source)
{
	m_rows = source.rows();
	m_cols = source.cols();
	m_data = new Vector<DT> [m_rows];
	
	for (int r=0 ; r<m_rows ; r++)
	{
		const int colMax = (r<m_cols)? r+1 : m_cols;
		m_data[r].resize(colMax);
		
		for (int c=0 ; c<colMax ; c++)
		{
			const DT ele = source(r,c);
			// if (ele != source(c,r))
				// throw logic_error("SymmMatrix from non-SymmMatrix impossible");
			m_data[r][c] = ele;
		}
	}
}

template <class T> 
void SymmMatrix<T>::construct(unsigned int rows, unsigned int cols)
{
	if (rows != cols)
		throw logic_error("SymmMatrix from non-Square matrix impossible");
	m_rows = rows;
	m_cols = cols;
	m_data = new Vector<T> [m_rows];
	
	for (int r=0 ; r<rows ; r++)
	{
		const int colMax = (r<m_cols)? r+1 : m_cols;
		m_data[r].resize(colMax);
	}
}


template <class DT>
SymmMatrix<DT>& SymmMatrix<DT>::operator=(const SymmMatrix<DT>& rhs)
{
	if (m_data == rhs.m_data) return *this;
	delete [] m_data;
	construct(rhs);
	return *this;
}


template <class T>
SymmMatrix<T>& SymmMatrix<T>::operator+=(const SymmMatrix<T>& rhs)
{
	const int rRows = rhs.rows();
	const int rCols = rhs.cols();
	
	if (m_rows != rRows)
		throw logic_error("SymmMatrix += rows not aligned");
	if (m_cols != rCols)
		throw logic_error("SymmMatrix += cols not aligned");
	for (int r=0 ; r<m_rows ; r++)
		(*this)(r) += rhs(r);
	return *this;
}

template <class T>
SymmMatrix<T>& SymmMatrix<T>::operator-=(const SymmMatrix<T>& rhs)
{
	const int rRows = rhs.rows();
	const int rCols = rhs.cols();
	if (m_rows != rRows)
		throw logic_error("SymmMatrix -= rows not aligned");
	if (m_cols != rCols)
		throw logic_error("SymmMatrix -= cols not aligned");
	for (int r=0 ; r<m_rows ; r++)
		operator()(r) -= rhs(r);
	return *this;
}


template <class T>
SymmMatrix<T>& SymmMatrix<T>::operator*=(const SymmMatrix<T>& rhs)
{
	throw logic_error("SymmMatrix *= not possible");
	delete [] m_data;
	construct(rhs);
	return *this;
}


template <class T>
SymmMatrix<T>& SymmMatrix<T>::operator*=(const T& rhs)
{
	for (int r=0 ; r<m_rows ; r++)
		(*this)(r) *= rhs;
	return *this;
}

template <class T>
const SymmMatrix<T> SymmMatrix<T>::operator-() const
{
	SymmMatrix<T> result(*this);
	result *= -1;
	return result;
}

template <class T>
const Vector<T> SymmMatrix<T>::operator*(const Vector<T>& rhs) const
{
	const int rSize = rhs.size();
	if (m_rows != rSize)
		throw logic_error("SymmMatrix * vector row and size not aligned");
	Vector<T> result(rSize);
	for (int c=0 ; c<m_cols ; c++)
		for (int r=0 ; r<m_rows ; r++)
			result[c] += rhs[c] * (*this)(r,c);
	return result;
}

template <class T>
const Vector<T>& SymmMatrix<T>::operator()(unsigned int row) const 
{
	if (m_rows <= row)
		throw logic_error("SymmMatrix (row) const off matrix");
	return m_data[row];
}
template <class T>
Vector<T>& SymmMatrix<T>::operator()(unsigned int row) 
{
	if (m_rows <= row)
		throw logic_error("SymmMatrix (row) reference off matrix");
	return m_data[row]; 
}


template <class DT>
bool SymmMatrix<DT>::equals(const SymmMatrix<DT>& other) const
{
	if (m_rows != other.m_rows) return false;
	if (m_cols != other.m_cols) return false;
	if (m_data == other.m_data) return true;
	
	for (int r=0 ; r<m_rows ; r++)
		if (m_data[r] != other.m_data[r])
			return false;
	return true;
}


template <class T>
inline const T& SymmMatrix<T>::operator()(unsigned int r, unsigned int c) const 
{
	return constAccess(r,c);
}

template <class T>
inline T& SymmMatrix<T>::operator()(unsigned int r, unsigned int c) 
{
	if (r >= m_rows)
		throw logic_error("SymmMatrix (r,c) reference row off matrix");
	if (c >= m_cols)
		throw logic_error("SymmMatrix (r,c) reference col off matrix");
	if (r == c)
		return m_data[r][c];
	return (r>c)? m_data[r][c] : m_data[c][r];
	// throw logic_error("SymmMatrix (r,c) r!=c references are restricted");
}

template <class T>
inline const T& SymmMatrix<T>::constAccess(unsigned int r, unsigned int c) const
{
	if (r >= m_rows)
		throw logic_error("SymmMatrix (r,c) reference row off matrix");
	if (c >= m_cols)
		throw logic_error("SymmMatrix (r,c) reference col off matrix");
	return (r>c)? m_data[r][c] : m_data[c][r];
}
