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
#include "SymmMatrix.h"
#include "GlobalFunctions.h"
#include "Tests.h"


#include "GlobalPDE.hpp"

using namespace std;

int main(int argc, char * argv[])
{
	ifstream ifs;
	string filename;
	bool fileForInput = false;
	
	if (argc > 1)
	{
		filename = argv[1];
		fileForInput = true;
	}
	
	while (fileForInput && ifs.is_open() == false)
	{
		if ( filename == "" )
		{
			cout<<"Enter input file:"<<endl;
		   	cin >> filename;
		}
		ifs.open(filename.c_str());
		filename = "";
	}
	
  cout<<"genBvec = 4:  ";
  Vector<double> bVec = genBpdeVector(4);
  cout<<bVec<<endl;
  
  return 0;
  
	cout<<"Running unit tests ...."<<endl;
	
	testVectorClass();
	testFullMatrixClass();
	// testSymmMatrixClass();
	
	return 0;
}

