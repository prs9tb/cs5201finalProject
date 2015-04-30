//Abira Das
//Assignment 4
//UpperTri.hpp
//The implementation class for a Matrix

#include <iostream>
using namespace std;

#include <cstdlib>
#include <cmath>
#include "RangeError.h"

template <class T>
UpperTri<T>::UpperTri()
{
  m_row = 0;
  m_col = 0;
  m_ptr = NULL;
  
}

template <class T>
UpperTri<T>::UpperTri(int row, int col)
{
  m_ptr = new T*[row];
  m_row = row;
  m_col = col;

  for(int i=0;i<row;i++)
  {
    m_ptr[i] = new T[m_row-i];
  }
  T temp = 0;
  for(int i =0; i < m_row; i ++)
  {
    for(int j =0; j < m_col-i; j ++)
    {
      m_ptr[i][j] = temp;
    }
  }
  
}
  
template <class T>
UpperTri<T>::UpperTri(const UpperTri<T>& u)
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
  m_row = u.m_row;
  m_col = u.m_col;
  
  m_ptr = new T*[m_row];
  
  for(int i=0;i<m_row;i++)
  {
    m_ptr[i] = new T[m_row-i];
  }
  
  for(int i =0; i < m_row; i ++)
  {
    for(int j =0; j < m_col-i; j ++)
    {
      m_ptr[i][j] = u[i][j];
    }
  }
  
}

template <class T>
UpperTri<T>::~UpperTri()
{
  
  if(m_ptr == NULL)
  {
    return;
  }
  
  for(int i=0;i<m_row;i++)
  {
     delete [] m_ptr[i];
  }
  delete [] m_ptr;
  
  m_ptr = NULL;
  m_row = 0;
  m_col = 0;
  
}
 
//-------------------------------------------------------//

template <class T>
int UpperTri<T>::getRow()const
{
  return(m_row);
}

template <class T>
int UpperTri<T>::getCol()const
{
  return(m_col);
}

template <class T>
T UpperTri<T>::getValue(int i, int j)
{
  if(i > m_row)
  {
    throw RangeError(i);
  }
  if(j>=i)
  {
    return (m_ptr[i][j-i]);
  }
    return(0);
}

template <class T>
void UpperTri<T>::setValue(int i, int j, const T& value)
{
  if(i > m_row)
  {
    throw RangeError(i);
  }
  
  if(j>=i)
  {
    m_ptr[i][j-i] = value;
  }
  else
  {
    throw RangeError(i);
  }
}
    
//----------------------------------OPERATORS------------------------//

template <class T>
UpperTri<T>& UpperTri<T>::operator=(const UpperTri<T>& u)
{
  m_row = u.m_row;
  m_col = u.m_col;
  
  for(int i=0;i<m_row;i++)
  {
     delete [] m_ptr[i];
  }
  delete [] m_ptr;
  
  m_ptr = new T*[m_row];

  for(int i=0;i<m_row;i++)
  {
    m_ptr[i] = new T[m_row-i];
  }

  for(int i =0; i < m_row; i ++)
  {
    for(int j =0; j < m_row-i; j ++)
    {
      m_ptr[i][j] = u[i][j];
    }
  }
  return(*this);
}

