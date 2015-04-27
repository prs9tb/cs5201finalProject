/// Programmer: Patrick Sullivan
/// Date: 3 - 15 - 2015
/// Class: CS 5201 (Price)
/// Assignment #4: Matrices and Gaussian Elimination
/// File: driver.cpp
/// Purpose: main program for testing FullMatrix and Vector

#include <iostream>
#include <fstream>
#include <string>

#include "Vector.h"
#include "MatrixBase.h"
#include "FullMatrix.h"
#include "LowerTriMatrix.h"
#include "UpperTriMatrix.h"
#include "SymmMatrix.h"
       	 		#include "DiagMatrix.h"
#include "TriDiagMatrix.h"
#include "GlobalFunctions.h"
#include "GaussElim.h"
#include "CholeskyDecomp.h"
#include "ThomasTriDiag.h"
#include "Tests.h"

using namespace std;

int main(int argc, char * argv[])
{
	ifstream ifs;
	string filename;
	
	if (argc > 1)
		filename = argv[1];
	
	while ( ifs.is_open() == false)
	{
		if ( filename == "" )
		{
  	 	                                            	cout<<"Enter in the input data set:"<<endl;
		   	cin >> filename;
		}
		
		ifs.open(filename.c_str());
		filename = "";
	}
	
	
	int dimensions;
	ifs >> dimensions;
	FullMatrix<double> inputMatrix1(dimensions);
	Vector<double> bVec1(dimensions);
	ifs >> inputMatrix1;
	ifs >> bVec1;
	ifs >> dimensions;
	FullMatrix<double> inputMatrix2(dimensions);
	Vector<double> bVec2(dimensions);
	ifs >> inputMatrix2;
	ifs >> bVec2;
	ifs.close();
	
	TriDiagMatrix<double> triDiagInput(inputMatrix1);
	cout<<"*************   First input matrix: "<<endl;
	cout<<triDiagInput<<endl;
	cout<<"*************   First input vector: "<<endl;
	cout<<bVec1<<endl<<endl;
	
	SymmMatrix<double> symmInput(inputMatrix2);
	cout<<"*************   Second input matrix: "<<endl;
	cout<<symmInput<<endl;
	cout<<"*************   Second input vector: "<<endl;
	cout<<bVec2<<endl<<endl;
	
	
	
	cout<<"%%%%%%%%%%%% Here is the Thomas Algorithm: %%%%%%%%%%%%%%%"<<endl;
	ThomasTriDiag ThomasSolver;
	Vector<double> thomasSoln = ThomasSolver(triDiagInput, bVec1);
	cout<<"Solution is : "<<thomasSoln<<endl<<endl;
	
	cout<<"%%%%%%%%%%%% Here is the Cholesky Decomposition: %%%%%%%%%%%%%"<<endl;
	CholeskyDecomp symmDecomposer;
	LowerTriMatrix<double> decompMatrix = symmDecomposer(symmInput);
	cout<<decompMatrix<<endl<<endl;
	
	cout<<"Press enter to see some lovely Matrix tests: "<<endl;
	cin.get();
	
	// testVectorClass();
	// testFullMatrixClass();
	// testLowMatrixClass();
	// testUpperMatrixClass();
	testSymmMatrixClass();
	testDiagMatrixClass();
	testTriDiagMatrixClass();
	
	cout<<"*** You may comment/uncomment other tests suites in driver.cpp *** "<<endl;
	cout<<"*** All tests are in Tests.cpp , so go take a look if you're curious"<<endl;
	cout<<"Goodbye :) "<<endl;
	
	return 0;
}

