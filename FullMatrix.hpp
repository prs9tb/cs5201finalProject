/// Author: Patrick Sullivan
/// Date: 4 - 20 - 2015
/// Class: CS 5201 (Price) 

#include <stdexcept>
using std::logic_error;

#include "FullMatrix.h"

template <class DT>
Vector<DT> FullMatrix<DT>::solve(const Vector<DT>& b) const
{
  Vector<DT> result(b.size());
  // do gaussian elimination
  return result;
}




template <class DT> 
inline const DT& FullMatrix<DT>::getValue(unsigned int r, unsigned int c) const
{ return operator()(r,c); }

template <class DT> 
inline void FullMatrix<DT>::setValue(unsigned int r, unsigned int c, const DT& value)
{ operator()(r,c) = value;  }

template <class T> 
void FullMatrix<T>::row_swap(unsigned int row1, unsigned int row2)
{
	(*this)(row1).swap((*this)(row2));
}

template <class T> 
void FullMatrix<T>::row_multi(unsigned int row, const T& scalar)
{
	(*this)(row) *= scalar;
}

template <class T> 
void FullMatrix<T>::row_multi_add(unsigned int source, const T& scalar, unsigned int dest)
{
	(*this)(dest) += (*this)(source) * scalar;
}


template <class DT> 
void FullMatrix<DT>::construct(unsigned int rows, unsigned int cols)
{
	m_rows = rows;
	m_cols = cols;
	m_data = new Vector<DT> [m_rows];
	for (int r=0 ; r<m_rows ; r++)
		m_data[r].resize(m_cols);
}

template <class DT> 
template <class MT>
void FullMatrix<DT>::construct(const MatrixBase<MT, DT>& source)
{
	m_rows = source.rows();
	m_cols = source.cols();
	m_data = new Vector<DT> [m_rows];
	
	for (int r=0 ; r<m_rows ; r++)
	{
		m_data[r].resize(m_cols);
		for (int c=0 ; c<m_cols ; c++)
			m_data[r][c] = source(r,c);
	}
}

template <class DT>
FullMatrix<DT>& FullMatrix<DT>::operator=(const FullMatrix<DT>& rhs)
{
	if (m_data == rhs.m_data) return *this;
	delete [] m_data;
	construct(rhs);
	return *this;
}

template <class DT>
template <class MT>
FullMatrix<DT>& FullMatrix<DT>::operator=(const MatrixBase<MT, DT>& rhs)
{
	if (m_data == rhs.m_data) return *this;
	delete [] m_data;
	construct(rhs);
	return *this;
}

template <class DT>
template <class MT>
FullMatrix<DT>& FullMatrix<DT>::operator+=(const MatrixBase<MT, DT>& rhs)
{
	const int rRows = rhs.rows();
	const int rCols = rhs.cols();
	if (m_rows != rRows || m_cols != rCols)
		throw logic_error("FullMatrix += matrices don't align");
	for (int r=0 ; r<m_rows ; r++)
		for (int c=0 ; c<m_cols ; c++)
			operator()(r,c) += rhs(r,c);
	return *this;
}
template <class DT>
template <class MT>
FullMatrix<DT>& FullMatrix<DT>::operator-=(const MatrixBase<MT, DT>& rhs)
{
	const int rRows = rhs.rows();
	const int rCols = rhs.cols();
	if (m_rows != rRows || m_cols != rCols)
		throw logic_error("FullMatrix -= matrices don't align");
	for (int r=0 ; r<m_rows ; r++)
		for (int c=0 ; c<m_cols ; c++)
			operator()(r,c) -= rhs(r,c);
	return *this;
}


template <class DT>
template <class MT>
FullMatrix<DT>& FullMatrix<DT>::operator*=(const MatrixBase<MT, DT>& rhs)
{
	const int resultRows = m_rows;
	const int resultCols = rhs.cols();
	const int rRows = rhs.rows();
	const int rCols = rhs.cols();
	
	if (m_cols != rRows)
		throw logic_error("FullMatrix *= matrices don't align");
	
	Vector<DT> * newData = new Vector<DT>[m_rows];
	for (int r=0 ; r<m_rows ; r++)
		newData[r].resize(rCols);
	
	
	for (int r=0 ; r<m_rows ; r++)
		for (int c=0 ; c<rCols ; c++)
			for (int i=0 ; i<m_rows ; i++)
				newData[r][c] += operator()(r,i) * rhs(i,c);
	
	
	delete [] m_data;
	m_data = newData;
	m_rows = resultRows;
	m_cols = resultCols;
	return *this;
}

template <class T> 
void FullMatrix<T>::resize(const unsigned int rows , const unsigned int cols)
{
	if (m_rows != rows && m_cols != cols)
	{
		Vector<T> * newData = new Vector<T>[rows];
		
		for (int i=0 ; i<rows ; i++)
		{
			// this part can be optimized using iterators
			if ( i < m_rows )
				newData[i] = m_data[i];
			newData[i].resize(cols);
		}
		
		delete [] m_data;
		m_data = newData;
	}
	else if (m_rows != rows)
	{
		Vector<T> * newData = new Vector<T>[rows];
		
		for (int i=0 ; i<rows ; i++)
		{
			if (i < m_rows)
				newData[i] = m_data[i];
			else
				newData[i].resize(cols);
		}
		
		delete [] m_data;
		m_data = newData;
	}
	else if (m_cols != cols)
	{
		for (int i=0 ; i<rows ; i++)
			m_data[i].resize(cols);
	}
	
	m_rows = rows;
	m_cols = cols;
}


