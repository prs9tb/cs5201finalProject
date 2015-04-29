//Abira Das
//assignment 4
//LowerTri.h
//The Lower Triangular Matrix class

#ifndef LOWERTRI_H
#define LOWERTRI_H

#include <iostream>
#include "SuperMatrix.h"
#include "Matrix.h"
#include "UpperTri.h"

using namespace std;
template <class T>
class LowerTri:public SuperMatrix<T>
{
  private:
    int m_row;
    int m_col;
    T** m_ptr;
  public:
    //Pre: None
    //Post: Sets m_ptr to NULL and m_row and m_col to 0
    //Description: The default constructor for the LowerTri class
    LowerTri();
    //Pre: row and col should be positive
    //Post: Sets m_row to r and m_col to c and m_ptr to an array of arrays
    //Description: The constructor for the LowerTri class
    LowerTri(int row, int col);
    //Pre: None
    //Post: Deletes any data of the calling object's and sets it to the new
    //LowerTri's variables and data, m_ptr will point to new data
    //Description: The copy constructor for the LowerTri class
    LowerTri(const LowerTri<T>& l);
    //Pre: None
    //Post: Deletes any data of the calling object's and sets m_ptr to NULL
    //Description: The destructor for the LowerTri class
    ~LowerTri();
        
    //Pre: None
    //Post: Returns the number of rows
    //Description: Get function for the number of rows in the matrix
    int getRow()const;
    //Pre: None
    //Post: Returns the number of columns
    //Description: Get function for the number of columns in the matrix
    int getCol()const;
    
    //Pre: i must be within # of rows, j must be within # of columns
    //Post: Returns the value at [i][j] if it is in the lower triangular part, otherwise
    //returns 0
    //Description: Accessor function for the values in the matrix
    T getValue(int i, int j);
    //Pre: i and j must be in range of # of rows and columns respectively, as well as
    //in the lower triangular half or the matrix
    //Post: Sets the value at [i][j] if it is in the lower triangular part to value, otherwise
    //throws a range error
    //Description: Set function for the values in the matrix
    void setValue(int i, int j, const T& value);
    
    //Pre: None
    //Post: Sets calling object's data to that of the passed in LowerTri, m_ptr will point to new data
    //Description: The overloaded assignment operator for the LowerTri class
    LowerTri<T>& operator=(const LowerTri<T>& l);
    //Pre: i must be in range of the number of rows or columns in the matrix, cannot change
    //values in the upper half of the matrix
    //Post: Changes value at LowerTri[i]
    //Description: The overloaded bracket operator for the LowerTri class
    T* operator[](int i);
    //Pre: i must be in range of the number of rows or columns in the matrix
    //Post: Returns value at LowerTri[i]
    //Description: The overloaded bracket operator for the LowerTri class
    const T* operator[](int i)const;
    //Pre: rows and columns of one matrix must be equal to the other
    //addition must be defined for type T
    //Post: Adds corresponding data at each index, returns resulting matrix
    //Description: The overloaded addition operator for the LowerTri class
    LowerTri<T> operator+(const LowerTri<T>& l)const;
    //Pre: unary - must be defined for type T, should be a non-null LowerTri
    //Post: Makes each value in the matrix its negative, returns resulting matrix
    //Description: The overloaded unary - operator for the LowerTri class
    LowerTri<T> operator-()const;
    //Pre: unary - and addition must be defined for type T
    //Post: Subtracts corresponding data at each index, returns resulting matrix
    //Description: The overloaded binary - operator for the LowerTri class
    LowerTri<T> operator-(const LowerTri<T>& l)const;
    //Pre: multiplication must be defined for type T
    //Post: Multiplies data at each index by T, returns resulting matrix
    //Description: The overloaded * operator, for multiplying by a scalar, for the LowerTri class
    LowerTri<T> operator*(T& scalar)const;
    //Pre: Matrices should have the same size (since both are square)
    //Post: Performs standard matrix multiplication, returns m_row by m_col resulting matrix
    //Description: The overloaded * operator, for multiplying by another matrix, for the LowerTri class
    LowerTri<T> operator*(const LowerTri<T>& l)const;
    //Pre: << operator is defined for type TU
    //Post: Outputs the data at each row and column of the passed in LowerTri, if data is
    //not stored (upper 0's), outputs zeros
    //Description: The overloaded << operator for the LowerTri class
    template <class TU>
    friend ostream& operator<< (ostream& out, const LowerTri<TU>& l);
    //Pre: rows and columns of the matrix should already be set, the data passed in
    //should be the right number of data points for the space allocated in the LowerTri
    //>> operator is defined for type TU, should be a full matrix (including upper 0's)
    //Post: Sets the data at each row and column of the passed in LowerTri matrix as whatever the input is,
    //ignores upper zeros
    //Description: The overloaded >> operator for the LowerTri class
    template <class TU>
    friend istream& operator>> (istream& is, LowerTri<TU>& l);
    
    
    //Pre: Should be non null matrix
    //Post: Finds transpose, returns resulting matrix (returns Matrix, not LowerTri)
    //Description: A function to find and return the transpose of a Lower Triangular matrix
    Matrix<T> transpose();
    //Pre: Should not have 0's in the pivot column
    //Post: Returns an array of answers for a system of vectors by using back substitution on the passed in matrix
    //Description: Back substitution for the Gaussian elimination method
    Array<T> backSub(Array<T> a);
    //Pre: LowerTri must contain a linearly independent set of vectors, cannot have negative values
    //in the diagonal, passed in augmented Array must be the same size as m_row
    //Post: Uses backSubstitution to solve a linearly independent system and outputs the result
    //Description: Solves a matrix with back substitution for the Solver class
    Array<T> solver(Array<T>& augment);
};

#include "LowerTri.hpp"
#endif