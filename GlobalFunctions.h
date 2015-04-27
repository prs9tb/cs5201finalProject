/// Programmer: Patrick Sullivan
/// Date: 3 - 15 - 2015
/// Class: CS 5201 (Price)
/// Assignment #4: Matrices and Gaussian Elimination
/// File: GlobalFunctions.h
/// Purpose: Global Function declarations and docs


#ifndef GLOBAL_FUNCTIONS_H
#define GLOBAL_FUNCTIONS_H

#include <iostream> // operators << and >>
#include <vector> // std::vector
#include "Vector.h" // Vector class definition
#include "MatrixBase.h" // MatrixBase class definition
#include "FullMatrix.h" // FullMatrix class definition

using std::istream;
using std::ostream;

// *** V E C T O R   C L A S S *** //

//Pre : T defines operator>> behavior
//Post: rhs saves m_size T in data, using >>
//Desc: Insertion operator from raw data into Vector
template <class T>
istream& operator>>(istream& is, Vector<T>& rhs);

//Pre : T defines operator << behavior
//Post: rhs data is writted to os using << ; surrounded with [] and seperated with ', '
//Desc: Extraction operator to display Vector contents nicely
template <class T>
ostream& operator<<(ostream& os, const Vector<T>& rhs);

// Pre: T defines += , =
//Post: New vector returned with sum of component vectors
//Excp: binary + operator for Vectors
template <class T>
const Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs);

// Pre: T defines -= , =
//Post: New vector returned with difference of component vectors
//Excp: binary - operator for Vectors
template <class T>
const Vector<T> operator-(const Vector<T>& lhs, const Vector<T>& rhs);

// Pre: T defines *= , =
//Post: New vector that is component vector elements multiplied by scalar
//Excp: Scalar multiplication operations for Vectors
template <class T>
const Vector<T> operator*(const Vector<T>& lhs, const T& rhs) {return rhs*lhs;}
template <class T>
const Vector<T> operator*(const T& scalar, const Vector<T>& rhs);


// *** M A T R I X   C L A S S *** //

//Pre : T defines operator>> behavior
//Post: rhs copies m_rows of Vectors in data, using >>
//Desc: Insertion operator from raw data into FullMatrix
template <class T>
istream& operator>>(istream& is, FullMatrix<T>& rhs);

//Pre : T defines operator << behavior
//Post: rhs data is written to os using << ; surrounded with [] and separated with '\n'
//Desc: Extraction operator to display Matrix contents nicely
template <class MT, class DT>
ostream& operator<<(ostream& os, const MatrixBase<MT, DT>& rhs);

// Pre: T defines +=
//Post: deep copy of lhs uses += on rhs
//Desc: binary + operator for Matrix addition
template <class MT, class DT>
const MT operator+(const MatrixBase<MT, DT>& lhs, const MatrixBase<MT, DT>& rhs);

// Pre: T defines -=
//Post: deep copy of lhs uses -= on rhs
//Desc: binary - operator for Matrix subtraction
template <class MT, class DT>
const MT operator-(const MatrixBase<MT, DT>& lhs, const MatrixBase<MT, DT>& rhs);

// Pre: T defines * and +
//Post: deep copy of lhs uses *= (dot products of rows&cols) on rhs
//Desc: binary * operator for Matrix Multiplication
template <class MT, class DT>
const MT operator*(const MatrixBase<MT, DT>& lhs, const MatrixBase<MT, DT>& rhs);

// Pre: T defines *=
//Post: deep copy of matrix uses *= with scalar
//Desc: binary * operators for scalar multiplication of Matrices
template <class MT, class DT>
const MT operator*(const DT& scalar, const MatrixBase<MT, DT>& rhs);
template <class MT, class DT>
const MT operator*(const MatrixBase<MT, DT>& lhs, const DT& scalar){return scalar*lhs;}


template <class MT, class DT>
bool operator==(const MatrixBase<MT, DT>& lhs, const MatrixBase<MT, DT>& rhs)
{	return lhs.equals(rhs);   }

template <class MT, class DT>
bool operator!=(const MatrixBase<MT, DT>& lhs, const MatrixBase<MT, DT>& rhs)
{	return ! (lhs.equals(rhs));   }


#include "GlobalFunctions.hpp"

#endif