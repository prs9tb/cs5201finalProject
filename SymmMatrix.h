/// Author: Patrick Sullivan
/// Date: 4 - 20 - 2015
/// Class: CS 5201 (Price) 

#ifndef SYMM_MATRIX_H
#define SYMM_MATRIX_H

#include "Vector.h" // Vector class definition
#include "MatrixBase.h"// Matrix interface definition

template <class DT>
class SymmMatrix : public virtual MatrixBase<SymmMatrix<DT> , DT>
{
	public:
		
		// *** ( D E - ) C O N S T R U C T O R S *** //
		
		///\see construct()
		SymmMatrix() : SymmMatrix(0,0) {};
		
		///\see construct()
		SymmMatrix(const unsigned int dims) : SymmMatrix(dims,dims) {};
		
		///\see construct()
		SymmMatrix(const unsigned int rows , const unsigned int cols)
		{	construct(rows, cols);	}
		
		///\see construct()
		template<class MT>
		SymmMatrix(const MatrixBase<MT, DT>& source){	construct(source);	}
		
		///\see construct()
		SymmMatrix(const SymmMatrix<DT>& source) {	construct(source);	}
		
		///\pre allocated data
		///\post deallocates data
		virtual ~SymmMatrix() {delete [] m_data;} ;
		
		// *** A S S I G N E M E N T   F U N C T I O N S *** //
		
		///\note deallocates before constructing
		///\see construct()
		SymmMatrix<DT>& operator=(const SymmMatrix<DT>& rhs);
		
		///\pre DT defines += , matricies align
		///\post matrix data incremented by rhs matrix
		///\throw logic_error if matrices misalign
		virtual SymmMatrix<DT>& operator+=(const SymmMatrix<DT>& rhs);
		
		///\pre DT defines -= , matricies align
		///\post matrix data decremented by rhs matrix
		///\throw logic_error if matrices misalign
		virtual SymmMatrix<DT>& operator-=(const SymmMatrix<DT>& rhs);
		
		///\pre DT defines * ; =
		///\post dot product of rows with rhs stored
		///\throw logic_error on matrix misalignment
		virtual SymmMatrix<DT>& operator*=(const SymmMatrix<DT>& rhs);
		
		///\pre DT defines *=
		///\post matrix data is scaled
		virtual SymmMatrix<DT>& operator*=(const DT& rhs);
		
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
		
		/// negation math operation, no side effects
		virtual const SymmMatrix<DT> operator-() const;
		
		///\pre DT defines = , + , constructors
		///\post dot product of matrix and rhs given
		///\param rhs : const Vector<DT> operand
		const Vector<DT> operator*(const Vector<DT>& rhs) const;
		
		// *** A C C E S S   F U N C T I O N S *** //
		
		///relation and comparison function
		virtual bool equals(const SymmMatrix<DT>& other) const;
		
		///rows member accessor
		inline virtual unsigned int rows() const { return m_rows; }
		///cols member accessor
		inline virtual unsigned int cols() const { return m_cols; }
		
		///\post gives m_data information
		///\throw logic_error on bad index or restricted zone
		virtual DT& operator()(unsigned int r, unsigned int c);
		///\post shows m_data information or empty matrix space
		///\throw logic error on bad index
		virtual const DT& operator()(unsigned int r, unsigned int c) const;
		
	private:
		Vector<DT> * m_data;
		unsigned int m_rows;
		unsigned int m_cols;
		static const DT s_zeroElt;
		
		/// Pre: None
		///Excp: throws out_of_range if index exceeds m_rows
		///Post: accesses the m_data[index] element
		///Desc: reference data accessor
		virtual Vector<DT>& operator()(unsigned int row);
		/// Pre: None
		///Excp: throws out_of_range if index exceeds m_rows
		///Post: accesses the m_data[index] element
		///Desc: reference data accessor
		virtual const Vector<DT>& operator()(unsigned int row) const;
		
		/// pure const references to data
		const DT& constAccess(unsigned int r, unsigned int c) const;
		
		///\pre unallocated m_data
		///\post allocated m_data and members sized correctly
		///\param rows: int number of rows in matrix
		///\param cols: int number of cols in matrix
		void construct(unsigned int rows, unsigned int cols);
		
		///\pre unallocated m_data
		///\post allocated m_data and members sized correctly
		///\param source shows data to be copied to here
		void construct(const SymmMatrix<DT>& source);
		template <class MT>
		void construct(const MatrixBase<MT, DT>& source);
		
		///\pre unallocated m_data
		///\post allocated m_data and members sized correctly
		///\param source shows data to be copied to here
		
};

template <class DT> 
const DT SymmMatrix<DT>::s_zeroElt = DT(0);

#include "SymmMatrix.hpp"

#endif