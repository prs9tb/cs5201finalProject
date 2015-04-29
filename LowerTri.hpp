//Abira Das
//Assignment 4
//LowerTriangular.hpp
//The implementation class for a Matrix

#include <iostream>
using namespace std;

#include <cstdlib>
#include <cmath>
#include "RangeError.h"

//-------------------------------------------------------//

template <class T>
LowerTri<T>::LowerTri()
{
  m_ptr = NULL;
  m_row = 0;
  m_col = 0;
}

template <class T>
LowerTri<T>::LowerTri(int r, int c)
{
  m_ptr = new T*[r];
  m_row = r;
  m_col = c;

  for(int i=0;i<r;i++)
  {
    m_ptr[i] = new T[i+1];
  }
  
  T tmp=0; 
  for(int i=0; i < m_row; i ++)
  {
    for(int j=0; j < i+1; j ++)
    { 
      m_ptr[i][j] = tmp;
    }
  }
  
}

template <class T>
LowerTri<T>::LowerTri(const LowerTri<T>& l)
{
/*
  if(m_ptr == NULL)
  {
    for(int i=0;i<m_row;i++)
    {
      delete [] m_ptr[i];
    }
    delete [] m_ptr;
  }
*/  
  m_row = l.m_row;
  m_col = l.m_col;
  
  m_ptr = new T*[m_row];
  
  for(int i =0; i < m_row; i ++)
  {
    m_ptr[i] = new T[i+1];    
  }
  
  for(int i =0; i < m_row; i ++)
  {
    for(int j =0; j < i+1; j ++)
    {
      m_ptr[i][j] = l[i][j];
    }
  } 
}

template <class T>
LowerTri<T>::~LowerTri()
{
  if(m_ptr == NULL)
    return;
  
  for(int i=0;i<m_row;i++)
  {
    delete [] m_ptr[i];
  }
  delete [] m_ptr;
  
  m_ptr = NULL;
  m_row = 0;
  m_col = 0;
  
}

//--------------------------------------------------------------//

template <class T>
LowerTri<T>& LowerTri<T>::operator=(const LowerTri<T>& l)
{
  m_row = l.m_row;
  m_col = l.m_col;
  
  for(int i=0;i<m_row;i++)
  {
     delete [] m_ptr[i];
  }
  delete [] m_ptr;
  
  m_ptr = new T*[m_row];
  
  for(int i =0; i < m_row; i ++)
  {
    m_ptr[i] = new T[i+1];    
  } 
  
  //set stuff =
  for(int i =0; i < m_row; i ++)
  {
    for(int j =0; j < i+1; j ++)
    {
      m_ptr[i][j] = l[i][j];
    }
  } 
  return (*this);
}


//**********
//i must be in range
template <class T>
T* LowerTri<T>::operator[](int i)
{
  if(i > m_row)
  {
    throw RangeError(i);
  }
  return m_ptr[i];
}

//**********
//i must be in range
template <class T>
const T* LowerTri<T>::operator[](int i)const
{
  if(i > m_row)
  {
    throw RangeError(i);
  }
  return m_ptr[i];
}

template <class T>
LowerTri<T> LowerTri<T>::operator+(const LowerTri<T>& l)const
{
	if(m_row != l.m_row && m_col != l.m_col)
		throw SizeError(m_row);

  LowerTri<T> newL(m_row, m_col);
  
  for(int i = 0; i < m_row; i ++)
  {
    for(int j = 0; j < i+1; j++)
    {
      newL[i][j] = (*this)[i][j] + l[i][j];
    }
  }
  return(newL);
}

template <class T>
LowerTri<T> LowerTri<T>::operator-()const
{
  LowerTri<T> newL(m_row, m_col);
  for(int i = 0; i < m_row; i ++)
  {
    for(int j = 0; j < i+1; j++)
    {
      newL[i][j] = -(*this)[i][j];
    }
  }
  return(newL);
}


template <class T>
LowerTri<T> LowerTri<T>::operator-(const LowerTri<T>& l)const
{

	if(m_row != l.m_row && m_col != l.m_col)
		throw SizeError(m_row);

  LowerTri<T> newL(m_row, m_col);
  
  for(int i = 0; i < m_row; i ++)
  {
    for(int j = 0; j < i+1; j++)
    {
      newL[i][j] = (*this)[i][j] + (-l[i][j]);
    }
  }
  return(newL);

}

