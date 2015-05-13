/// Author: Patrick Sullivan
/// Date: 4 - 20 - 2015
/// Class: CS 5201 (Price) 

#ifndef UPPER_TRI_MATRIX_H
#define UPPER_TRI_MATRIX_H

#include <stdexcept>

#include "Vector.h" // Vector class definition
#include "MatrixBase.h"// Matrix interface definition

template <class DT>
class UpperTriMatrix : public virtual MatrixBase<UpperTriMatrix<DT> , DT>
{
	public:
	
		
		// *** ( D E - ) C O N S T R U C T O R S *** //
		
		///\see construct()
		UpperTriMatrix()
		{ construct(0,0); };
		
		///\see construct()
		UpperTriMatrix(unsigned int dims)
		{ construct(dims, dims);  }
		
		///\see construct()
		UpperTriMatrix(const unsigned int rows , const unsigned int cols)
		{	construct(rows, cols);	}
		
		///\see construct()
		template<class MT>
		UpperTriMatrix(const MatrixBase<MT, DT>& source){	construct(source);	}
		
		///\see construct()
		UpperTriMatrix(const UpperTriMatrix<DT>& source) {	construct(source);	}
		
		///\pre allocated data
		///\post deallocates data
		virtual ~UpperTriMatrix() {delete [] m_data;} ;
		
		// *** A S S I G N E M E N T   F U N C T I O N S *** //
		
		///\note deallocates before constructing
		///\see construct()
		virtual UpperTriMatrix<DT>& operator=(const UpperTriMatrix<DT>& rhs);
		
		///\pre DT defines += , matricies align
		///\post matrix data incremented by rhs matrix
		///\throw logic_error if matrices misalign
		virtual UpperTriMatrix<DT>& operator+=(const UpperTriMatrix<DT>& rhs);
		
		///\pre DT defines -= , matricies align
		///\post matrix data decremented by rhs matrix
		///\throw logic_error if matrices misalign
		virtual UpperTriMatrix<DT>& operator-=(const UpperTriMatrix<DT>& rhs);
		
		///\pre DT defines *=
		///\post matrix data is scaled
		virtual UpperTriMatrix<DT>& operator*=(const DT& rhs);
		
		// *** C A L C U L A T I O N   F U N C T I O N S *** //
		
		/// negation math operation, no side effects
		virtual const UpperTriMatrix<DT> operator-() const;
		
		///\pre DT defines = , + , constructors
		///\post dot product of matrix and rhs given
		///\param rhs : const Vector<DT> operand
		const Vector<DT> operator*(const Vector<DT>& rhs) const;
		
		// *** A C C E S S   F U N C T I O N S *** //
		
		///relation and comparison function
		virtual bool equals(const UpperTriMatrix<DT>& other) const;
		
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
		
		virtual const DT& getValue(unsigned int r, unsigned int c) const;
		virtual void setValue(unsigned int r, unsigned int c, const DT& value);
		
	private:
		Vector<DT> * m_data;
		unsigned int m_rows;
		unsigned int m_cols;
		static const DT s_zeroElt;
		
		/// Pre: None
		///Excp: throws out_of_range if index exceeds m_rows
		///Post: accesses the m_data[index] element
		///Desc: reference data accessor
		// virtual Vector<DT>& operator()(unsigned int row);
		/// Pre: None
		///Excp: throws out_of_range if index exceeds m_rows
		///Post: accesses the m_data[index] element
		///Desc: reference data accessor
		// virtual const Vector<DT>& operator()(unsigned int row) const;
		
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
		template <class MT>
		void construct(const MatrixBase<MT, DT>& source);
};

template <class DT> 
const DT UpperTriMatrix<DT>::s_zeroElt = DT(0);

#include "UpperTriMatrix.hpp"

#endif