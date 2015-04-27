/// Programmer: Patrick Sullivan
/// Date: 4 - 16 - 2015
/// Class: CS 5201 (Price)
/// Purpose: Base interface class for use in derivative matrices

#ifndef MATRIX_BASE_H
#define MATRIX_BASE_H

#include "Vector.h"

template <class MT , class DT> 
class MatrixBase
{
	public:
		virtual void getValue(unsigned int row, unsigned int col) const = 0;
		virtual void setValue(unsigned int row, unsigned int col, const DT& value) const = 0;
		
		
		virtual const DT& operator()(unsigned int r, unsigned int c) const = 0;
		virtual DT& operator()(unsigned int r, unsigned int c) = 0;
		
		virtual void row_swap(unsigned int row1, unsigned int row2) = 0;
		virtual void row_multi(unsigned int row, const DT& scalar) = 0;
		virtual void row_multi_add(unsigned int row1, const DT& scalar, unsigned int row2) = 0;
		
		virtual MT& operator+=(const MT& other) = 0;
		virtual MT& operator-=(const MT& other) = 0;
		virtual MT& operator*=(const DT& other) = 0;
		virtual const MT operator-() const = 0;
		
		virtual unsigned int rows() const = 0;
		virtual unsigned int cols() const = 0;
		
		virtual bool equals(const MT& other) const = 0 ;
};


#endif