template <class T>
LowerTri<T> LowerTri<T>::operator*(T& scalar)const
{
  LowerTri<T> newL(m_row, m_col);
  for(int i = 0; i < m_row; i ++)
  {
    for(int j = 0; j < i+1; j++)
    {
      newL[i][j] = (*this)[i][j] * scalar;
    }
  }
  return(newL);
}


template <class T>
LowerTri<T> LowerTri<T>::operator*(const LowerTri<T>& l)const
{
  //columns of first must equal rows of second
	if(m_col != l.m_row)
  {
	  throw SizeError(m_col);
  }
  
  LowerTri<T> newL(m_row, m_col);
  int sum=0;
  
  for(int i =0; i < m_row; i ++)
  {
    for(int j=0;j <= i; j ++)
    {
      sum=0;
      for(int k=j;k<=i; k++ )
      {
        sum += (*this)[i][k] * l[k][j];
      }
      newL[i][j]=sum;
    }
  }
  return newL;
}

template <class T>
Matrix<T> LowerTri<T>::transpose()
{
  Matrix<T> newM(m_col, m_row);

  for(int i =0; i < m_col; i ++)
  {
    for(int j =0; j < m_row; j ++)
    {
      if(j <=i)
      {
        newM[j][i] = (*this)[i][j]; //switch appropriate numbers
      }
      else
      {
       newM[j][i] = 0; //switch appropriate numbers
      }
    } 
  }
  cout << newM << endl;
  return(newM);
}

template <class TU>
istream& operator>>(istream& is, LowerTri<TU>& l)
{
  TU a;   //takes the extra zeros
  for(int i =0; i < l.m_row; i ++)
  {
    for(int j =0; j < l.m_col; j ++)
    {
      if(j <= i)
      {
        is >> l.m_ptr[i][j];
      }
      else{
        is >> a;
      }
    }
  }
  return is;
}

template <class TU>
ostream& operator<< (ostream& out, const LowerTri<TU>& l)
{

  for(int i =0; i < l.m_row; i ++)
    {
      for(int j =0;j < l.m_col; j ++)
      {
        if(j <=i)
        {
          out << l.m_ptr[i][j] << " ";
        }
        else
        {
          out << "0 ";
        }
      }
      out << endl;
    }
  return out;
}

//-------------------------------------------------------//

template <class T>
int LowerTri<T>::getRow()const
{
  return(m_row);
}

template <class T>
int LowerTri<T>::getCol()const
{
  return(m_col);
}

template <class T>
T LowerTri<T>::getValue(int i, int j)
{
if(i > m_row || j > m_col)
  {
    throw RangeError(i);
  }
  
  if(j<=i)
  {
    return (m_ptr[i][j]);
  }
  else
  {
    return(0);
  }
}

template <class T>
void LowerTri<T>::setValue(int i, int j, const T& value)
{
  if(i > m_row)
  {
    throw RangeError(i);
  }
  
  if(j<=i)
  {
    m_ptr[i][j] = value;
  }
  else
  {
    throw RangeError(i);
  }
}

//---------------------------------------------------//
template <class T>
Array<T> LowerTri<T>::backSub(Array<T> a)
{
  T sum = 0;
  Array<T> answers(m_row);
  //cout << a << endl;
  answers[0] = a[0]/(*this)[0][0];
  //sets first solution to the last augmented matrix number divided by the
  //last variable's cofefficient

  //cout << "x1 is " << answers[0] << endl;
  
  for(int i=1; i < m_row; i++) //go through rows
  {
    sum = 0;
    for(int j=0; j <=i; j ++) //sum up cols with known answers
    {
      sum += (*this)[i][j]*answers[j];
    }

    answers[i] = (a[i] - sum)/((*this)[i][i]); //augmented col - sum/ pivot
    if(abs(answers[i]) < 0.000000001)	//round to 0
    {
      answers[i] = 0;
    }
    //cout << "x" << i+1 << " is " << answers[i] << endl;
  }
  return(answers);
}

template <class T>
Array<T> LowerTri<T>::solver(Array<T>& augment)
{

  return( backSub(augment));

}
