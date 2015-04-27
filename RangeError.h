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


#include <exception>

class RangeError: public exception
{
  public:
    RangeError(int i)
	{
		char numstr[21]; // enough to hold all numbers up to 64-bits
		itoa(i, numstr, 10);
		
		strcat(message, "Range Error: ");
		strcat(message, numstr);
	}
	
	
	
	RangeError(const char* err)
	{
		strcat(message, err);
	}
	
	
	
    int badSubsur();
	virtual const char* what() const noexcept  
	{
		return message;
	}
	
  private:
	char* message[100];
    int subsur;
};

class SizeError: public exception
{
  public:
    SizeError(int i);
    int badSubsur();
  private:
    int subsur;
};
int RangeError::badSubsur()
{
  return subsur;
}
int SizeError::badSubsur()
{
  return subsur;
}
RangeError::RangeError(int i)
{
  subsur = i;
}

SizeError::SizeError(int i)
{
  subsur = i;
}

#endif
