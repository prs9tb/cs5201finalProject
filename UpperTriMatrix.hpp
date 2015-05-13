/// Programmer: Patrick Sullivan
/// Date: 3 - 15 - 2015
/// Class: CS 5201 (Price)
/// Assignment #4: Matrices and Gaussian Elimination
/// File: UpperTriMatrix.hpp
/// Purpose: UpperTriMatrix class function definitions / implementation

#include "UpperTriMatrix.h"

using std::logic_error;

template <class DT>
inline const DT& UpperTriMatrix<DT>::getValue(unsigned int r, unsigned int c) const
{ return operator()(r,c); }


template <class DT>
inline void UpperTriMatrix<DT>::setValue(unsigned int r, unsigned int c, const DT& value)
{  operator()(r,c) = value;  }


template <class DT>
template <class MT>
void UpperTriMatrix<DT>::construct(const MatrixBase<MT, DT>& source)
{
	m_rows = source.rows ();
	m_cols = source.cols ();
	m_data = new Vector<DT> [m_rows];
	for (int r = 0 ; r < m_rows ; r++)
	{
		const int colMax = (r > m_cols) ? m_cols : m_cols - r ;
		m_data[r].resize (colMax);
		for (int c = r ; c < m_cols ; c++)
			operator () (r, c) = source (r, c);
	}
}

template <class DT> 
void UpperTriMatrix<DT>::construct(unsigned int rows, unsigned int cols)
{
	if (rows != cols)
		throw logic_error("UpperTriMatrix from non-Square matrix impossible");
	m_rows = rows;
	m_cols = cols;
	m_data = new Vector<DT> [m_rows];
	int colMax;
	for (int r = 0 ; r < rows ; r++)
	{
		colMax = (r > m_cols) ? 0 : m_cols - r ;
		m_data[r].resize (colMax);
	}
}


template <class DT>
UpperTriMatrix<DT>& UpperTriMatrix<DT>::operator=(const UpperTriMatrix<DT>& rhs)
{
	if (m_data == rhs.m_data) return *this;
	delete [] m_data;
	construct(rhs);
	return *this;
}


template <class T>
UpperTriMatrix<T>& UpperTriMatrix<T>::operator+=(const UpperTriMatrix<T>& rhs)
{
	const int rRows = rhs.rows();
	const int rCols = rhs.cols();
	
	if (m_rows != rRows)
		throw logic_error("UpperTriMatrix += rows not aligned");
	if (m_cols != rCols)
		throw logic_error("UpperTriMatrix += cols not aligned");
	for (int r=0 ; r<m_rows ; r++)
		m_data[r] += rhs.m_data[r];
		// (*this)(r) += rhs(r);
	return *this;
}

template <class T>
UpperTriMatrix<T>& UpperTriMatrix<T>::operator-=(const UpperTriMatrix<T>& rhs)
{
	const int rRows = rhs.rows();
	const int rCols = rhs.cols();
	if (m_rows != rRows)
		throw logic_error("UpperTriMatrix -= rows not aligned");
	if (m_cols != rCols)
		throw logic_error("UpperTriMatrix -= cols not aligned");
	for (int r=0 ; r<m_rows ; r++)
		m_data[r] -= rhs.m_data[r];
		// operator()(r) -= rhs(r);
	return *this;
}

template <class T>
UpperTriMatrix<T>& UpperTriMatrix<T>::operator*=(const T& rhs)
{
	for (int r=0 ; r<m_rows ; r++)
		m_data[r] *= rhs;
		// (*this)(r) *= rhs;
	return *this;
}

template <class T>
const UpperTriMatrix<T> UpperTriMatrix<T>::operator-() const
{
	UpperTriMatrix<T> result(*this);
	result *= -1;
	return result;
}

template <class T>
const Vector<T> UpperTriMatrix<T>::operator*(const Vector<T>& rhs) const
{
	const int rSize = rhs.size();
	if (m_rows != rSize)
		throw logic_error("UpperTriMatrix * vector row and size not aligned");
	Vector<T> result(rSize);
	for (int c=0 ; c<m_cols ; c++)
		for (int r=0 ; r<m_rows ; r++)
			result[c] += rhs[c] * (*this)(r,c);
	return result;
}

/*
template <class T>
const Vector<T>& UpperTriMatrix<T>::operator()(unsigned int row) const 
{
	if (m_rows <= row)
		throw logic_error("UpperTriMatrix (row) const off matrix");
	return m_data[row];
}
template <class T>
Vector<T>& UpperTriMatrix<T>::operator()(unsigned int row) 
{
	if (m_rows <= row)
		throw logic_error("UpperTriMatrix (row) reference off matrix");
	return m_data[row]; 
}
*/

template <class DT>
bool UpperTriMatrix<DT>::equals(const UpperTriMatrix<DT>& other) const
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
inline const T& UpperTriMatrix<T>::operator()(unsigned int r, unsigned int c) const 
{
	return constAccess(r,c);
}

template <class T>
inline T& UpperTriMatrix<T>::operator()(unsigned int r, unsigned int c) 
{
	if (r >= m_rows)
		throw logic_error("UpperTriMatrix (r,c) reference row off matrix");
	if (c >= m_cols)
		throw logic_error("UpperTriMatrix (r,c) reference col off matrix");
	if (r > c)
		throw logic_error("UpperTriMatrix (r,c) reference to restrited area");
	return m_data[r][c - r];
}

template <class T>
inline const T& UpperTriMatrix<T>::constAccess(unsigned int r, unsigned int c) const
{
	if (r >= m_rows)
		throw logic_error("UpperTriMatrix (r,c) reference row off matrix");
	if (c >= m_cols)
		throw logic_error("UpperTriMatrix (r,c) reference col off matrix");
	if (r > c)
		return s_zeroElt;
	return m_data[r][c - r];
}
