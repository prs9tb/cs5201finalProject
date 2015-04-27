/// Programmer: Patrick Sullivan
/// Date: 3 - 15 - 2015
/// Class: CS 5201 (Price)
/// Assignment #4: Matrices and Gaussian Elimination
/// File: SymmMatrix.hpp
/// Purpose: SymmMatrix class function definitions / implementation

#include <stdexcept>
using std::logic_error;

#include "Vector.h"

template <class T> 
void SymmMatrix<T>::row_swap(unsigned int row1, unsigned int row2)
{
	if (row1 == row2) return;
	throw logic_error("SymmMatrix row_swap causes invalid state");
}

template <class T> 
void SymmMatrix<T>::row_multi(unsigned int row, const T& scalar)
{
	if (scalar == 1) return;
	if (row >= m_rows) 
		logic_error("SymmMatrix row_multi row off matrix");
	throw logic_error("SymmMatrix row_multi always causes invalid state");
}

template <class T> 
void SymmMatrix<T>::row_multi_add(unsigned int source, const T& scalar, unsigned int dest)
{
	if (scalar == 0) return;
	if (source == dest) return row_multi(dest, scalar+1);
	throw logic_error("SymmMatrix row_multi_add causes invalid state");
}

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
			if (ele != source(c,r))
				throw logic_error("SymmMatrix from non-SymmMatrix impossible");
			m_data[r][c] = ele ;
		}
	}
}

template <class DT>
void SymmMatrix<DT>::construct(const SymmMatrix<DT>& source)
{
	m_rows = source.rows();
	m_cols = source.cols();
	m_data = new Vector<DT> [m_rows];
	
	for (int r=0 ; r<m_rows ; r++)
		m_data[r] = source.m_data[r];
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
