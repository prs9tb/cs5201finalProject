
#include "Vector.h"
#include "MatrixBase.h"
#include "FullMatrix.h"
#include "LowerTriMatrix.h"
#include "UpperTriMatrix.h"
#include "SymmMatrix.h"
#include "DiagMatrix.h"
#include "TriDiagMatrix.h"
#include "GlobalFunctions.h"


#ifndef MATRIX_TESTS_H
#define MATRIX_TESTS_H

void testTriDiagMatrixClass();
void testDiagMatrixClass();
void testSymmMatrixClass();
void testLowMatrixClass();
void testUpperMatrixClass();
void testFullMatrixClass();
void testVectorClass();

template<class MT, class DT>
void testCalcOps(const MatrixBase<MT,DT>& matrix);


#endif

