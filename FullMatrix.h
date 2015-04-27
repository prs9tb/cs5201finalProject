/// Author: Patrick Sullivan
/// Date: 4 - 20 - 2015
/// Class: CS 5201 (Price) 

#ifndef FULL_MATRIX_H
#define FULL_MATRIX_H

#include "Vector.h" // Vector class definition
#include "MatrixBase.h"// Matrix interface definition

template <class DT>
class FullMatrix : public virtual MatrixBase<FullMatrix<DT> , DT>
{
	public:
		
		// *** ( D E - ) C O N S T R U C T O R S *** //
		
		///\see construct()
		FullMatrix(){	construct(0, 0);	}
		
		///\see construct()
		FullMatrix(const unsigned int dims)
		{	construct(dims, dims);	}
		
		///\see construct()
		FullMatrix(const unsigned int rows , const unsigned int cols)
		{	construct(rows, cols);	}
		
		///\see construct()
		FullMatrix(const FullMatrix<DT>& source) {	construct(source); }
		///\see construct()
		template<class MT>
		FullMatrix(const MatrixBase<MT, DT>& source) {	construct(source); }
		
		///\pre m_data is allocated , no other references
		///\post m_data is deallocated and *this is destroyed
		virtual ~FullMatrix() {	delete [] m_data;	}
		
		// *** C O N T A I N E R   F U N C T I O N S *** //
		
		// Pre: DT has default constructor
		//Post: m_data deleted, reallocated to new dimensions
		//Desc: resize m_data to new dimensions
		void resize(const unsigned int rows , const unsigned int cols);
		
		// *** A S S I G N E M E N T   F U N C T I O N S *** //
		
		///\note deallocates m_data before construction
		///\see construct()
		template <class MT>
		FullMatrix<DT>& operator=(const MatrixBase<MT, DT>& rhs);
		
		///\note deallocates m_data before construction
		///\see construct()
		FullMatrix<DT>& operator=(const FullMatrix<DT>& rhs);
		
		// Pre: DT defines += operator
		//Excp: throws invalid_argument if dimensions mismatch
		//Post: m_data elements incremented by rhs.m_data elements
		//Desc: FullMatrix addition operation
		template <class MT>
		FullMatrix<DT>& operator+=(const MatrixBase<MT, DT>& rhs);
		virtual FullMatrix<DT>& operator+=(const FullMatrix<DT>& rhs);
		
		// Pre: DT defines -= operator
		//Excp: throws invalid_argument if dimensions mismatch
		//Post: m_data elements decremented by rhs.m_data elements
		//Desc: FullMatrix subtraction operation
		template <class MT>
		FullMatrix<DT>& operator-=(const MatrixBase<MT, DT>& rhs);
		virtual FullMatrix<DT>& operator-=(const FullMatrix<DT>& rhs);
		
		// Pre: DT defines *= operator
		//Excp: throws invalid_argument if col*row mismatch
		//Post: m_data elements become dot product of row and col of Matricies
		//Desc: FullMatrix multiplication operation
		template <class MT>
		FullMatrix<DT>& operator*=(const MatrixBase<MT, DT>& rhs);
		virtual FullMatrix<DT>& operator*=(const FullMatrix<DT>& rhs);
		
		// Pre: DT defines *= operator
		//Post: m_data elements muliplied by scalar
		//Desc: scalar-FullMatrix multiplication operaton
		virtual FullMatrix<DT>& operator*=(const DT& rhs);
		
		// *** M A T R I X   M A N I P U L A T I O N *** //
		///\pre DT has = 
		///\post rows are swapped
		///\throw logic_error on invalid matrix state
		///\param row1 and row2 int indexes of rows
		virtual void row_swap(unsigned int row1, unsigned int row2);
		
		///\pre DT has = * 
		///\post row in matrix is scaled
		///\param row int index
		///\param DT scalar for multiplication
		///\throw logic_error on bad row index
		virtual void row_multi(unsigned int row, const DT& scalar);
		
		///\pre DT has +, *, =
		///\post destination row is increased by scaled source row
		///\param source: int row index 
		///\param scalar: DT modifier of source row
		///\param dest: int row index 
		///\throw logic_error on invalid matrix state
		virtual void row_multi_add(unsigned int source, const DT& scalar, unsigned int dest);
		
		// *** C A L C U L A T I O N   F U N C T I O N S *** //
		
		// Pre: DT defines = and unary -
		//Post: m_data elements are negated
		//Desc: FullMatrix negation operation
		virtual const FullMatrix<DT> operator-() const;
		
		// Pre: DT has default constructor, =, +, *
		//Excp: throws invalid_argument if rows-size mismatch
		//Post: m_data elements dot rhs to form resulting multiplication vector
		//Desc: FullMatrix-Vector multiplication operation
		const Vector<DT> operator*(const Vector<DT>& rhs) const;
		
		// Pre: DT defines =
		//Post: dimensions swap and m_data elements swap positions
		//Desc: FullMatrix Transpose operation
		const FullMatrix<DT> transpose() const;
		
		// *** R E L A T I O N A L   F U N C T I O N S *** //
		virtual bool equals(const FullMatrix<DT>& other) const;
		
		// *** A C C E S S   F U N C T I O N S *** //
		virtual DT& operator()(unsigned int r, unsigned int c);
		virtual const DT& operator()(unsigned int r, unsigned int c) const;
		
		// Pre: None
		//Excp: throws out_of_range if index exceeds m_rows
		//Post: accesses the m_data[index] element
		//Desc: row data accessor
		virtual Vector<DT>& operator()(unsigned int row);
		virtual const Vector<DT>& operator()(unsigned int row) const;
		
		// Pre: None
		//Post: dimension is returned
		//Desc: accessor to size of containers
		inline virtual unsigned int rows() const { return m_rows; }
		inline virtual unsigned int cols() const { return m_cols; }
		
	private:
		Vector<DT> * m_data;
		unsigned int m_rows;
		unsigned int m_cols;
		static const DT s_zeroElt;
		
		///\pre unallocated m_data
		///\post allocated m_data and members sized correctly
		///\param source shows data to be copied to here
		template <class MT>
		void construct(const MatrixBase<MT, DT>& source);
		
		///\pre unallocated m_data
		///\post allocated m_data and members sized correctly
		///\param rows: int number of rows in matrix
		///\param cols: int number of cols in matrix
		void construct(unsigned int rows, unsigned int cols);
};

template <class DT>
const DT FullMatrix<DT>::s_zeroElt = DT();

#include "FullMatrix.hpp"

#endif