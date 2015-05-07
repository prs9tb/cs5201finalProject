/// Programmer: Patrick Sullivan
/// Date: 3 - 15 - 2015
/// Class: CS 5201 (Price)
/// Assignment #4: Matrices and Gaussian Elimination
/// File: GlobalFunctions.hpp
/// Purpose: Global function definitions / implementation

#include "GlobalFunctions.h"
// using std::istream;
// using std::ostream;

long getNow()
{
  auto time = sc::system_clock::now();
  auto since_epoch = time.time_since_epoch();
  auto millis = sc::duration_cast<sc::milliseconds>(since_epoch);
  return millis.count();
}

// *** V E C T O R   C L A S S *** //

template <class T>
istream& operator>>(istream& is, Vector<T>& rhs)
{
	for (int i=0 ; i<rhs.size() ; i++)
		is >> rhs[i];
	return is;
}

template <class T>
ostream& operator<<(ostream& os, const Vector<T>& rhs)
{
	os << "[" ;
	for (int i=0 ; i<rhs.size() ; i++)
	{
		os << rhs[i];
		if (i < rhs.size() -1)
			os << ", ";
	}
	os << "]" ;
	return os;
}

template <class T>
const Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs)
{
	Vector<T> result(lhs);
	result += rhs;
	return result;
}

template <class T>
const Vector<T> operator-(const Vector<T>& lhs, const Vector<T>& rhs)
{
	Vector<T> result(lhs);
	result -= rhs;
	return result;
}


template <class T>
const Vector<T> operator*(const T& scalar, const Vector<T>& rhs)
{
	Vector<T> result(rhs);
	result *= scalar;
	return result;
}


// *** M A T R I X   C L A S S *** //

template <class T>
istream& operator>>(istream& is, FullMatrix<T>& rhs)
{
	for (int i=0 ; i<rhs.rows() ; i++)
		is >> rhs(i);
	return is;
}

template <class MT, class DT>
ostream& operator<<(ostream& os, const MatrixBase<MT, DT>& rhs)
{
	const int rRows = rhs.rows();
	const int rCols = rhs.cols();
	
	os<<"[  ";
	for (int r=0 ; r<rRows ; r++)
	{
		if (r != 0)
			os<<"   ";
		os<<"[ ";
		for (int c=0 ; c<rCols ; c++)
		{
			os<< rhs(r,c);
			
			if (c != rCols-1)
				os<<", ";
		}
		os<<" ]";
		if (r != rRows-1)
			os <<"\n";
	}
	os<<"  ]";
	
	return os;
}


template <class MT, class DT>
const MT operator+(const MatrixBase<MT, DT>& lhs, const MatrixBase<MT, DT>& rhs)
{
	MT result(lhs);
	result += rhs;
	return result;
}

template <class MT, class DT>
const MT operator-(const MatrixBase<MT, DT>& lhs, const MatrixBase<MT, DT>& rhs)
{
	MT result(lhs);
	result -= rhs;
	return result;
}

template <class MT, class DT>
const MT operator*(const MatrixBase<MT, DT>& lhs, const MatrixBase<MT, DT>& rhs)
{
	MT result(lhs);
	result *= rhs;
	return result;
}

template <class MT, class DT>
const MT operator*(const DT& scalar, const MatrixBase<MT, DT>& rhs)
{
	MT result(rhs);
	result *= scalar;
	return result;
}

