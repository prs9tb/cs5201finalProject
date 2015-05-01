/// Programmer: Abira Das
/// Class: CS 5201 (Price)
/// File: SolverBase.h
/// Purpose: Interface Solver Base class


#ifndef SOLVER_BASE_H
#define SOLVER_BASE_H

#include "Vector.h"

template <class MT, class DT>
class SolverBase
{
  public:
    virtual Vector<DT> operator()(MT& a, Vector<DT>& b)=0;
};

#endif