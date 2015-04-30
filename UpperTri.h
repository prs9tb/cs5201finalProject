//Abira Das
//assignment 4
//UpperTri.h
//The Upper Triangular Matrix class

#ifndef UPPERTRI_H
#define UPPERTRI_H

#include <iostream>
#include "SuperMatrix.h"

using namespace std;
template <class T>
class UpperTri:public SuperMatrix<T>
{
  private:
    int m_row;
    int m_col;
    T** m_ptr;
  public:
    //Pre: None
    //Post: Sets m_ptr to NULL and m_row and m_col to 0
    //Description: The default constructor for the UpperTri class
    UpperTri();
    //Pre: row and col should be positive
    //Post: Sets m_row to r and m_col to c and m_ptr to an array of arrays
    //Description: The constructor for the UpperTri class
    UpperTri(int row, int col);
    //Pre: None
    //Post: Deletes any data of the calling object's and sets it to the new
    //UpperTri's variables and data, m_ptr will point to new data
    //Description: The copy constructor for the UpperTri class
    UpperTri(const UpperTri<T>& l);
    //Pre: None
    //Post: Deletes any data of the calling object's and sets m_ptr to NULL
    //Description: The destructor for the UpperTri class
    ~UpperTri();
    
    //Pre: None
    //Post: Returns the number of rows
    //Description: Get function for the number of rows in the matr
    int getRow()const;
    //Pre: None
    //Post: Returns the number of columns
    //Description: Get function for the number of columns in the matrix
    int getCol()const;
    //Pre: i must be within # of rows, j must be within # of columns
    //Post: Returns the value at [i][j] if it is in the upper triangular part, otherwise
    //returns 0
    //Description: Accessor function for the values in the matrix
    T getValue(int i, int j);
    //Pre: i and j must be in range of # of rows and columns respectively, as well as
    //in the upper triangular half or the matrix
    //Post: Sets the value at [i][j] if it is in the upper triangular part to value, otherwise
    //throws a range error
    //Description: Set function for the values in the matrix
    void setValue(int i, int j, const T& value);
    
    //Pre: None
    //Post: Sets calling object's data to that of the passed in UpperTri, m_ptr will point to new data
    //Description: The overloaded assignment operator for the UpperTri class
    UpperTri<T>& operator=(const UpperTri<T>& u);
    //Pre: i must be in range of the number of rows or columns in the matrix, cannot change
    //values in the lower half of the matrix
    //Post: Changes value at UpperTri[i]
    //Description: The overloaded bracket operator for the UpperTri class
    T* operator[](int i);
    //Pre: i must be in range of the number of rows or columns in the matrix
    //Post: Returns value at UpperTri[i]
    //Description: The overloaded bracket operator for the UpperTri class
    const T* operator[](int i)const;
    //Pre: rows and columns of one matrix must be equal to the other
    //addition must be defined for type T
    //Post: Adds corresponding data at each index, returns resulting matrix
    //Description: The overloaded addition operator for the UpperTri class
    UpperTri<T> operator+(const UpperTri<T>& u)const;
    //Pre: unary - must be defined for type T, should be a non-null UpperTri
    //Post: Makes each value in the matrix its negative, returns resulting matrix
    //Description: The overloaded unary - operator for the UpperTri class
    UpperTri<T> operator-()const;
    //Pre: unary - and addition must be defined for type T
    //Post: Subtracts corresponding data at each index, returns resulting matrix
    //Description: The overloaded binary - operator for the UpperTri class
    UpperTri<T> operator-(const UpperTri<T>& u)const;
    //Pre: Matrices should have the same size (since both are square)
    //Post: Performs standard matrix multiplication, returns m_row by m_col resulting matrix
    //Description: The overloaded * operator, for multiplying by another matrix, for the UpperTri class
    UpperTri<T> operator*(T& scalar)const;
    //Pre: << operator is defined for type TU
    //Post: Outputs the data at each row and column of the passed in UpperTri, if data is
    //not stored (lower 0's), outputs zeros
    //Description: The overloaded << operator for the UpperTri class
    UpperTri<T> operator*(const UpperTri<T>& u)const;
    template <class TU>
    friend ostream& operator<< (ostream& out, const UpperTri<TU>& u);
    //Pre: rows and columns of the matrix should already be set, the data passed in
    //should be the right number of data points for the space allocated in the UpperTri
    //>> operator is defined for type TU, should be a full matrix (including upper 0's)
    //Post: Sets the data at each row and column of the passed in UpperTri matrix as whatever the input is,
    //ignores lower zeros
    //Description: The overloaded >> operator for the UpperTri class
    template <class TU>
    friend istream& operator>> (istream& is, UpperTri<TU>& u);
    
    //Pre: Should be non null matrix
    //Post: Finds transpose, returns resulting matrix (returns Matrix, not UpperTri) 
    //Description: A function to find and return the transpose of a Upper Triangular matrix
    Matrix<T> transpose();
    //Pre: Should not have 0's in the pivot column
    //Post: Returns an array of answers for a system of vectors by using back substitution on the passed in matrix
    //Description: Back substitution for the Gaussian elimination method
    Array<T> backSub(Array<T> a);
    //Pre: LowerTri must contain a linearly independent set of vectors,  
    //passed in augmented Array must be the same size as m_row
    //Post: Uses backSubstitution to solve a linearly independent system and outputs the result
    //Description: Solves a matrix with back substitution for the Solver class
    Array<T> solver(Array<T>& augment);
};

#include "UpperTri.hpp"
#endif