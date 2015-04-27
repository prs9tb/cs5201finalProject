//Abira Das
//assignment 4
//Error class

#ifndef RANGEERROR_H
#define RANGEERROR_H

#include <iostream>
using namespace std;

#include <exception>

class RangeError: public exception
{
  public:
    RangeError(int i);
    int badSubsur();
  private:
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
