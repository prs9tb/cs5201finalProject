/// Programmer: Patrick Sullivan
/// Date: 3 - 15 - 2015
/// Class: CS 5201 (Price)
/// Assignment #4: Matrices and Gaussian Elimination
/// File: Vector.hpp
/// Purpose: Vector class function definitions / implementation

#include "Vector.h"
#include <stdexcept>

using std::invalid_argument;
using std::out_of_range;

// ****  ( D E - ) C O N S T R U C T O R S **** //
template <class T>
Vector<T>::Vector(const unsigned int size /* =0 */ )
{
	m_size = size;
	m_ptr_data = new T[size];
}

template <class T>
Vector<T>::Vector(const unsigned int size, const T& eleSource)
{
	m_size = size;
	m_ptr_data = new T[size];
	setAll(eleSource);
}

template <class T>
Vector<T>::Vector(const Vector<T>& source)
{
	m_size = source.m_size;
	m_ptr_data = new T[source.m_size];
	copy(source);
}

template <class T>
Vector<T>::Vector(const unsigned int sourceSize, const T* sourceData)
{
	m_size = sourceSize;
	m_ptr_data = new T[sourceSize];
	for (int i=0 ; i<m_size ; i++)
		m_ptr_data[i] = sourceData[i];
}

template <class T>
Vector<T>::~Vector()
{
	delete [] m_ptr_data;
}


// **** A S S I G N M E N T   F U N C T I O N S **** //
template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
	if (rhs.m_ptr_data != m_ptr_data || rhs.m_size != m_size)
	{
		resize(rhs.m_size);
		copy(rhs);
	}
	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& rhs)
{
	if (m_size != rhs.m_size)
		throw invalid_argument("Vector sizes must match for operator+=");
	for (int i=0 ; i<m_size ; i++)
		m_ptr_data[i] += rhs[i];
	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& rhs)
{
	if (m_size != rhs.m_size)
		throw invalid_argument("Vector sizes must match for operator-=");
	for (int i=0 ; i<m_size ; i++)
		m_ptr_data[i] -= rhs[i];
	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator*=(const T& scalar)
{
	for (int i=0 ; i<m_size ; i++)
		m_ptr_data[i] *= scalar;
	return *this;
}

// **** C O N T A I N E R   O P E R A T I O N S **** //
template <class T>
void Vector<T>::resize(const unsigned int newSize)
{
	if (newSize != m_size) 
	{
		T * new_data_ptr = new T[newSize];
		T defaultElement = T();
		for (int i=0 ; i<newSize ; i++)
		{
			if (i < m_size)
				new_data_ptr[i] = m_ptr_data[i];
			else
				new_data_ptr[i] = defaultElement;
		}
		
		delete [] m_ptr_data;
		m_ptr_data = new_data_ptr;
		m_size = newSize;
	}
}

template <class T>
void Vector<T>::swap(Vector<T>& other)
{
	T* oldData = m_ptr_data;
	unsigned int oldSize = m_size;
	
	m_ptr_data = other.m_ptr_data;
	m_size = other.m_size;
	
	other.m_ptr_data = oldData;
	other.m_size = oldSize;
}

template <class T>
void Vector<T>::fillFrom(const Vector<T>& source)
{
	for (unsigned int i=0 ; i<m_size ; i++)
	{
		if (i < source.m_size)
			m_ptr_data[i] = source[i];
	}
}

template <class T>
void Vector<T>::setAll(const T& eleSource)
{
	for (int i=0 ; i<m_size ; i++)
		m_ptr_data[i] = eleSource;
}


// **** E L E M E N T   O P E R A T I O N S **** //
template <class T>
inline const T Vector<T>::operator[](unsigned const int index) const
{
	if (m_size <= index)
		throw out_of_range("m_size <= index");
	return m_ptr_data[index];
}

template <class T>
inline T& Vector<T>::operator[](unsigned const int index)
{    
	if (m_size <= index)
		throw out_of_range("m_size <= index");
	return m_ptr_data[index];
}


// **** C A L C U L A T I O N   O P E R A T O R S **** //
template <class T>
const Vector<T> Vector<T>::operator-() const
{
	Vector<T> result(*this);
	for (int i=0 ; i<result.m_size ; i++)
		result[i] = -result[i];
	return result;
}

template <class T>
const T Vector<T>::operator*(const Vector<T>& rhs) const
{
	if (m_size != rhs.m_size)
		throw invalid_argument("size mismatch!");
	T sumOfProducts = 0;
	for (int i=0 ; i<m_size ; i++)
		sumOfProducts = sumOfProducts + (m_ptr_data[i] * rhs[i]);
	return sumOfProducts;
}


// **** R E L A T I O N A L   O P E R A T O R S **** //
template <class T>
bool Vector<T>::operator==(const Vector<T>& rhs) const
{
	if (m_size != rhs.m_size)
		return false;
	for (int i=0 ; i<m_size ; i++)
		if (! (m_ptr_data[i] == rhs[i]))
			return false;
	return true;
}

template <class T>
bool Vector<T>::operator!=(const Vector<T>& rhs) const
{
	return !(*this == rhs);
}

// ******* P R I V A T E S ******** //
template <class T>
void Vector<T>::copy(const Vector<T>& source)
{
	for (int i=0 ; i<m_size ; i++)
		m_ptr_data[i] = source[i];
}


template <class T>
void Vector<T>::swapEle(const unsigned int i1, const unsigned int i2)
{
	if (i1 == i2) return;
	T temp(operator[](i1));
	operator[](i1) = i2;
	operator[](i2) = temp;
}