template <class TU>
ostream& operator<<(ostream& out, const UpperTri<TU>& u)
{
  for(int i =0; i < u.m_row; i ++)
  {
    for(int j =0; j < u.m_col; j ++)
    {
      if(j>=i)
      {
        out << u.m_ptr[i][j-i] << " ";
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

template <class TU>
istream& operator>> (istream& is, UpperTri<TU>& u)
{
  TU eater; //take all the 0's
  for(int i =0; i < u.m_row; i ++)
  {
    for(int j =0; j < u.m_col; j ++)
    {
      if(j>=i)
      {
        is >> u.m_ptr[i][j-i];
      }
      else
      {
        is >> eater;
      }        
    }
  }
  return is;
}

template <class T>
T* UpperTri<T>::operator[](int i)
{
  if(i > m_row)
  {
    throw RangeError(i);
  }
  return(m_ptr[i]);
}
template <class T>
const T* UpperTri<T>::operator[](int i)const
{
  if(i > m_row)
  {
    throw RangeError(i);
  }
  return(m_ptr[i]);
}

template <class T>
UpperTri<T> UpperTri<T>::operator+(const UpperTri<T>& u)const
{
  if(m_row != u.m_row && m_col != u.m_col)
		throw SizeError(m_row);

  UpperTri<T> newU(m_row, m_col);
  
  for(int i = 0; i < m_row; i ++)
  {
    for(int j = 0; j < m_col-i; j++)
    {
      newU[i][j] = (*this)[i][j] + u[i][j];
      //cout << newU[i][j] << " ";
    }
    //cout << endl;
  }
  return(newU);
}

template <class T>
UpperTri<T> UpperTri<T>::operator-()const
{
  UpperTri<T> newU(m_row, m_col);
  
  for(int i = 0; i < m_row; i ++)
  {
    for(int j = 0; j < m_col-i; j++)
    {
      newU[i][j] = -(*this)[i][j];
     // cout << newU[i][j] << " ";
    }
    //cout << endl;
  }
  return(newU);
}

template <class T>
UpperTri<T> UpperTri<T>::operator-(const UpperTri<T>& u)const
{
  
  if(m_row != u.m_row && m_col != u.m_col)
		throw SizeError(m_row);

  UpperTri<T> newU(m_row, m_col);
  
  for(int i = 0; i < m_row; i ++)
  {
    for(int j = 0; j < m_col-i; j++)
    {
      newU[i][j] = (*this)[i][j] - u[i][j];
      //cout << newU[i][j] << " ";
    }
    //cout << endl;
  }
  return(newU);
}

template <class T>
UpperTri<T> UpperTri<T>::operator*(T& scalar)const
{
  UpperTri<T> newU(m_row, m_col);
  
  for(int i = 0; i < m_row; i ++)
  {
    for(int j = 0; j < m_col-i; j++)
    {
      newU[i][j] = scalar * (*this)[i][j];
     // cout << newU[i][j] << " ";
    }
    //cout << endl;
  }
  return(newU);
}


template <class T>
UpperTri<T> UpperTri<T>::operator*(const UpperTri<T>& u)const
{
  UpperTri<T> newU(m_row, m_col);
  int sum=0;
  
  for(int i=0; i < m_row; i++)
  {
    for(int j=i; j < m_col ; j++)
    {
      sum=0;
      for(int k=i; k <=j; k++)
      {
        sum += (*this)[i][k-i] * u[k][j-k];        
      }
      newU[i][j-i] = sum;
      //cout << newU[i][j] << " ";
    }
    //cout << endl;
  }
  return(newU);
}

template <class T>
Matrix<T> UpperTri<T>::transpose()
{
  Matrix<T> newM(m_col, m_row);

  for(int i =0; i < m_col; i ++)
  {
    for(int j =0; j < m_row; j ++)
    {
      if(j >=i)
      {
        newM[j][i] = (*this)[i][j-i]; //switch appropriate numbers
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

// template <class T>
// Matrix<T> UpperTri<T>::toMatrix()
// {
  // Matrix<T> newM(m_row, m_col);
  
  // for(int i =0; i < m_row; i ++)
  // {
    // for(int j =0;j < m_col; j ++)
    // {
      // if(j >=i)
      // {
        // newM[i][j] = (*this)[i][j];
      // }
      // else
      // {
        // newM[i][j] =0;
      // }
    // }
  // }
  // cout << newM << endl;
  // return(newM);
  
// }


template <class T>
Array<T> UpperTri<T>::backSub(Array<T> a)
{
  T sum = 0;
  Array<T> answers(m_row);
  
  
  answers[m_row-1] = (a[m_row-1])/(*this)[m_row-1][0];
  //sets first solution to the last augmented matrix number divided by the
  //last variable's cofefficient

  cout << "x" << m_row << " is " << answers[m_row-1] << endl;

  for(int i=m_row-2; i >=0; i--) //go through rows
  {
    sum = 0;
    for(int j=i+1; j <m_row; j ++) //sum up cols with known answers
    {
      sum += (*this)[i][j-i]*answers[j];    
    }

    answers[i] = (a[i] - sum)/((*this)[i][0]);
    if(abs(answers[i]) < 0.000000001)	//round to 0
    {
      answers[i] = 0;
    }
    cout << "x" << i+1 << " is " << answers[i] << endl;
  }
  return(answers);
}

template <class T>
Array<T> UpperTri<T>::solver(Array<T>& augment)
{
  return (backSub(augment));
}
