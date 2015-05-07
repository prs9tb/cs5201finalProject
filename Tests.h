
#ifndef MATRIX_TESTS_H
#define MATRIX_TESTS_H

#include <iostream>
#include <assert.h>
#include <stdexcept>

#include "Vector.h"
#include "MatrixBase.h"
#include "FullMatrix.h"
#include "SymmMatrix.h"
#include "GlobalFunctions.h"

// void testTriDiagMatrixClass();
// void testDiagMatrixClass();
void testSymmMatrixClass();
// void testLowMatrixClass();
// void testUpperMatrixClass();
void testFullMatrixClass();
void testVectorClass();

template<class MT, class DT>
void testCalcOps(const MatrixBase<MT,DT>& matrix);


#include "Tests.hpp"

#endif

