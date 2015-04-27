/// Programmer: Patrick Sullivan
/// Date: 3 - 15 - 2015
/// Class: CS 5201 (Price)
/// Assignment #4: Matrices and Gaussian Elimination
/// File: Vector.h
/// Purpose: Vector class declarations and function docs

#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector
{
	public:
		// *** ( D E - ) C O N S T R U C T O R S *** //
		
		//Pre : T must have default constructor
		//Post: Vector is constructed for size given, defaults to zero
		//Desc: Default and sized constructor for type T
		Vector(const unsigned int size=0);
		
		//Pre : T defines assignment (=) operator
		//Post: Vector is constructed for size given, filled with copies of eleSource
		//Desc: Sized and default object constructor 
		Vector(const unsigned int size, const T& eleSource);
		
		//Pre : T defines operator= 
		//Post: Vector is constructed, deep copy of source's data
		//Desc: Copy constructor from another vector
		Vector(const Vector<T>& source);
		
		//Pre : T defines operator= ; sourceData points to allocated T array
		//Pre : Length of sourceData >= sourceSize 
		//Post: Vector is constructed, deep copy of sourceData's data pointer
		//Desc: Deep copy constructor from pointer to T array 
		Vector(const unsigned int sourceSize, const T* sourceData);
		
		//Pre : None
		//Post: m_ptr_data is deallocated
		//Desc: Destructor of Vector, deallocates any claimed memeory
		~Vector();
		
		// **** A S S I G N M E N T   F U N C T I O N S **** //
		
		//Pre : T defines operator=
		//Post: Vector is resized and holds copy of data from rhs
		//Desc: Assignment resulting in resize and deep copy
		Vector<T>& operator=(const Vector<T>& rhs);
		
		//Pre : T defines operator +=
		//Excp: invalid_argument if sizes mismatch
		//Post: m_ptr_data elements incremented by rhs.m_ptr_data elements
		//Desc: Vector addition operation
		Vector<T>& operator+=(const Vector<T>& rhs);
		
		//Pre : T defines operator -=
		//Excp: invalid_argument if sizes mismatch
		//Post: m_ptr_data elements decremented by rhs.m_ptr_data elements
		//Desc: Vector subtraction operation
		Vector<T>& operator-=(const Vector<T>& rhs);
		
		//Pre : T defines operator *=
		//Excp: invalid_argument if sizes mismatch
		//Post: m_ptr_data elements multiplied by the scalar
		//Desc: Scalar multiplication operation for vectors
		Vector<T>& operator*=(const T& scalar);
		
		// **** C O N T A I N E R   O P E R A T I O N S **** //
		
		//Pre : T defines operator= and default constructor
		//Post: allocates newSize, deep copies data over, deallocates old mem, m_size = newSize
		//Desc: Creates new size for Vector data structure
		void resize(const unsigned int newSize);
		
		//Pre : T defines operator=
		//Post: all members of other are swap with this objects members
		//Desc: fast - swapping of one vector for another (deep)
		void swap(Vector<T>& other);
		
		//Pre : T defines operator=
		//Post: data ptr holds max amount of data from source, without resizing or out_of_range
		//Desc: Copies as much data from source into Vector as possible without changing m_size
		void fillFrom(const Vector<T>& source);
		
		//Pre : T defines operator=
		//Post: Data ptr now holds m_size copies of eleSource in array
		//Desc: Assigns eleSource to every element in data pointer
		void setAll(const T& eleSource);
		
		// **** E L E M E N T   O P E R A T I O N S **** //
		
		//Pre : None ; throws out_of_range on m_size <= index
		//Post: immutable T from m_ptr_data[index] returned
		//Desc: Index element accessor for data ptr contents
		const T operator[](unsigned const int index) const;
		
		//Pre : None ; throws out_of_range on m_size <= index
		//Post: mutable T reference to m_ptr_data[index] returned
		//Desc: Index element mutator for data ptr contents
		T& operator[](unsigned const int index);
		
		// **** C A L C U L A T I O N   O P E R A T I O R S **** //
		
		//Pre : T defines unary operator- and operator=
		//Post: constructed vector of negated values returned
		//Desc: Negation of vector operation
		const Vector<T> operator-() const;
		
		//Pre : T defines operatior*, operator+, operation=
		//Pre : throws invalid_argument on rhs.m_size!=m_size
		//Post: sum of products of matching elements in vectors returned
		//Desc: Dot Producted of Vectors operation
		const T operator*(const Vector<T>& rhs) const;
		
		// **** R E L A T I O N A L   O P E R A T I O R S **** //
		
		//Pre : T defines == operator
		//Post: returns true if sizes match and if all elements true on ==, otherwise false
		//Desc: Equality test of Vectors operation
		bool operator==(const Vector<T>& rhs) const;
		
		//Pre : T defines == operator
		//Post: returns false if sizes match and if all elements true on ==, otherwise true
		//Desc: InEquality test of Vectors operation
		bool operator!=(const Vector<T>& rhs) const;
		
		// **** A C C E S S   F U N C T I O N S **** //
		
		//Pre : None
		//Post: m_size returned
		//Desc: Accessor to the size of the Vector
		inline unsigned int size() const { return m_size; }
		
		
		
		void swapEle(const unsigned int i1, const unsigned int i2);
		
		
	private:
		// **** D A T A ***** //
		unsigned int m_size;
		T * m_ptr_data;
		
		// ***** H I D D E N   F U N C T I O N A L I T Y **** //
		
		//Pre : m_size < source.m_size ; T defines operator=
		//Post: Data ptr holds deep copies of first m_size elements from source data
		//Desc: Deep copy of source data without resizing 
		void copy(const Vector<T>& source);
};

#include "Vector.hpp"

#endif