template <class T>
FullMatrix<T>& FullMatrix<T>::operator+=(const FullMatrix<T>& rhs)
{
	const int rRows = rhs.rows();
	const int rCols = rhs.cols();
	if (m_rows != rRows)
		throw logic_error("FullMatrix += rows don't align");
	else if (m_cols != rCols)
		throw logic_error("FullMatrix += cols don't align");
	for (int r=0 ; r<m_rows ; r++)
		(*this)(r) += rhs(r);
	return *this;
}

template <class T>
FullMatrix<T>& FullMatrix<T>::operator-=(const FullMatrix<T>& rhs)
{
	const int rRows = rhs.rows();
	const int rCols = rhs.cols();
	if (m_rows != rRows)
		throw logic_error("FullMatrix -= rows don't align");
	else if (m_cols != rCols)
		throw logic_error("FullMatrix -= cols don't align");
	for (int r=0 ; r<m_rows ; r++)
		(*this)(r) -= rhs(r);
	return *this;
}


template <class DT>
FullMatrix<DT>& FullMatrix<DT>::operator*=(const FullMatrix<DT>& rhs)
{
	const int resultRows = m_rows;
	const int resultCols = rhs.cols();
	const int rRows = rhs.rows();
	const int rCols = rhs.cols();
	
	if (m_cols != rRows)
		throw logic_error("FullMatrix *= matrices don't align");
	
	Vector<DT> * newData = new Vector<DT>[m_rows];
	for (int r=0 ; r<m_rows ; r++)
		newData[r].resize(rCols);
	
	for (int r=0 ; r<m_rows ; r++)
		for (int c=0 ; c<rCols ; c++)
			for (int i=0 ; i<m_rows ; i++)
				newData[r][c] += operator()(r,i) * rhs(i,c);
	
	
	delete [] m_data;
	m_data = newData;
	m_rows = resultRows;
	m_cols = resultCols;
	return *this;
}


template <class T>
FullMatrix<T>& FullMatrix<T>::operator*=(const T& rhs)
{
	for (int r=0 ; r<m_rows ; r++)
		(*this)(r) *= rhs;
	return *this;
}

template <class T>
const FullMatrix<T> FullMatrix<T>::operator-() const
{
	FullMatrix<T> result(*this);
	for (int r=0 ; r<result.m_rows ; r++)
		result(r) = -result(r);
	return result;
}

template <class T>
const Vector<T> FullMatrix<T>::operator*(const Vector<T>& rhs) const
{
	const int rSize = rhs.size();
	if (m_rows != rSize)
		throw logic_error("FullMatrix * vector rows don't align");
	Vector<T> result(rSize);
	for (int r=0 ; r<m_rows ; r++)
		result(r) = rhs*(*this)(r);
	return result;
}

template <class T>
const FullMatrix<T> FullMatrix<T>::transpose() const
{
	FullMatrix<T> result(m_cols, m_rows);
	for (int r=0 ; r<m_rows ; r++)
		for (int c=0 ; c<m_cols ; c++)
			result(c,r) = (*this)(r,c);
	return result;
}

template <class T>
inline Vector<T>& FullMatrix<T>::operator()(unsigned int row) 
{
	if (row >= m_rows)
		throw logic_error("FullMatrix (row) reference row off matrix");
	return m_data[row]; 
}
template <class T>
inline const Vector<T>& FullMatrix<T>::operator()(unsigned int row) const 
{
	if (row >= m_rows)
		throw logic_error("FullMatrix (row) const row off matrix");
	return m_data[row];
}

template <class DT>
bool FullMatrix<DT>::equals(const FullMatrix<DT>& other) const
{
	if (m_rows != other.m_rows) return false;
	if (m_cols != other.m_cols) return false;
	if (m_data == other.m_data) return true;
	
	for (int r=0 ; r<m_rows ; r++)
		for (int c=0 ; c<m_cols ; c++)
			if (m_data[r][c] != other.m_data[r][c])
				return false;
	return true;
}

template <class T>
inline T& FullMatrix<T>::operator()(unsigned int r, unsigned int c) 
{
	if (m_rows <= r)
		throw logic_error("FullMatrix (r,c) reference row off matrix");
	if (m_cols <= c)
		throw logic_error("FullMatrix (r,c) reference col off matrix");
	return m_data[r][c];
}

template <class T>
inline const T& FullMatrix<T>::operator()(unsigned int r, unsigned int c) const 
{
	if (m_rows <= r)
		throw logic_error("FullMatrix (r,c) const row off matrix");
	if (m_cols <= c)
		throw logic_error("FullMatrix (r,c) const col off matrix");
	return m_data[r][c];
}
