//Abira Das
//assignment 4
//Error class

#ifndef RANGEERROR_H
#define RANGEERROR_H

#include <iostream>
using namespace std;

#include <cstring>
#include <stdlib.h>
#include <string.h>



#include <stdio.h>

#include <exception>

class RangeError: public exception
{
  public:
    RangeError(int i)
    {
      sprintf(message, "Range Error: value=%d", i);
    }
	
    RangeError(const char* err)
    {
      sprintf(message, "[%s]" , err);
    }
	
    virtual const char* what() const noexcept  
    {
      return message;
    }
	
  private:
    char message[100];
};

class SizeError: public exception
{
  public:
    SizeError(int i)
    {
      sprintf(message, "Size Error: value=%d", i);
    }
	
    SizeError(const char* err)
    {
      sprintf(message, "[%s]" , err);
    }
	
    virtual const char* what() const noexcept  
    {
      return message;
    }
	
  private:
    char message[100];
};

#endif
